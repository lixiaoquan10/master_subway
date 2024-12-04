#ifndef CPROCESSNTP_H
#define CPROCESSNTP_H
#include <QCoreApplication>
#include <QTimer>
#include <QUdpSocket>
#include <QByteArray>
#include <QDateTime>

class CprocessNtp  : public QObject
{
    Q_OBJECT
public:
    explicit CprocessNtp(const QHostAddress& ntpServer, QUdpSocket* udpSocket);
    ~CprocessNtp();
    void startNtpTimer();
private slots:
    void slot_requestTime();
    void onResponseReceived();
private:
    QHostAddress m_hostAddress;
    QUdpSocket *m_udpSocket;
    QTimer* m_ntpTimer;             //对时定时器
};
#endif // CPROCESSNTP_H
