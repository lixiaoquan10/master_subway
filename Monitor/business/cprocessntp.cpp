#include "cglobal.h"
#include "cprocessntp.h"
#include <arpa/inet.h>
#include <QCoreApplication>
#include <QUdpSocket>
#include <QByteArray>
#include <QDateTime>
#include <QDebug>
#include <QHostInfo>
#include <QTimeZone>


CprocessNtp::CprocessNtp(const QHostAddress& ntpServer, QUdpSocket* udpSocket)
    :m_hostAddress(ntpServer), m_udpSocket(udpSocket)
{
    if (!m_udpSocket->bind(QHostAddress(QHostAddress::Any), static_cast<quint16>(0)))
    {

    }
    // 设置 readyRead 信号槽
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &CprocessNtp::onResponseReceived);
    //定时对时
    m_ntpTimer = new QTimer();
    connect(m_ntpTimer, &QTimer::timeout, this, &CprocessNtp::slot_requestTime);
}

CprocessNtp::~CprocessNtp()
{
    delete m_udpSocket;
    delete m_ntpTimer;
}

void CprocessNtp::startNtpTimer()
{
//    QHostAddress address(m_serverAddress);
//    if(address.protocol() == QAbstractSocket::IPv4Protocol
//            || address.protocol() == QAbstractSocket::IPv6Protocol)
//    {
//        // 如果是 IP 地址
//        m_hostAddress = address;
//    }
//    else
//    {
//        // 这里假设 mqttHost 是域名并且可以通过 DNS 解析
//        QHostInfo hostInfo = QHostInfo::fromName(m_serverAddress);
//        if (!hostInfo.addresses().isEmpty())
//            m_hostAddress = hostInfo.addresses().first();
//    }
    m_ntpTimer->start(30000);
}

void CprocessNtp::slot_requestTime()
{
    // 如果没有网络连接，可以直接返回
    if (m_udpSocket->state() != QAbstractSocket::BoundState)
    {
        QString content = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss")
                + QLatin1Char('\n')
                + QLatin1String("Request NTP time failed! No BoundState")
                + QLatin1Char('\n');
        QFile file("/home/xfss/root/logfile/NTPData.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << content << '\n';
            file.close();
        }
        return;
    }
    if (m_hostAddress.isNull())
    {
        QString content = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss")
                + QLatin1Char('\n')
                + QLatin1String("Request NTP time failed! hostAddress is Null")
                + QLatin1Char('\n');
        QFile file("/home/xfss/root/logfile/NTPData.txt");
        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << content << '\n';
            file.close();
        }
        return;
    }
    // 创建 NTP 请求包
    QByteArray requestPacket(48, 0);
    requestPacket[0] = 0x1B; // 28秒的偏移，表示 NTP 客户端请求，版本号 3，模式 3（客户端请求）

    QString content = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss")
            + QLatin1Char('\n');

    // 发送数据包
    qint64 bytesWritten = m_udpSocket->writeDatagram(requestPacket, m_hostAddress, 123);
    if (bytesWritten == -1) {
        content = content + QLatin1String("Request NTP time sucessed!")
                + QLatin1Char('\n');
    } else {
        content = content + QLatin1String("Request NTP time failed!")
                + QLatin1Char('\n');
    }
    QFile file("/home/xfss/root/logfile/NTPData.txt");
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << content << '\n';
        file.close();
    }
}


void CprocessNtp::onResponseReceived()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray response;
        response.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(response.data(), response.size());

        if (response.size() >= 48) {
            // NTP时间戳从第40字节开始，长度为4字节
            uint32_t ntp_seconds = *reinterpret_cast<uint32_t*>(response.data() + 40);
            ntp_seconds = ntohl(ntp_seconds); // 转换为主机字节序
            uint32_t unix_time = ntp_seconds - 2208988800U; // 转换为 Unix 时间戳

            // 打印 NTP 时间
            QDateTime ntpDateTime = QDateTime::fromSecsSinceEpoch(unix_time);
            // 获取当前时间（系统时间）
            QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
            // 计算时间差（秒数）
            qint64 diffInSeconds = ntpDateTime.toTime_t() - currentDateTime.toTime_t();
            // 创建 UTC 时区对象
            QTimeZone utcZone("UTC");
            // 设置 QDateTime 的时区为 UTC
            ntpDateTime.setTimeZone(utcZone);
            QString content;
            // 如果偏差超过 1s，修改程序时间
            if (qAbs(diffInSeconds) >= 1)
            {

                CGlobal::instance()->TimeInterval()->setSystemTime(ntpDateTime.toString("yyyy-MM-dd HH:mm:ss"));
                content = content + QLatin1String("Set NTP time:")
                        + ntpDateTime.toString("yyyy-MM-dd HH:mm:ss")
                        + QLatin1Char('\n');
            }
            content = content + QLatin1String("NTP time:")
                    + ntpDateTime.toString("yyyy-MM-dd HH:mm:ss")
                    + QLatin1Char('\n')
                    + QLatin1String("current time:")
                    + currentDateTime.toString("yyyy-MM-dd HH:mm:ss")
                    + QLatin1Char('\n');
            QFile file("/home/xfss/root/logfile/NTPData.txt");
            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << content << '\n';
                file.close();
            }
        } else {
        }
    }
}
