#ifndef CPROCESSMQTT_H
#define CPROCESSMQTT_H
#include <QCoreApplication>
#include <QtMqtt/QMqttClient>
#include <QTimer>

class CController;
class CDistribution;
class CLoop;
class CDevice;
class CObject;
class CprocessMqtt  : public QObject
{
    Q_OBJECT
public:
    explicit CprocessMqtt(QMqttClient *mqttClient = 0);
    ~CprocessMqtt();
    QMqttClient *mqttClient() { return m_mqttClient; }
    QByteArray creatControllerJsonData(CController* controller);              //创建控制器信息JSon数据
    QByteArray creatDistributionJsonData(CDistribution* distribution);        //创建集中电源信息JSon数据
    QByteArray creatLoopJsonData(CLoop* loop);                                //创建回路信息JSon数据
    QByteArray creatDeviceJsonData(CDevice* device);                          //创建灯具信息JSon数据
    void uploadAllDeviceInfo();                                               //上传所有设备信息JSon数据

    QByteArray creatControllerStatusJsonData(CController* controller);        //创建控制器状态JSon数据
    QByteArray creatDistributionStatusJsonData(CDistribution* distribution);  //创建集中电源状态JSon数据
    QByteArray creatLoopStatusJsonData(CLoop* loop);                          //创建回路状态JSon数据
    QByteArray creatDeviceStatusJsonData(CDevice* device);                    //创建灯具状态JSon数据
    void subscribeComTopic();                                  //订阅服务器相关主题

    void subscribeToTopic(const QString &topic);               //订阅某个主题
    void manualConnectToBroker(const QString &host, quint16 port);   //连接到服务器
    void manualDisconnectToBroker();                                 //断开连接

    void replyHostControl(QString msgid, bool isTrue);   //回复服务器控制指令

    void saveDataToFile(QString fileName, QString data);   //保存到文件

    void clearSendData();        // 清理发送相关数据

public slots:
    bool publishMessage(const QString &topic, const QByteArray &message);                     //发送数据
    void slot_updateLogStateChange();                                                         //连接状态变化
    void slot_brokerDisconnected();                                                           //服务器断开连接
    void slot_handleMessageReceived(const QByteArray &message, const QMqttTopicName &topic);  //数据接收
    void slot_pingResponse();                                                                 //ping回复
    void slot_requestPing();                                                                  //重连ping
    void slot_reconnectToBroker();                                                            //重连服务器
    void slot_messageStatusChanged(quint16 packetId, QMqtt::MessageStatus status);            //发送消息状态变化   （发送完成）
    void slot_ResendTimerTimeout();                                                           //发送数据超时处理
    void slot_sendDeviceStatusMsg(CObject* object, bool isDistributionEmergencyOrFault = false);        //设备状态信息上传
    void slot_uploadAllDeviceStatus();                     //所有设备状态信息上传
signals:
    void connectStatus(bool status);
    void hostControlMsg(int type);

private:
    QMqttClient *m_mqttClient;
    QString m_host;
    quint16 m_port;
    QString m_productKey;
    QString m_deviceSN;
    QString m_deviceSecret;
    uint32_t m_msgid;                //数据计时
    QTimer* m_pingTimer;             //心跳定时器
    QTimer* m_reconnectTimer;        //重连定时器
    QMap<quint16, QTimer*> m_resendTimers;     // 维护一个重发定时器列表
    QMap<quint16, QPair<QByteArray, QString>> m_sendMessages;  // 维护每个 packetId 对应的消息内容和主题
    const int m_resendTimeout = 3000;       // 3秒超时
    bool m_isPingRespond;                   // 是否有回复
    int m_pingNoRespondCount;               // 未回复次数

    int m_reconnectInterval;                     // 当前重连时间间隔（毫秒）
    const int m_initialReconnectInterval = 3000; // 初始重连时间间隔
    const int m_maxReconnectInterval = 24000;    // 最大重连时间间隔（例如24s）
};
#endif // CPROCESSMQTT_H
