#ifndef DLGTIMEINTERVAL_H
#define DLGTIMEINTERVAL_H

#include "cglobal.h"
#include <QPainter>
#include <QHostInfo>
#include "business/cprocessmqtt.h"
#include "business/cprocessntp.h"

namespace Ui {
class dlgTimeInterval;
}

class TriangleButton : public QPushButton
{
public:
    TriangleButton(const QIcon &icon, QWidget *parent = NULL)
        : QPushButton(parent), m_icon(icon)
    {
        setIcon(icon);
        setIconSize(QSize(32, 32)); // 设置图标大小
        setFixedSize(32, 32); // 设置按钮固定大小
    }

protected:
    void paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        QPainter painter(this);
        // 绘制图标
        if (!m_icon.isNull()) {
            QSize iconSize = m_icon.actualSize(QSize(32, 32)); // 使用图标的实际大小
            int x = (width() - iconSize.width()) / 2;
            int y = (height() - iconSize.height()) / 2;
            painter.drawPixmap(x, y, m_icon.pixmap(iconSize));
        }

        // 设置绘制笔的颜色和样式
        painter.setPen(Qt::NoPen); // 设置绘制笔为无边框
        painter.setBrush(Qt::transparent); // 设置绘制刷为透明
        // 绘制三角形
        QPolygonF triangle;
        triangle << QPointF(0, height()) << QPointF(width(), height()) << QPointF(width() / 2, 0);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawPolygon(triangle);
    }
private:
    QIcon m_icon;
};

class dlgTimeInterval : public QDialog
{
    Q_OBJECT

public:
    explicit dlgTimeInterval(QWidget *parent = 0);
    ~dlgTimeInterval();
    void systemChanged();
    void updateVersion();
    void updateSqliteData();
    void updateWLANData();
    void updateAdminPuttonGeometry();
    void saveSqliteData(QString ParamName, QString ParamValue);
    void setHost1AddressPort(QString ip, QString port);
    void setSystemTime(QString dateTime);
    void setUseTime(int usetime);
    void setIpAndTimeHide(bool enable);
    bool isWLANChanged();
    bool isHost1AddressChanged();
    bool isHost2AddressChanged();
    QString getGateway(const QString &interfaceName);
    void setWLANData();

    void setTestLinkageComResult(QString str);
    void setLinkageComStatus(QString str);
    void uploadStatusToMqtt();
    //配置MQTT通讯网络
    void configureRoute(QString wlanName, QString wlanIP,
                        QString wlanGateway, QString mqttIP);

    QString m_getTmpip1;
//    QString m_getTmpgateway1;
    QString m_getTmpmask1;

    QString m_getTmpip2;
//    QString m_getTmpgateway2;
    QString m_getTmpmask2;

    QString m_dateTimeStr;
private slots:

    void on_pushButton_UseTime_clicked();

    void on_m_ButtonTimeSet_clicked();

    void on_pingButton_clicked();

    void slot_timeFinished();

    void slot_pingFinished(double successRate);

    void slot_wlanFinished(QString wlanIP1, QString wlanGateway1,
                           QString wlanName2, QString wlanIP2, QString wlanGateway2);

    void slot_ipsetFinished();

    void on_TwinkleCheckBox_clicked();

    void on_EnergyCheckBox_clicked();

    void on_pushButton_saveHost1Address_clicked();

    void on_pushButton_saveHost2Address_clicked();

    void on_pushButton_can1can2_clicked();

    void on_pushButton_can3can4_clicked();

    void on_allStartCheckBox_clicked();

    void on_onlyStartPageCheckBox_clicked();

    void on_onlyStartGroupCheckBox_clicked();

    void on_Can4CheckBox_clicked();

    void on_Can8CheckBox_clicked();

    void on_triangleButton_clicked();

    void on_pushButton_can5can6_clicked();

    void on_pushButton_can7can8_clicked();

    void on_singleWLAN_clicked();

    void on_doubleWLAN_clicked();

    void on_pushButton_saveWlan_clicked();

    void on_autoPageCheckBox_clicked();

    void on_testLinkageComButton_clicked();

    void slot_testComResult();

    void on_pushButton_testLinkageCom_clicked();

    void on_emergencyOnlyDistributionCheckBox_clicked();

    void on_pushButton_phoneNumber_clicked();

    void on_pushButton_lampForbidList_clicked();

    void on_pushButton_firepointNumber_clicked();

    void on_DirectionTwinkleOneCheckBox_clicked();

    void on_DirectionTwinkleDoubleCheckBox_clicked();

    void on_TwinkleConfigCheckBox_clicked();

    void on_pushButton_lamptwinkleconfig_clicked();

    void on_forbidARTUCheckBox_clicked();

    void on_ARTU079KCheckBox_clicked();

    void on_ARTU079KJCheckBox_clicked();

    void on_ARTU426CheckBox_clicked();

    void on_pushButton_ModbusTCP_clicked();

    void slot_setCom1Status(bool enable);
    void slot_setCom2Status(bool enable);
    void slot_setHostControlMsg(int type);

    void onMqttSocketConnected1();
    void onMqttSocketConnected2();

    void slot_setNTPprocess(QHostAddress convertIP);

private:
    Ui::dlgTimeInterval *ui;
    bool isThreadRunning;
    TriangleButton *m_triangleButton;

    QTcpSocket *m_tcpSocket1;
    CprocessMqtt *m_processMqtt1;
    QMqttClient *m_mqttClient1;
    QThread *m_mqttThread1;

    QTcpSocket *m_tcpSocket2;
    CprocessMqtt *m_processMqtt2;
    QMqttClient *m_mqttClient2;
    QThread *m_mqttThread2;

    CprocessNtp *m_processNtp;
    QUdpSocket *m_ntpClient;
    QThread *m_ntpThread;

signals:
    void m_Checked_signal(bool checked);
    void uploadStatusToMQTT();
};

class timeThread : public QThread
{
    Q_OBJECT
public:
    explicit timeThread(QObject *parent = NULL)
        : QThread(parent)
    {
    }
signals:
    void timeFinished();
protected:
    void run();
};

class ipsetThread : public QThread
{
    Q_OBJECT
public:
    explicit ipsetThread(QObject *parent = NULL)
        : QThread(parent)
    {
    }
signals:
    void ipsetFinished();
protected:
    void run();
};

class pingThread : public QThread
{
    Q_OBJECT
public:
    explicit pingThread(QObject *parent = NULL)
        : QThread(parent)
    {
    }
    void setpingIP(QString ip) { m_pingIP = ip; }
signals:
    void pingFinished(double successRate);
protected:
    void run();
private:
    QString m_pingIP;
};

class wlanThread : public QThread
{
    Q_OBJECT
public:
    explicit wlanThread(QObject *parent = NULL)
        : QThread(parent)
    {
    }
    QString getGateway(const QString &interfaceName)
    {
        QString gateway;

        QProcess process;
        // 构建命令，只获取特定接口的网关信息
        QString command = "ip route show dev " + interfaceName + " default";
        process.start(command);
        process.waitForFinished();

        QString result = process.readAllStandardOutput();
        QStringList lines = result.split("\n");

        foreach (QString line, lines) {
            if (line.contains("default via")) {
                QStringList parts = line.split(" ");
                gateway = parts.at(2);
                break;
            }
        }
        return gateway;
    }
    void configureRoute(QString wlanName, QString wlanIP, QString wlanGateway, QString mqttIP)
    {
        QProcess process;
        // 获取网关
        if(wlanGateway == "")
        {
            QStringList ipParts = wlanIP.split('.');
            if (ipParts.size() == 4) {
                ipParts[3] = "1";  // 设置网关的最后一部分为 '1'
                wlanGateway = ipParts.join('.');
            }
        }
        QHostAddress address(mqttIP);
        if(address.protocol() == QAbstractSocket::IPv4Protocol
                || address.protocol() == QAbstractSocket::IPv6Protocol)
        {
            // 如果是 IP 地址
            QString args = "ip route add " + mqttIP + " via " + wlanGateway + " dev " + wlanName;
            process.start(args);
        }
        else
        {
            // 这里假设 mqttHost 是域名并且可以通过 DNS 解析
            QHostInfo hostInfo = QHostInfo::fromName(mqttIP);
            if (!hostInfo.addresses().isEmpty()) {
                QString resolvedIP = hostInfo.addresses().first().toString();
                QString args = "ip route add " + resolvedIP + " via " + wlanGateway + " dev " + wlanName;
                process.start(args);
            }
        }

        // 等待进程完成
        process.waitForFinished();
    }
    void convertAddress(QString ip)
    {
        QHostAddress address(ip);
        if(address.protocol() != QAbstractSocket::IPv4Protocol
                || address.protocol() != QAbstractSocket::IPv6Protocol)
        {
            // 这里假设 mqttHost 是域名并且可以通过 DNS 解析
            QHostInfo hostInfo = QHostInfo::fromName(ip);
            if (!hostInfo.addresses().isEmpty()) {
                QString convertIP = hostInfo.addresses().first().toString();
                emit convertAddressFinished(convertIP);
            }
        }
        else
            emit convertAddressFinished(ip);
    }
signals:
    void wlanFinished(QString wlanIP1, QString wlanGateway1,
                      QString wlanName2, QString wlanIP2, QString wlanGateway2);
    void convertAddressFinished(QString ip);
protected:
    void run();
private:

};


class convertIPThread : public QThread
{
    Q_OBJECT
public:
    explicit convertIPThread(QObject *parent = NULL)
        : QThread(parent)
    {
    }
    void setConvertIP(QString ip) { m_convertIP = ip; }
signals:
    void convertAddressFinished(QHostAddress ip);
protected:
    void run()
    {
        QHostAddress IPaddress(m_convertIP);
        if(IPaddress.protocol() != QAbstractSocket::IPv4Protocol
                || IPaddress.protocol() != QAbstractSocket::IPv6Protocol)
        {
            // 这里假设 mqttHost 是域名并且可以通过 DNS 解析
            QHostInfo hostInfo = QHostInfo::fromName(m_convertIP);
            if (!hostInfo.addresses().isEmpty()) {
                IPaddress = hostInfo.addresses().first();
            }
        }
        emit convertAddressFinished(IPaddress);
    }
private:
    QString m_convertIP;
};

#endif // DLGTIMEINTERVAL_H
