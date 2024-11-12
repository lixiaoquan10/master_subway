#ifndef MQTTTEST_H
#define MQTTTEST_H

#include <QMqttClient>
#include <QDialog>

namespace Ui {
class mqttTest;
}

class CDistribution;
class CDevice;
class mqttTest : public QDialog
{
    Q_OBJECT

public:
    explicit mqttTest(QWidget *parent = 0);
    ~mqttTest();
    void uploadDeviceInfo();
    QByteArray creatDistributionJsonData(CDistribution* distribution);
    QByteArray creatDeviceJsonData(CDevice* device);

public slots:
    void setClientPort(int p);

private slots:
    void on_buttonConnect_clicked();
    void on_buttonQuit_clicked();
    void updateLogStateChange();

    void brokerDisconnected();

    void on_buttonPublish_clicked();

    void on_buttonSubscribe_clicked();

    void on_buttonPing_clicked();

    void on_buttonClear_clicked();

private:
    Ui::mqttTest *ui;
    QMqttClient *m_client;
    qint64 m_msgid;
};

#endif // MQTTTEST_H
