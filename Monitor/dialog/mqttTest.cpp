#include "mqttTest.h"
#include "ui_mqttTest.h"
#include "cglobal.h"

#include <QtCore/QDateTime>
#include <QtMqtt/QMqttClient>
#include <QtWidgets/QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>

mqttTest::mqttTest(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::mqttTest)
{
    m_msgid = 1;
    ui->setupUi(this);

    ui->lineEditHost->setText("broker.hivemq.com");
    ui->lineEditTopic->setText("$v1/{安科瑞消防疏散}/{111}/sys/property/up");
    m_client = new QMqttClient(this);
    m_client->setHostname(ui->lineEditHost->text());
    m_client->setPort(ui->spinBoxPort->value());

    connect(m_client, &QMqttClient::stateChanged, this, &mqttTest::updateLogStateChange);
    connect(m_client, &QMqttClient::disconnected, this, &mqttTest::brokerDisconnected);

    connect(m_client, &QMqttClient::messageReceived, this, [this](const QByteArray &message, const QMqttTopicName &topic) {
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" Received Topic: ")
                    + topic.name()
                    + QLatin1String(" Message: ")
                    + message
                    + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
    });

    connect(m_client, &QMqttClient::pingResponseReceived, this, [this]() {
        ui->buttonPing->setEnabled(true);
        const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(" PingResponse")
                    + QLatin1Char('\n');
        ui->editLog->insertPlainText(content);
    });

    connect(ui->lineEditHost, &QLineEdit::textChanged, m_client, &QMqttClient::setHostname);
    connect(ui->spinBoxPort, QOverload<int>::of(&QSpinBox::valueChanged), this, &mqttTest::setClientPort);
    updateLogStateChange();
}

mqttTest::~mqttTest()
{
    delete ui;
}

void mqttTest::on_buttonConnect_clicked()
{
    if (m_client->state() == QMqttClient::Disconnected) {
        ui->lineEditHost->setEnabled(false);
        ui->spinBoxPort->setEnabled(false);
        ui->buttonConnect->setText(tr("断开"));
        m_client->connectToHost();
    } else {
        ui->lineEditHost->setEnabled(true);
        ui->spinBoxPort->setEnabled(true);
        ui->buttonConnect->setText(tr("连接"));
        m_client->disconnectFromHost();
    }
}

void mqttTest::on_buttonQuit_clicked()
{
    this->close();
}

void mqttTest::updateLogStateChange()
{
    const QString content = QDateTime::currentDateTime().toString()
                    + QLatin1String(": State Change")
                    + QString::number(m_client->state())
                    + QLatin1Char('\n');
    ui->editLog->insertPlainText(content);
}

void mqttTest::brokerDisconnected()
{
    ui->lineEditHost->setEnabled(true);
    ui->spinBoxPort->setEnabled(true);
    ui->buttonConnect->setText(tr("连接"));
}

void mqttTest::setClientPort(int p)
{
    m_client->setPort(p);
}

void mqttTest::on_buttonPublish_clicked()
{
    uploadDeviceInfo();
//    if (m_client->publish(ui->lineEditTopic->text(), ui->lineEditMessage->text().toUtf8()) == -1)
//        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not publish message"));
}

void mqttTest::on_buttonSubscribe_clicked()
{
    auto subscription = m_client->subscribe(ui->lineEditTopic->text());
    if (!subscription) {
        QMessageBox::critical(this, QLatin1String("Error"), QLatin1String("Could not subscribe. Is there a valid connection?"));
        return;
    }
}

void mqttTest::uploadDeviceInfo()
{
//    qDebug() << "CprocessMqtt::XmlLampInfo"
//             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    QString topic = ui->lineEditTopic->text();
    // 创建上行报文
    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
    {
        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
        if(!canport)
            continue;
        for(int j=0; j<62; j++)
        {
            CDistribution* distribution = canport->distributionByAddress(j+1);
            if(distribution)
            {
                QByteArray distributionJsonData = creatDistributionJsonData(distribution);
                m_client->publish(topic, distributionJsonData);
                for(int l=0; l<8; l++)
                {
                    CLoop* loop = distribution->loopByAdd(l+1);
                    if(loop)
                    {
                        for(int m=0; m<255; m++)
                        {
                            CDevice* device = loop->deviceByAdd(m+1);
                            if(device)
                            {
                                QByteArray deviceJsonData = creatDeviceJsonData(device);
                                m_client->publish(topic, deviceJsonData);
                            }
                        }
                    }
                }
            }
        }
    }
}

QByteArray mqttTest::creatDistributionJsonData(CDistribution* distribution)
{
    // 创建上行报文
    qint64 distributionTime = QDateTime::currentMSecsSinceEpoch();
    QJsonObject distributionName;
    distributionName["value"] = "集中电源";
    distributionName["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject distributionAddress;
    distributionAddress["value"] = QString::number(distribution->canportAddress()-2) + "-" + QString::number(distribution->distributionAddress());
    distributionAddress["ts"] = QDateTime::currentMSecsSinceEpoch();
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
    paramsObj["Name"] = distributionName;
    paramsObj["Address"] = distributionAddress;
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

QByteArray mqttTest::creatDeviceJsonData(CDevice* device)
{
    // 创建上行报文
    qint64 deviceTime = QDateTime::currentMSecsSinceEpoch();
    QJsonObject deviceName;
    deviceName["value"] = "灯具";
    deviceName["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject deviceCommunicationFault;
    deviceCommunicationFault["value"] = !device->isDeviceOnline()? "True" : "False";
    deviceCommunicationFault["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject deviceAddress;
    deviceAddress["value"] = QString::number(device->canportAdd()-2)
            + "-" + QString::number(device->distributionAdd())
            + "-" + QString::number(device->loopAdd())
            + "-" + QString::number(device->deviceAdd());
    deviceAddress["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject deviceLightFault;
    deviceLightFault["value"] = (device->deviceValue(DEVICE_VALUE_LIGHT) == "光源故障")? "True" : "False";
    deviceLightFault["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject deviceWarning;
    deviceWarning["value"] = (device->deviceValue(DEVICE_VALUE_EMERGENCY) == "应急"
                                 || CGlobal::instance()->m_isEmergency)? "True" : "False";
    deviceWarning["ts"] = QDateTime::currentMSecsSinceEpoch();
    QJsonObject paramsObj;
    paramsObj["Name"] = deviceName;
    paramsObj["Address"] = deviceAddress;
    paramsObj["CommunicationFault"] = deviceCommunicationFault;
    paramsObj["LightFault"] = deviceLightFault;
    paramsObj["Warning"] = deviceWarning;

    QJsonObject msgObj;
    msgObj["msgid"] = QString::number(m_msgid++);
    msgObj["params"] = paramsObj;
    // 转换为JSON文档
    QJsonDocument doc(msgObj);
    QByteArray jsonData = doc.toJson();
    return jsonData;
}

void mqttTest::on_buttonPing_clicked()
{
    ui->buttonPing->setEnabled(false);
    m_client->requestPing();
}

void mqttTest::on_buttonClear_clicked()
{
    ui->editLog->clear();
}
