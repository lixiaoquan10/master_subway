#include "cglobal.h"
#include "cprocessmqtt.h"
#include "cclientbusiness.h"
#include <QtMqtt/QMqttClient>
#include <QJsonDocument>
#include <QJsonObject>

CprocessMqtt::CprocessMqtt(QMqttClient *mqttClient) : m_mqttClient(mqttClient)
{
    m_msgid = 1;
    m_isPingRespond = true;
    m_productKey = "安科瑞应急照明与疏散指示系统";
    m_reconnectInterval = m_initialReconnectInterval;
    m_deviceSN = CGlobal::instance()->ClientBusiness()->generateUniqueID();
    m_mqttClient->setProtocolVersion(QMqttClient::MQTT_3_1_1);
    m_mqttClient->setClientId(m_deviceSN);
    //通讯状态变化
    connect(m_mqttClient, &QMqttClient::stateChanged, this, &CprocessMqtt::slot_updateLogStateChange);
    //断开连接
    connect(m_mqttClient, &QMqttClient::disconnected, this, &CprocessMqtt::slot_brokerDisconnected);
    //数据接收
    connect(m_mqttClient, &QMqttClient::messageReceived, this, &CprocessMqtt::slot_handleMessageReceived);
    //心跳ping数据回复
    connect(m_mqttClient, &QMqttClient::pingResponseReceived, this, &CprocessMqtt::slot_pingResponse);
    // 连接发布后的信号
    connect(m_mqttClient, &QMqttClient::messageStatusChanged, this, &CprocessMqtt::slot_messageStatusChanged);
    //定时ping
    m_pingTimer = new QTimer();
    connect(m_pingTimer, &QTimer::timeout, this, &CprocessMqtt::slot_requestPing);
    //定时重连
    m_reconnectTimer = new QTimer();
    connect(m_reconnectTimer, &QTimer::timeout, this, &CprocessMqtt::slot_reconnectToBroker);
}

CprocessMqtt::~CprocessMqtt()
{
    m_mqttClient->disconnectFromHost();
    delete m_mqttClient;
    delete m_pingTimer;
    delete m_reconnectTimer;
    // 清理所有定时器
    for (QTimer *timer : m_resendTimers) {
        timer->stop();  // 停止定时器
        delete timer;   // 删除定时器
    }
    // 清理定时器列表本身
    m_resendTimers.clear();
    // 清理发送的消息列表（此处不需要额外的清理工作，QString 和 QByteArray 会自动销毁）
    m_sendMessages.clear();
}

//断开连接
void CprocessMqtt::slot_brokerDisconnected()
{
    m_reconnectTimer->start(m_reconnectInterval);
    m_pingTimer->stop();
    // 清理所有定时器
    for (QTimer *timer : m_resendTimers) {
        timer->stop();  // 停止定时器
        delete timer;   // 删除定时器
    }
    // 清理定时器列表本身
    m_resendTimers.clear();
    // 清理发送的消息列表（此处不需要额外的清理工作，QString 和 QByteArray 会自动销毁）
    m_sendMessages.clear();
    const QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + m_mqttClient->hostname()
            + QLatin1String(":")
            + QString::number(m_mqttClient->port())
            + QLatin1Char('\n')
            + QLatin1String("MQTT broker disconnected")
            + QLatin1Char('\n');
    saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
}

//连接状态发生变化
void CprocessMqtt::slot_updateLogStateChange()
{
    QString content;
    content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + m_mqttClient->hostname()
            + QLatin1String(":")
            + QString::number(m_mqttClient->port())
            + QLatin1Char('\n');
    if(m_mqttClient->state() == QMqttClient::Disconnected)
    {
        emit connectStatus(false);
        content = content
                + QLatin1String("MQTT state changed. Now: disconnected")
                + QLatin1Char('\n');
        saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
    }
    else if(m_mqttClient->state() == QMqttClient::Connecting)
    {
        content = content
                + QLatin1String("MQTT state changed. Now: connecting")
                + QLatin1Char('\n');
        saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
    }
    else if(m_mqttClient->state() == QMqttClient::Connected)
    {
        content = content
                + QLatin1String("MQTT state changed. Now: connected")
                + QLatin1Char('\n');
        saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
        m_isPingRespond = true;
        emit connectStatus(true);
        subscribeComTopic();
        uploadAllDeviceInfo();
        QTimer::singleShot(5000, this, &CprocessMqtt::slot_uploadAllDeviceStatus);
        m_pingTimer->start(2000);
        // 重置重连间隔
        m_reconnectInterval = m_initialReconnectInterval;
        m_reconnectTimer->stop();
    }
}

//手动连接服务器
void CprocessMqtt::manualConnectToBroker(const QString &host, quint16 port)
{
    m_host = host;
    m_port = port;
    m_mqttClient->setHostname(host);
    m_mqttClient->setPort(port);
    m_mqttClient->connectToHost();
    QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + QLatin1String("MQTT start connecting...")
            + QLatin1Char('\n')
            + m_host
            + QLatin1String(":")
            + QString::number(m_port)
            + QLatin1Char('\n');

    saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
}

//手动断开连接
void CprocessMqtt::manualDisconnectToBroker()
{
    m_mqttClient->disconnectFromHost();
}

//重连服务器
void CprocessMqtt::slot_reconnectToBroker()
{
    m_mqttClient->setHostname(m_host);
    m_mqttClient->setPort(m_port);
    m_mqttClient->connectToHost();
    QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + QLatin1String("MQTT restart connecting...")
            + QLatin1Char('\n')
            + m_host
            + QLatin1String(":")
            + QString::number(m_port)
            + QLatin1Char('\n');
    saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
    // 增加重连间隔，指数增长但不超过最大值
    m_reconnectInterval = qMin(m_reconnectInterval * 2, m_maxReconnectInterval);
    m_reconnectTimer->start(m_reconnectInterval);
}

//订阅通讯所需主题
void CprocessMqtt::subscribeComTopic()
{
    subscribeToTopic(QString("v1/{%1}/{%2}/sys/service/invoke").arg(m_productKey).arg(m_deviceSN));
}

//订阅主题
void CprocessMqtt::subscribeToTopic(const QString &topic)
{
    QString data;
    if (m_mqttClient->state() == QMqttClient::Connected)
    {
        QMqttSubscription *subscription = m_mqttClient->subscribe(topic);
        if (subscription)
        {
            data = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                    + QLatin1Char('\n')
                    + m_host
                    + QLatin1String(":")
                    + QString::number(m_port)
                    + QLatin1Char('\n')
                    + QLatin1String("Subscribe to topic:  ")
                    + topic
                    + QLatin1Char('\n');
            connect(subscription, SIGNAL(messageReceived(QByteArray, QMqttTopicName)),
                                this, SLOT(slot_handleMessageReceived(QByteArray, QMqttTopicName)));
        }
        else
        {
            data = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                    + QLatin1Char('\n')
                    + m_host
                    + QLatin1String(":")
                    + QString::number(m_port)
                    + QLatin1Char('\n')
                    + QLatin1String("Failed to subscribe to topic:  ")
                    + topic
                    + QLatin1Char('\n');
        }
        saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", data);
    } else {
        data = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                + QLatin1Char('\n')
                + m_host
                + QLatin1String(":")
                + QString::number(m_port)
                + QLatin1Char('\n')
                + QLatin1String("SubscribeToTopic failed. MQTT client is not connected.")
                + QLatin1Char('\n');
        saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", data);
        manualDisconnectToBroker();
        manualConnectToBroker(m_host, m_port);
    }  
}
//发送数据
void CprocessMqtt::publishMessage(const QString &topic, const QByteArray &message)
{
    QString filePath = "/home/xfss/root/logfile/MQTTData.txt";
    if (m_mqttClient->state() == QMqttClient::Connected) {
        quint32 packetId = m_mqttClient->publish(topic, message, 1);
        // 记录消息内容、主题和定时器
        m_sendMessages[packetId] = qMakePair(message, topic);
        // 为每个已发布的消息启动一个定时器，3秒超时后重发
        if (!m_resendTimers.contains(packetId)) {
            QTimer *timer = new QTimer(this);
            timer->setSingleShot(true);  // 只触发一次
            connect(timer, &QTimer::timeout, this, &CprocessMqtt::slot_ResendTimerTimeout);
            m_resendTimers[packetId] = timer;
            timer->start(m_resendTimeout);  // 启动定时器，3秒后超时
        }
        QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                + QLatin1Char('\n')
                + m_host
                + QLatin1String(":")
                + QString::number(m_port)
                + QLatin1Char('\n')
                + QLatin1String("Send Topic: ")
                + topic
                + QLatin1Char('\n')
                + QLatin1String("packetId: ")
                + QString::number(packetId)
                + QLatin1Char('\n')
                + message
                + QLatin1Char('\n');
        saveDataToFile(filePath, content);
    } else {
        QString data = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                + QLatin1Char('\n')
                + m_host
                + QLatin1String(":")
                + QString::number(m_port)
                + QLatin1Char('\n')
                + QLatin1String("MQTT client is not connected.")
                + QLatin1Char('\n');
        saveDataToFile(filePath, data);
        manualDisconnectToBroker();
        manualConnectToBroker(m_host, m_port);
    }
    CGlobal::instance()->controlTxtFileSize(filePath, 1024 * 1024);
}

// 处理消息状态变化的槽函数
void CprocessMqtt::slot_messageStatusChanged(quint16 packetId, QMqtt::MessageStatus status)
{
    QString str;
    switch (status) {
        case QMqtt::MessageStatus::Acknowledged:
            str = " has been acknowledged.";
            // 停止并删除对应的定时器
            if (m_resendTimers.contains(packetId)) {
                QTimer *timer = m_resendTimers.take(packetId);
                timer->stop();
                delete timer;  // 删除定时器
                m_sendMessages.remove(packetId);
            }
            break;
        default:
            str = " Unknown status for packetId";
            break;
    }
    QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + m_host
            + QLatin1String(":")
            + QString::number(m_port)
            + QLatin1Char('\n')
            + "packetId:"
            + QString::number(packetId)
            + str
            + QLatin1Char('\n');
    saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
}

//接收ACK数据超时处理
void CprocessMqtt::slot_ResendTimerTimeout()
{
    // 获取所有定时器，判断哪个超时了
    for (auto it = m_resendTimers.begin(); it != m_resendTimers.end();) {
        quint16 packetId = it.key();
        QTimer *timer = it.value();

        if (timer->isActive()) {
            // 超时处理逻辑: 如果没有收到 `Acknowledged` 状态，则进行重发
            // 获取消息内容并重新发布
            if (m_sendMessages.contains(packetId)) {
                QByteArray message = m_sendMessages[packetId].first;  // 消息内容
                QString topic = m_sendMessages[packetId].second;      // 消息主题
                publishMessage(topic, message);
                m_sendMessages.remove(packetId);
                QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                        + QLatin1Char('\n')
                        + m_host
                        + QLatin1String(":")
                        + QString::number(m_port)
                        + QLatin1Char('\n')
                        + "No Acknowledged! Resend packetId:"
                        + QString::number(packetId)
                        + QLatin1Char('\n');
                saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
            }

            // 重发后，重新启动定时器
            timer->start(m_resendTimeout);  // 再次启动定时器等待下次超时
            ++it;  // 保持原有迭代器
        } else {
            // 如果定时器已经停止，移除该项
            it = m_resendTimers.erase(it);
        }
    }
}

//接收数据处理
void CprocessMqtt::slot_handleMessageReceived(const QByteArray &message, const QMqttTopicName &topic)
{
    const QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + m_host
            + QLatin1String(":")
            + QString::number(m_port)
            + QLatin1Char('\n')
            + QLatin1String(" Received Topic: ")
            + topic.name()
            + QLatin1Char('\n')
            + message
            + QLatin1Char('\n');
    saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
    if(topic.name() == QString("v1/{%1}/{%2}/sys/service/invoke").arg(m_productKey).arg(m_deviceSN))
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(message);
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();

            QString msgid = jsonObj.value("msgid").toString();
            QJsonObject params = jsonObj.value("params").toObject();
            if(msgid == "")
            {
                replyHostControl(QString::number(m_msgid++), false);
                return;
            }
            // 提取各个字段
            QString reset = params.value("Reset").toObject().value("value").toString();
            QString start = params.value("Start").toObject().value("value").toString();
            if((reset == "") || (start == "") ||
                    ((reset != "True") && (reset != "False")) ||
                    ((start != "True") && (start != "False")))
            {
                replyHostControl(msgid, false);
                return;
            }
            if(reset == "True")
                emit hostControlMsg(0x01);
            if(start == "True")
                emit hostControlMsg(0x02);
            replyHostControl(msgid, true);
        }
    }
}

//请求心跳ping
void CprocessMqtt::slot_requestPing()
{
    if(m_isPingRespond) {
        //有回复
        m_mqttClient->requestPing();
        QString str = QString::number(m_mqttClient->state());
        const QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
                + QLatin1Char('\n')
                + m_host
                + QLatin1String(":")
                + QString::number(m_port)
                + QLatin1Char('\n')
                + QLatin1String("MQTT requestPing.  state: ")
                + str
                + QLatin1Char('\n');
        saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
    } else {
        //无回复
        manualDisconnectToBroker();
    }
    m_isPingRespond = false;
}

//心跳ping回复
void CprocessMqtt::slot_pingResponse()
{
    m_isPingRespond = true;
    const QString content = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz")
            + QLatin1Char('\n')
            + m_host
            + QLatin1String(":")
            + QString::number(m_port)
            + QLatin1Char('\n')
            + QLatin1String("MQTT pingResponse.")
            + QLatin1Char('\n');
    saveDataToFile("/home/xfss/root/logfile/MQTTData.txt", content);
}

//回复服务器控制指令
void CprocessMqtt::replyHostControl(QString msgid, bool isTrue)
{
    QString topic = QString("v1/{%1}/{%2}/sys/service/invoke_reply").arg(m_productKey).arg(m_deviceSN);
    QJsonObject msgObj;
    msgObj["msgid"] = msgid;
    if(isTrue)
        msgObj["code"] = 0;
    else
        msgObj["code"] = -1;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    publishMessage(topic, jsonData);
}

//上传所有设备信息到服务器
void CprocessMqtt::uploadAllDeviceInfo()
{
    QString topic = QString("v1/{%1}/{%2}/sys/property/up").arg(m_productKey).arg(m_deviceSN);
    // 创建上行报文
    CController* controller = CGlobal::instance()->controller();
    if(!controller)
        return;
    QByteArray controllerJsonData = creatControllerJsonData(controller);
    publishMessage(topic, controllerJsonData);
    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
    {
        CCanport* canport = controller->canportByAddress(i);
        if(!canport)
            continue;
        for(int j=0; j<62; j++)
        {
            CDistribution* distribution = canport->distributionByAddress(j+1);
            if(distribution)
            {
                QByteArray distributionJsonData = creatDistributionJsonData(distribution);
                publishMessage(topic, distributionJsonData);
                for(int l=0; l<8; l++)
                {
                    CLoop* loop = distribution->loopByAdd(l+1);
                    if(loop)
                    {
                        QByteArray loopJsonData = creatLoopJsonData(loop);
                        publishMessage(topic, loopJsonData);
                        for(int m=0; m<255; m++)
                        {
                            CDevice* device = loop->deviceByAdd(m+1);
                            if(device)
                            {
                                QByteArray deviceJsonData = creatDeviceJsonData(device);
                                publishMessage(topic, deviceJsonData);
                            }
                        }
                    }
                }
            }
        }
    }
}

//设备状态变化上报
void CprocessMqtt::slot_sendDeviceStatusMsg(CObject* object, bool isDistributionEmergencyOrFault)
{
    QString type = object->type();
    QString topic = QString("v1/{%1}/{%2}/sys/event/up").arg(m_productKey).arg(m_deviceSN);
    if(type == CController::type_s)
    {
        CController* controller = static_cast<CController*>(object);
        if(!controller)
            return;
        QByteArray controllerJsonData = creatControllerStatusJsonData(controller);
        publishMessage(topic, controllerJsonData);
    }
    else if(type == CDistribution::type_s)
    {
        CDistribution* distribution = static_cast<CDistribution*>(object);
        if(!distribution)
            return;
        QByteArray distributionJsonStatusData = creatDistributionStatusJsonData(distribution);
        publishMessage(topic, distributionJsonStatusData);
        if(!isDistributionEmergencyOrFault)
            return;
        for(int l=0; l<8; l++)
        {
            CLoop* loop = distribution->loopByAdd(l+1);
            if(!loop)
                continue;
            if(distribution->getStatus(OBJS_DistributionCommunicationFault))
            {
                QByteArray loopStatusJsonData = creatLoopStatusJsonData(loop);
                publishMessage(topic, loopStatusJsonData);
            }
            QList<CDevice*> devices = loop->devices();
            for(int m=0; m<devices.count(); m++)
            {
                CDevice* device = devices.at(m);
                if(device)
                {
                    QByteArray deviceStatusJsonData = creatDeviceStatusJsonData(device);
                    publishMessage(topic, deviceStatusJsonData);
                }
            }
            devices.clear();
        }
    }
    else if(type == CLoop::type_s)
    {
        CLoop* loop = static_cast<CLoop*>(object);
        if(!loop)
            return;
        QByteArray loopJsonData = creatLoopStatusJsonData(loop);
        publishMessage(topic, loopJsonData);
        QList<CDevice*> devices = loop->devices();
        for(int m=0; m<devices.count(); m++)
        {
            CDevice* device = devices.at(m);
            if(device)
            {
                QByteArray deviceStatusJsonData = creatDeviceStatusJsonData(device);
                publishMessage(topic, deviceStatusJsonData);
            }
        }
        devices.clear();
    }
    else if(type == CDevice::type_s)
    {
        CDevice* device = static_cast<CDevice*>(object);
        if(!device)
            return;
        QByteArray deviceJsonData = creatDeviceStatusJsonData(device);
        publishMessage(topic, deviceJsonData);
    }
}

//上传所有设备状态到服务器
void CprocessMqtt::slot_uploadAllDeviceStatus()
{
    QString topic = QString("v1/{%1}/{%2}/sys/event/up").arg(m_productKey).arg(m_deviceSN);
    // 创建上行报文
    CController* controller = CGlobal::instance()->controller();
    if(!controller)
        return;
    QByteArray controllerJsonStatusData = creatControllerStatusJsonData(controller);
    publishMessage(topic, controllerJsonStatusData);
    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
    {
        CCanport* canport = controller->canportByAddress(i);
        if(!canport)
            continue;
        QList<CDistribution*> distributions = canport->distributions();
        for(int j=0; j<distributions.count(); j++)
        {
            CDistribution* distribution = distributions.at(j);
            if(!distribution)
                continue;
            QByteArray distributionJsonStatusData = creatDistributionStatusJsonData(distribution);
            publishMessage(topic, distributionJsonStatusData);
            for(int l=0; l<8; l++)
            {
                CLoop* loop = distribution->loopByAdd(l+1);
                if(!loop)
                    continue;
                QByteArray loopStatusJsonData = creatLoopStatusJsonData(loop);
                publishMessage(topic, loopStatusJsonData);
                QList<CDevice*> devices = loop->devices();
                for(int m=0; m<devices.count(); m++)
                {
                    CDevice* device = devices.at(m);
                    if(device)
                    {
                        QByteArray deviceStatusJsonData = creatDeviceStatusJsonData(device);
                        publishMessage(topic, deviceStatusJsonData);
                    }
                }
                devices.clear();
            }
        }
        distributions.clear();
    }
}


//创建控制器数据
QByteArray CprocessMqtt::creatControllerJsonData(CController* controller)
{
    Q_UNUSED(controller);
    // 创建上行报文
    QJsonObject controllerType;
    controllerType["value"] = "应急照明控制器";
    controllerType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject controllerID;
    controllerID["value"] = "1";
    controllerID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject paramsObj;
    paramsObj["Type"] = controllerType;
    paramsObj["ControllerID"] = controllerID;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

//创建集中电源数据
QByteArray CprocessMqtt::creatDistributionJsonData(CDistribution* distribution)
{
    // 创建上行报文
    QJsonObject distributionID;
    distributionID["value"] = QString::number(distribution->keyId());
    distributionID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionAddress;
    distributionAddress["value"] = QString::number(distribution->canportAddress()-2) + "-" +
            QString::number(distribution->distributionAddress());
    distributionAddress["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionType;
    distributionType["value"] = "集中电源";
    distributionType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionName;
    distributionName["value"] = distribution->distributionValue(DISTRIBUTION_VALUE_NAME).toString();
    distributionName["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionArea;
    distributionArea["value"] = distribution->distributionValue(DISTRIBUTION_VALUE_AREA).toString();
    distributionArea["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionLocation;
    distributionLocation["value"] = distribution->distributionValue(DISTRIBUTION_VALUE_LOCATION).toString();
    distributionLocation["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject paramsObj;
    paramsObj["CanDeviceID"] = distributionID;
    paramsObj["Type"] = distributionType;
    paramsObj["Name"] = distributionName;
    paramsObj["CanDeviceAddress"] = distributionAddress;
    paramsObj["Area"] = distributionArea;
    paramsObj["Location"] = distributionLocation;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

//创建回路数据
QByteArray CprocessMqtt::creatLoopJsonData(CLoop* loop)
{
    // 创建上行报文
    QJsonObject loopID;
    loopID["value"] = QString::number(loop->keyId());
    loopID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopType;
    loopType["value"] = "回路";
    loopType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopName;
    QString name = "回路" + QString::number(loop->loopAdd());
    loopName["value"] = name;
    loopName["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopAddress;
    loopAddress["value"] = QString::number(loop->canportAdd()-2) + "-" +
            QString::number(loop->distributionAdd()) + "-" +
            QString::number(loop->loopAdd());
    loopAddress["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject paramsObj;
    paramsObj["LoopID"] = loopID;
    paramsObj["Type"] = loopType;
    paramsObj["Name"] = loopName;
    paramsObj["LoopAddress"] = loopAddress;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

//创建灯具数据
QByteArray CprocessMqtt::creatDeviceJsonData(CDevice* lamp)
{
    // 创建上行报文
    QJsonObject lampID;
    lampID["value"] = QString::number(lamp->keyId());
    lampID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampType;
    lampType["value"] = "灯具";
    lampType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampName;
    lampName["value"] = lamp->deviceValue(DEVICE_VALUE_TYPE).toString();
    lampName["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampAddress;
    lampAddress["value"] = QString::number(lamp->canportAdd()-2) + "-" +
            QString::number(lamp->distributionAdd()) + "-" +
            QString::number(lamp->loopAdd()) + "-" +
            QString::number(lamp->deviceAdd());
    lampAddress["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampArea;
    lampArea["value"] = lamp->deviceValue(DEVICE_VALUE_AREA).toString();
    lampArea["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampLocation;
    lampLocation["value"] = lamp->deviceValue(DEVICE_VALUE_LOCATION).toString();
    lampLocation["ts"] = QDateTime::currentMSecsSinceEpoch();


    QJsonObject paramsObj;
    paramsObj["LampID"] = lampID;
    paramsObj["Type"] = lampType;
    paramsObj["Name"] = lampName;
    paramsObj["LampAddress"] = lampAddress;
    paramsObj["LampArea"] = lampArea;
    paramsObj["LampLocation"] = lampLocation;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}


//创建控制器状态数据
QByteArray CprocessMqtt::creatControllerStatusJsonData(CController* controller)
{
    // 创建上行报文
    QJsonObject controllerType;
    controllerType["value"] = "应急照明控制器";
    controllerType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject controllerID;
    controllerID["value"] = "1";
    controllerID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject controllerMainPowerFault;
    controllerMainPowerFault["value"] = CGlobal::instance()->m_isShieldMainPowerFaultEmergency? "True" : "False";
    controllerMainPowerFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject controllerBatteryPowerFault;
    controllerBatteryPowerFault["value"] =  (controller->getStatus(OBJS_StandbyPowerOff) ||
                                             controller->getStatus(OBJS_StandbyPowerShort) ||
                                             controller->getStatus(OBJS_StandbyPowerUndervoltage))? "True" : "False";
    controllerBatteryPowerFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject controllerWarning;
    controllerWarning["value"] = CGlobal::instance()->m_isEmergency? "True" : "False";
    controllerWarning["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject paramsObj;
    paramsObj["Type"] = controllerType;
    paramsObj["ControllerID"] = controllerID;
    paramsObj["MainPowerFault"] = controllerMainPowerFault;
    paramsObj["BatteryPowerFault"] = controllerBatteryPowerFault;
    paramsObj["Warning"] = controllerWarning;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

//创建集中电源状态数据
QByteArray CprocessMqtt::creatDistributionStatusJsonData(CDistribution* distribution)
{
    // 创建上行报文
    QJsonObject distributionID;
    distributionID["value"] = QString::number(distribution->keyId());
    distributionID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionAddress;
    distributionAddress["value"] = QString::number(distribution->canportAddress()-2) + "-" +
            QString::number(distribution->distributionAddress());
    distributionAddress["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionType;
    distributionType["value"] = "集中电源";
    distributionType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionName;
    distributionName["value"] = distribution->distributionValue(DISTRIBUTION_VALUE_NAME).toString();
    distributionName["ts"] = QDateTime::currentMSecsSinceEpoch();


    QJsonObject distributionCommunicationFault;
    distributionCommunicationFault["value"] = distribution->getStatus(OBJS_DistributionCommunicationFault)? "True" : "False";
    distributionCommunicationFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionMainPowerFault;
    distributionMainPowerFault["value"] = distribution->getmainPowerFault()? "True" : "False";
    distributionMainPowerFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionBatteryPowerFault;
    distributionBatteryPowerFault["value"] = distribution->getbackupPowerFault()? "True" : "False";
    distributionBatteryPowerFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject distributionWarning;
    distributionWarning["value"] = distribution->getemergencyStatus()? "True" : "False";
    distributionWarning["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject paramsObj;

    paramsObj["CanDeviceID"] = distributionID;
    paramsObj["Type"] = distributionType;
    paramsObj["Name"] = distributionName;
    paramsObj["CanDeviceAddress"] = distributionAddress;
    paramsObj["CommunicationFault"] = distributionCommunicationFault;
    paramsObj["MainPowerFault"] = distributionMainPowerFault;
    paramsObj["BatteryPowerFault"] = distributionBatteryPowerFault;
    paramsObj["Warning"] = distributionWarning;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

//创建回路状态数据
QByteArray CprocessMqtt::creatLoopStatusJsonData(CLoop* loop)
{
    // 创建上行报文
    QJsonObject loopID;
    loopID["value"] = QString::number(loop->keyId());
    loopID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopType;
    loopType["value"] = "回路";
    loopType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopName;
    QString name = "回路" + QString::number(loop->loopAdd());
    loopName["value"] = name;
    loopName["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopAddress;
    loopAddress["value"] = QString::number(loop->canportAdd()-2) + "-" +
            QString::number(loop->distributionAdd()) + "-" +
            QString::number(loop->loopAdd());
    loopAddress["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject loopCommunicationFault;
    loopCommunicationFault["value"] = loop->getLoopCommunicationFault()? "True" : "False";
    loopCommunicationFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject paramsObj;
    paramsObj["LoopID"] = loopID;
    paramsObj["Type"] = loopType;
    paramsObj["Name"] = loopName;
    paramsObj["LoopAddress"] = loopAddress;
    paramsObj["CommunicationFault"] = loopCommunicationFault;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

//创建灯具状态数据
QByteArray CprocessMqtt::creatDeviceStatusJsonData(CDevice* lamp)
{
    // 创建上行报文
    QJsonObject lampID;
    lampID["value"] = QString::number(lamp->keyId());
    lampID["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampType;
    lampType["value"] = "灯具";
    lampType["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampName;
    lampName["value"] = lamp->deviceValue(DEVICE_VALUE_TYPE).toString();
    lampName["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampAddress;
    lampAddress["value"] = QString::number(lamp->canportAdd()-2) + "-" +
            QString::number(lamp->distributionAdd()) + "-" +
            QString::number(lamp->loopAdd()) + "-" +
            QString::number(lamp->deviceAdd());
    lampAddress["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampCommunicationFault;
    lampCommunicationFault["value"] = !lamp->isDeviceOnline()? "True" : "False";
    lampCommunicationFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampLightFault;
    lampLightFault["value"] = (lamp->deviceValue(DEVICE_VALUE_LIGHT) == "光源故障")? "True" : "False";
    lampLightFault["ts"] = QDateTime::currentMSecsSinceEpoch();

    QJsonObject lampWarning;
    lampWarning["value"] = (lamp->deviceValue(DEVICE_VALUE_EMERGENCY) == "应急"
                                 || CGlobal::instance()->m_isEmergency)? "True" : "False";
    lampWarning["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject paramsObj;
    paramsObj["LampID"] = lampID;
    paramsObj["Type"] = lampType;
    paramsObj["Name"] = lampName;
    paramsObj["LampAddress"] = lampAddress;
    paramsObj["CommunicationFault"] = lampCommunicationFault;
    paramsObj["LightFault"] = lampLightFault;
    paramsObj["Warning"] = lampWarning;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

void CprocessMqtt::saveDataToFile(QString fileName, QString data)
{
    QFile file(fileName);
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << data << '\n';
        file.close();
    }
//    CGlobal::instance()->controlTxtFileSize(filePath, 1024 * 1024);
}

