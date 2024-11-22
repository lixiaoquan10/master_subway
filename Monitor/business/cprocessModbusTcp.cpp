#include "cprocessModbusTcp.h"
#include "cglobal.h"

#include "dm/ccontroller.h"
#include "dm/ccanport.h"
#include "dm/cdistribution.h"
#include "dm/cloop.h"
#include "dm/cdevice.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QApplication>
#include <QHostAddress>
#include <QMessageBox>
#include <QDebug>
#include <QDomDocument>
#include <QXmlStreamReader>

CprocessModbusTcp::CprocessModbusTcp()
{
    m_modbustcpServer = new QTcpServer(this);
    m_timer = new QTimer();
    m_disconnectTimer = new QTimer();
    m_controlTxtTimer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_serverlisten()));
    connect(m_disconnectTimer, SIGNAL(timeout()), this, SLOT(slot_handleDisconnected()));
    connect(m_controlTxtTimer, SIGNAL(timeout()), this, SLOT(slot_controlTxtFileSize()));
    m_timer->start(5000);
    m_controlTxtTimer->start(5000);
}

CprocessModbusTcp::~CprocessModbusTcp()
{
    delete m_modbustcpServer;
    delete m_modbustcpSocket;
    delete m_timer;
    delete m_disconnectTimer;
}

void CprocessModbusTcp::slot_serverlisten()
{
    qDebug() << "CprocessModbusTcp::slot_serverlisten"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(!m_modbustcpServer->listen(QHostAddress::Any, 502))
    {
        qDebug() << "Unable to start the server: " << m_modbustcpServer->errorString() << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
        return;
    }
    connect(m_modbustcpServer, SIGNAL(newConnection()), this, SLOT(slot_handleNewConnection()));
}

// ????????
void CprocessModbusTcp::slot_handleNewConnection()
{
    qDebug() << "CprocessModbusTcp::slot_handleNewConnection"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    m_modbustcpSocket = m_modbustcpServer->nextPendingConnection();  // ?????
    m_timer->stop();
    QString str = QString("modbusTcp connect: %1:%2").arg(m_modbustcpSocket->peerAddress().toString()).arg(m_modbustcpSocket->peerPort());
    //??????????txt??
//    CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", str);
    connect(m_modbustcpSocket, SIGNAL(readyRead()), this, SLOT(slot_readClientData()));  // ???????
    connect(m_modbustcpSocket, SIGNAL(disconnected()), this, SLOT(slot_handleDisconnected()));
    connect(m_modbustcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
}

void CprocessModbusTcp::onSocketError(QAbstractSocket::SocketError error)
{
    qDebug() << "CprocessModbusTcp::onSocketError"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if (m_modbustcpSocket)
    {
        qDebug() << "modbusTcp error occurred: " << m_modbustcpSocket->errorString();
        qDebug() << "Error code: " << error;
        QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
        QString dataWithTimestamp;
        dataWithTimestamp = "(modbusTcp error occurred:" + timestamp + ")" + '\n' + m_modbustcpSocket->errorString();
//        CGlobal::instance()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
    }
}


// ???????
void CprocessModbusTcp::slot_readClientData()
{
    qDebug() << "CprocessModbusTcp::slot_readClientData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if (m_modbustcpSocket)
    {
        QByteArray array = m_modbustcpSocket->readAll();  // ???????
        // ???????
        qDebug() << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
        qDebug() << array;

        // ??????????
        m_receiveBuff.append(array);
        // ?????
        processReceiveData(m_receiveBuff);
    }
}


void CprocessModbusTcp::processReceiveData(QByteArray array)
{
    qDebug() << "CprocessModbusTcp::processReceiveData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString dataWithTimestamp;
    dataWithTimestamp = "(Receive:" + timestamp + ")" + '\n' + array.toHex();
    //??????????txt??
//    CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
    if(array.count() < 12)
        return;
    if(array.at(0) == char(0) && array.at(1) == char(0) &&
            array.at(2) == char(0) && array.at(3) == char(0) &&
            array.at(4) == char(0))
    {
        m_receiveBuff.remove(0,12);
//        int length = array.at(5);
        char typeNumber = array.at(7);
        char canportAddress = array.at(6)+2;
        if(typeNumber == 0x10)
        {
            if(array.at(8) == 0x00 && array.at(9) == 0x00)
            {
                if(array.at(11) == 0x01)
                {
                    CGlobal::instance()->TopToolBar()->resetSystem();
                }
                else if(array.at(11) == 0x02)
                {
                    CGlobal::instance()->m_isEmergency = true;
                    CMsgNull m_MsgNUll;
                    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_CancelMute, &m_MsgNUll);
                    CGlobal::instance()->DataProcessing()->setSoundIcon(true);
                    if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
                        return;
                    CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
                    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_EmergencyStart, &m_MsgNUll);
                }
            }
        }
        else if(typeNumber == 0x03)
        {
            int distributionAddress = array.at(8)/8+1;
            int loopAddress = array.at(8)%8;
            int deviceAddress = array.at(9);
            int number = array.at(10)<<8 | array.at(11);
            bool startflag = false;
            int count = 0;
            QByteArray deviceArray;
            for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
            {
                if(count >= number)
                    break;
                CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
                if(!canport)
                    continue;
                for(int j=1; j<=32; j++)
                {
                    if(count >= number)
                        break;
                    QApplication::processEvents();
                    CDistribution* distribution = canport->distributionByAddress(j);
                    if(!distribution)
                        continue;
                    for(int l=1; l<=8; l++)
                    {
                        if(count >= number)
                            break;
                        CLoop* loop = distribution->loopByAdd(l);
                        if(!loop)
                            continue;
                        for(int m=1; m<=255; m++)
                        {
                            QApplication::processEvents();
                            if((i == canportAddress) && (j == distributionAddress) &&
                                    (l == loopAddress) && (m == deviceAddress))
                                startflag = true;
                            if(startflag)
                            {
                                CDevice* device = loop->deviceByAdd(m);
                                if(!device)
                                    continue;
                                uint8_t status = 0;
                                uint8_t comFault = 0;
                                uint8_t lightFault = 0;
                                uint8_t batFault = 0;
                                uint8_t emergency = 0;
                                if(device->getDeviceCommunicationFault())
                                    comFault = 0x01;
                                if(device->deviceValue(DEVICE_VALUE_LIGHT) == "????")
                                    lightFault = 0x01;
                                if(device->deviceValue(DEVICE_VALUE_BATTERYPOWER).toString() == "????" ||
                                        device->deviceValue(DEVICE_VALUE_BATTERYPOWER).toString() == "????" ||
                                        device->deviceValue(DEVICE_VALUE_BATTERYPOWER).toString() == "?????")
                                    batFault = 0x01;
                                if((distribution->getemergencyStatus() || device->deviceValue(DEVICE_VALUE_EMERGENCY) == "??"))
                                    emergency = 0x01;
                                status |= comFault;
                                status |= lightFault<<1;
                                status |= batFault<<2;
                                status |= emergency<<3;
                                deviceArray.append(char(0));
                                deviceArray.append(status);
                                count ++;
                                if(count >= number)
                                    break;
                            }

                        }
                    }
                }
            }
            QByteArray data;
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(count*2+3));
            data.append(canportAddress-2);
            data.append(0x03);
            data.append(char(count*2));
            data.append(deviceArray);
            replySendData(data);
        }
        else if(typeNumber == 0x04)
        {
            int distributionAddress = array.at(9);
            int number = array.at(10)<<8 | array.at(11);
            bool startflag = false;
            int count = 0;
            QByteArray distributionArray;
            for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
            {
                if(count >= number)
                    break;
                CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
                if(canport)
                {
                    for(int j=1; j<=32; j++)
                    {
                        QApplication::processEvents();
                        if((i == canportAddress) && (j == distributionAddress))
                            startflag = true;
                        if(startflag)
                        {
                            CDistribution* distribution = canport->distributionByAddress(j);
                            if(distribution)
                            {
                                uint8_t status = 0;
                                uint8_t comFault = 0;
                                uint8_t mainpowerFault = 0;
                                uint8_t batpowerFault = 0;
                                uint8_t emergency = 0;
                                if((distribution->getStatus(OBJS_DistributionCommunicationFault) == 1) || (!distribution->isDistributionOnline()))
                                    comFault = 0x01;
                                if(distribution->getmainPowerFault())
                                    mainpowerFault = 0x01;
                                if(distribution->getbackupPowerFault())
                                    batpowerFault = 0x01;
                                if(distribution->getemergencyStatus())
                                    emergency = 0x01;
                                status |= comFault;
                                status |= mainpowerFault<<1;
                                status |= batpowerFault<<2;
                                status |= emergency<<3;
                                distributionArray.append(char(0));
                                distributionArray.append(status);
                                count ++;
                                if(count >= number)
                                    break;
                            }
                        }
                    }
                }
            }
            QByteArray data;
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(0));
            data.append(char(count*2+3));
            data.append(canportAddress-2);
            data.append(0x04);
            data.append(char(count*2));
            data.append(distributionArray);
            replySendData(data);
        }
    }
    else
        m_receiveBuff.clear();
}

void CprocessModbusTcp::replySendData(QByteArray data)
{
    qDebug() << "CprocessModbusTcp::replySendData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    qDebug() << data;

    qint64 datalength = m_modbustcpSocket->write(data);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz");
    QString dataWithTimestamp;
    qint64 bytesWaiting = m_modbustcpSocket->bytesToWrite();
    if (bytesWaiting > 0)
    {
        if(m_modbustcpSocket->waitForBytesWritten())
        {
            dataWithTimestamp = "(Send:" + timestamp +" length:"+ QString::number(datalength) + ")" + '\n' + data.toHex();
            //??????????txt??
//            CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
        }
        else
        {
            dataWithTimestamp = "(Send Failed:" + timestamp +" length:"+ QString::number(datalength) + ")" + '\n' + data.toHex();
            //??????????txt??
//            CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", dataWithTimestamp);
        }
    }
}


// ?????????
void CprocessModbusTcp::slot_handleDisconnected()
{
    qDebug() << "CprocessModbusTcp::slot_handleDisconnected"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if (m_modbustcpSocket)
    {
        m_modbustcpSocket->deleteLater(); // ?????socket??
        QString str = QString("modbusTcp????: %1:%2").arg(m_modbustcpSocket->peerAddress().toString()).arg(m_modbustcpSocket->peerPort());
        //??????????txt??
//        CGlobal::instance()->processSocket()->saveDataToTxt("/home/xfss/root/logfile/modbusTcpData.txt", str);
        m_timer->start(1000);
    }
}

void CprocessModbusTcp::slot_controlTxtFileSize()
{
    qDebug() << "CprocessModbusTcp::slot_controlTxtFileSize"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    //?????????1M
//    controlTxtFileSize("/home/xfss/root/logfile/modbusTcpData.txt",1024*1024);
}
