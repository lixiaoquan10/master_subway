#ifndef DLGTIMEINTERVAL_H
#define DLGTIMEINTERVAL_H

#include "cglobal.h"
#include <QPainter>
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

    QString m_getTmpip1;
    QString m_getTmpgateway1;
    QString m_getTmpmask1;

    QString m_getTmpip2;
    QString m_getTmpgateway2;
    QString m_getTmpmask2;

    QString m_dateTimeStr;
private slots:

    void on_pushButton_UseTime_clicked();

    void on_m_ButtonTimeSet_clicked();

    void on_pingButton_clicked();

    void slot_timeFinished();

    void slot_pingFinished(double successRate);

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

private:
    Ui::dlgTimeInterval *ui;
    bool isThreadRunning;
    TriangleButton *m_triangleButton;

    CprocessMqtt *m_processMqtt1;
    QMqttClient *m_mqttClient1;
    QThread *m_mqttThread1;

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

#endif // DLGTIMEINTERVAL_H
