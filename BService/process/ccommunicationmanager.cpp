#include "ccommunicationmanager.h"
#include "packageanalyzer.h"
#include "cserialport.h"
#include "cprocesscontroller.h"
#include "cprocessdistribution.h"
#include "cglobal.h"
#include "struct.h"
#include "struct/cmsgnull.h"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#define CANDATALEN 15

CCommunicationManager::CCommunicationManager(QObject *parent) :
    QObject(parent),m_isDebug(false)
{

    connect(&m_ledReciveTimer, SIGNAL(timeout()), this, SLOT(handleLedReciveData()));
    connect(&m_linkageReciveTimer, SIGNAL(timeout()), this, SLOT(handleLinkageReciveData()));

    connect(&m_testReciveTimer, SIGNAL(timeout()), this, SLOT(handleTestReciveData()));

    connect(&m_Can1ReciveTimer, SIGNAL(timeout()), this, SLOT(handleCan1ReciveData()));
    connect(&m_Can2ReciveTimer, SIGNAL(timeout()), this, SLOT(handleCan2ReciveData()));

    m_ledReciveTimer.start(30);
    m_linkageReciveTimer.start(30);

    m_testReciveTimer.start(30);

    m_Can1ReciveTimer.start(15);
    m_Can2ReciveTimer.start(15);

    led_reciveData = 0;
    CAN1_reciveData = 0;
    CAN2_reciveData = 0;

    m_isSerialportNameSeted = false;

    m_timerResetLinkageFlag = new QTimer(this);
    connect(m_timerResetLinkageFlag, SIGNAL(timeout()), this, SLOT(slot_LinkageFlagReset()));
    m_timerResetLinkageFlag->start(3000);

    m_timerARTUDIsend = new QTimer(this);
    connect(m_timerARTUDIsend, SIGNAL(timeout()), this, SLOT(slot_ARTUDIsend()));
}

CCommunicationManager::~CCommunicationManager()
{
    foreach(QString lineName,m_hashCommunicationLine.keys()){
        m_hashCommunicationLine[lineName]->destroy();
        m_hashCommunicationLine.remove(lineName);
    }
    delete m_timerResetLinkageFlag;
}

void CCommunicationManager::slot_LinkageFlagReset()
{
    if(!CGlobal::instance()->m_isReceiveLinkageData)
        CGlobal::instance()->m_isReceiveLinkageData = true;
}

void CCommunicationManager::slot_ARTUDIsend()
{
    if(!CGlobal::instance()->m_isReceiveLinkageData)
        return;
    if(ARTUDIlists.isEmpty())
    {
        m_timerARTUDIsend->stop();
        return;
    }
    QHash<QString, QVariant> controlDomain;
    controlDomain.insert("communicationType",CT_LinkageCard);
    CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, ARTUDIlists.at(0));
    ARTUDIlists.removeAt(0);
}

void CCommunicationManager::setTestLinkageCom(bool enable)
{
    qDebug() << "CCommunicationManager::setTestLinkageCom" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(enable)
        m_testReciveTimer.start(30);
    else
    {
        m_testReciveTimer.stop();
        CGlobal::instance()->m_linkageTestStatus = 0;
    }
}

void CCommunicationManager::setLinkageBaudRate(QString baudrateString)
{
    qDebug() << "CCommunicationManager::setLinkageBaudRate" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString linename = "linkagecard";
    long baudrate = baudrateString.toLong(); // 将QString转换为整数
    if(!m_hashCommunicationLine.contains(linename)) return;
    CSerialPort* pSerialPort = m_hashCommunicationLine[linename]->pSerialPort;

    if(pSerialPort)
    {
        pSerialPort->serialPort()->close();
        QString portName = pSerialPort->serialPort()->portName();
        pSerialPort->serialPort()->setPortName(portName);
        pSerialPort->serialPort()->setBaudRate((BaudRateType)baudrate);
        QObject::connect(pSerialPort->serialPort(), SIGNAL(readyRead()), pSerialPort->serialPort(), SLOT(doReciveData()));
        if(!pSerialPort->serialPort()->open(QIODevice::ReadWrite))
        {

        }
    }
}

int CCommunicationManager::getPortFromCommunicationType(int type)
{
    qDebug() << "CCommunicationManager::getPortFromCommunicationType" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    switch(type)
    {
        case CT_CanCard1:
            return 1;
        case CT_CanCard2:
            return 0;
        case CT_LedCard:
            return 2;
        case CT_LinkageCard:
            return 3;
        case CT_TestCard:
            return 4;
        case CT_NoCard:
            return 5;
        case CT_FASCard:
            return 6;
        default:
            return 10;
    }
}

bool CCommunicationManager::createCommunicationLine(const QString &lineName, int type)
{
    qDebug() << "CCommunicationManager::createCommunicationLine" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(m_hashCommunicationLine.contains(lineName)){
        return false;
    }
    CSerialPort *pSerialPort ;
    if (lineName == "cancard1" || lineName == "cancard2")
            pSerialPort = new CSerialPort(0, 115200);
    else if (lineName == "ledcard")
        pSerialPort = new CSerialPort(0, 19200);
    else if (lineName == "linkagecard")
        pSerialPort = new CSerialPort(0, 19200);
    else if (lineName == "testcard")
        pSerialPort = new CSerialPort(0, 19200);
    else
        pSerialPort = new CSerialPort();
    pSerialPort->setName(lineName);
    connect(pSerialPort, SIGNAL(sig_ReciveData(const QString&,const QByteArray&)),
            this, SLOT(doReciveData(const QString&,const QByteArray&)));

    connect(this, SIGNAL(sig_ReceivedPacket(int)), pSerialPort, SLOT(handleConfirmationPacket(int)));

    pSerialPort->setDebugOut(m_isDebug);
    CCommunicationLine *communicationLine = new CCommunicationLine();
    communicationLine->pSerialPort = pSerialPort;
    communicationLine->nPort = getPortFromCommunicationType(type);
    m_hashCommunicationLine.insert(lineName,communicationLine);
    return true;
}

void CCommunicationManager::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

bool CCommunicationManager::removeCommunicationLine(const QString& lineName)
{
    if(m_hashCommunicationLine.contains(lineName)){
        m_hashCommunicationLine[lineName]->destroy();
        m_hashCommunicationLine.remove(lineName);
        return true;
    }else{
        return false;
    }
}

bool CCommunicationManager::open(const QString &lineName)
{
    qDebug() << "CCommunicationManager::open" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(m_hashCommunicationLine.contains(lineName)){
        CCommunicationLine* line = m_hashCommunicationLine[lineName];
        int result = line->pSerialPort->open(line->nPort);
        qDebug() << "CCommunicationManager::open, lineName is " << lineName << ",open result is " << result << ",port is " << line->nPort ;

        if(result == 1){
            return true;
        }else{
            return false;
        }

    }else{
        return false;
    }
}

bool CCommunicationManager::isActive(const QString &lineName) const
{
    if(m_hashCommunicationLine.contains(lineName)){
        return m_hashCommunicationLine[lineName]->pSerialPort->isActive();
    }else{
        return false;
    }
}

bool CCommunicationManager::close(const QString &lineName)
{
    qDebug() << "CCommunicationManager::close" << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(m_hashCommunicationLine.contains(lineName)){
        int result = m_hashCommunicationLine[lineName]->pSerialPort->close();
        if(result == 1){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void CCommunicationManager::doReciveData(const QString &lineName,const QByteArray& data)
{
    if(m_hashCommunicationLine.contains(lineName)){
        m_hashCommunicationLine[lineName]->reciveData.append(data);
    }
}

bool CCommunicationManager::setTimeOut(const QString& lineName, int timeOut)
{
    if(m_hashCommunicationLine.contains(lineName)){
        m_hashCommunicationLine[lineName]->pSerialPort->setTimeOut(timeOut);
        return false;
    }else{
        return false;
    }
}

int CCommunicationManager::getTimeOut(const QString& lineName) const
{
    if(m_hashCommunicationLine.contains(lineName)){
        return m_hashCommunicationLine[lineName]->pSerialPort->getTimeOut();
    }else{
        return -1;
    }
}

void CCommunicationManager::setDebugOut(bool isDebug)
{
    m_isDebug=isDebug;
    foreach(CCommunicationLine* lineObj, m_hashCommunicationLine){
        CSerialPort* pSerialPort = lineObj->pSerialPort;
        if(pSerialPort){
            pSerialPort->setDebugOut(m_isDebug);
        }
    }
}

/*
================
slot CCommunicationManager::updataRecentSerialNumber
================
*/
void CCommunicationManager::updataRecentSerialNumber(const QString &name, int nSerialNumber)
{
    if(m_hashCommunicationLine.contains(name)){
        m_hashCommunicationLine[name]->recentRespondSerialNumber = nSerialNumber;
    }
}



/*
================
timer slot CCommunicationManager::handleReciveData
================
*/
void CCommunicationManager::handleLedReciveData()
{
    CSerialPort* pSerialPort = m_hashCommunicationLine["ledcard"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["ledcard"]->reciveData;
    if (reciveData.isEmpty())
        return;
    if(pSerialPort){
        if (reciveData.size() < 47 || reciveData.at(0) != 0x55 || reciveData.at(1) != 0x13) {
            reciveData.clear();
            return;
        }
        char sum = 0;
        for (int ix = 0; ix < 46; ix++)
            sum += reciveData.at(ix);
        if (reciveData.at(46) != sum) {
            reciveData.clear();
            return;
        }
//        QString data = "handleLedReciveData:  " + reciveData.left(47).toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
//        QFile file("/home/xfss/root/logfile/LedReciveData.txt");

//        if (file.open(QIODevice::Append | QIODevice::Text))
//        {
//            QTextStream stream(&file);
//            stream << data << '\n';
//            file.close();
//        }
        m_isSerialportNameSeted = true;
        QByteArray tmpByteArray;
        tmpByteArray.append(reciveData.at(2));
        tmpByteArray.append(reciveData.at(6));
        tmpByteArray.append(reciveData.at(7));
        tmpByteArray.append(reciveData.at(9));
        tmpByteArray.append(reciveData.at(10));
        tmpByteArray.append(reciveData.at(14));
        tmpByteArray.append(reciveData.at(15));
        tmpByteArray.append(reciveData.at(16));
        tmpByteArray.append(reciveData.at(17));
        tmpByteArray.append(reciveData.at(18));
        tmpByteArray.append(reciveData.at(19));
        tmpByteArray.append(reciveData.at(20));
        reciveData.clear();
        QHash<QString, QVariant> controlDomain;
        controlDomain.insert("communicationType",CT_LedCard);
        CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
    }
}

void CCommunicationManager::handleLinkageReciveData()
{
    CSerialPort* pSerialPort = m_hashCommunicationLine["linkagecard"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["linkagecard"]->reciveData;
    if (reciveData.isEmpty())
        return;
    if(pSerialPort)
    {
        //检测到灯键板通讯
        if (reciveData.size() >= 47 && reciveData.at(0) == 0x55  && reciveData.at(1) == 0x13)
        {
            char sum = 0;
            for (int ix = 0; ix < (47-1); ix++)
            {
               sum += reciveData.at(ix);
            }
            //校验和正确
            if (reciveData.at(46) == sum)
            {
                CSerialPort* pSerialPortLed = m_hashCommunicationLine["ledcard"]->pSerialPort;
                QString  data1 = "oldledPortName:  " + pSerialPortLed->serialPort()->portName() + "\n" +
                                "oldlinkagePortName:  " + pSerialPort->serialPort()->portName() + "\n" +
                                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                //关闭串口
                pSerialPort->serialPort()->close();
                pSerialPortLed->serialPort()->close();
                //交换串口名称
                QString ledPortName = pSerialPortLed->serialPort()->portName();
                BaudRateType ledbaudRate = pSerialPortLed->serialPort()->baudRate();
                QString linkagePortName = pSerialPort->serialPort()->portName();
                BaudRateType linkagebaudRate = pSerialPort->serialPort()->baudRate();
                pSerialPort->serialPort()->setPortName(ledPortName);
                pSerialPort->serialPort()->setBaudRate(linkagebaudRate);
                pSerialPortLed->serialPort()->setPortName(linkagePortName);
                pSerialPortLed->serialPort()->setBaudRate(ledbaudRate);
                QObject::connect(pSerialPort->serialPort(), SIGNAL(readyRead()), pSerialPort->serialPort(), SLOT(doReciveData()));
                QObject::connect(pSerialPortLed->serialPort(), SIGNAL(readyRead()), pSerialPortLed->serialPort(), SLOT(doReciveData()));
                // 重新打开串口
                if (pSerialPort->serialPort()->open(QIODevice::ReadWrite)) {
                    data1 =data1 + "串口重新打开成功" + "\n";
                    // 连接信号与槽等相关操作
                }  else {
                    data1 =data1 + "串口重新打开失败：" + pSerialPort->serialPort()->errorString() + "\n";
                }
                // 重新打开串口
                if (pSerialPortLed->serialPort()->open(QIODevice::ReadWrite)) {
                    data1 =data1 + "串口重新打开成功" + "\n";
                    // 连接信号与槽等相关操作
                }  else {
                    data1 =data1 + "串口重新打开失败：" + pSerialPort->serialPort()->errorString() + "\n";
                }

                data1 =data1 + "newledPortName:  " + pSerialPortLed->serialPort()->portName() + "\n" +
                                "newlinkagePortName:  " + pSerialPort->serialPort()->portName() + "\n" +
                                QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file1("/home/xfss/root/logfile/portName.txt");

                if (file1.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file1);
                    stream << data1 << '\n' << '\n';
                    file1.close();
                }

                m_isSerialportNameSeted = true;
                QByteArray tmpByteArray;
                tmpByteArray.append(reciveData.at(2));
                tmpByteArray.append(reciveData.at(6));
                tmpByteArray.append(reciveData.at(7));
                tmpByteArray.append(reciveData.at(9));
                tmpByteArray.append(reciveData.at(10));
                tmpByteArray.append(reciveData.at(14));
                tmpByteArray.append(reciveData.at(15));
                tmpByteArray.append(reciveData.at(16));
                tmpByteArray.append(reciveData.at(17));
                reciveData.clear();
                QHash<QString, QVariant> controlDomain;
                controlDomain.insert("communicationType",CT_LedCard);
                CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
            }
            else
            {
                reciveData.clear();
            }
        }
        //火报通讯USB接口测试
        else if(reciveData.count() == 6 && reciveData.at(0) == 0x55  && reciveData.at(1) == 0x13)
        {
            if(static_cast<unsigned char>(reciveData.at(2)) == 0xFF &&
               static_cast<unsigned char>(reciveData.at(3)) == 0xFF &&
               static_cast<unsigned char>(reciveData.at(4)) == 0xFF)
            {
                QString data = "FasTestUSBReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file("/home/xfss/root/logfile/FasTestData.txt");

                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << data << '\n';
                    file.close();
                }
                reciveData.clear();
                //火报通讯USB接口接收测试成功
                QHash<QString, QVariant> controlDomain;
                controlDomain.insert("communicationType",CT_TestCard);
                QByteArray tmpByteArray;
                tmpByteArray.append(char(0x02));
                CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
            }
        }
        //ARTU通讯
        else if(CGlobal::instance()->processController()->ARTUType())
        {
            //079-KJ
            if(CGlobal::instance()->processController()->ARTUType() == 2)
            {
                if(reciveData.count() < 6)
                {
                    reciveData.clear();
                    return;
                }
                CMsgNull msgNull;
                QByteArray byte = msgNull.data(NCT_LinkageComStatus);
                CGlobal::instance()->DealEvent(NCT_LinkageComStatus, byte);
                CGlobal::instance()->m_isReceiveLinkageData = true;
                m_timerResetLinkageFlag->start(3000);
                QString data = "ARTUReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file("/home/xfss/root/logfile/ARTUReciveData.txt");

                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << data << '\n';
                    file.close();
                }
                QString filePath = "/home/xfss/root/logfile/ARTUReciveData.txt";
                CGlobal::instance()->controlTxtFileSize(filePath, 1024 * 1024);

                int deviceAddress = CGlobal::instance()->processController()->ARTUAddress();

                if(reciveData.at(0) != deviceAddress || reciveData.at(1) != 0x02)
                {
                    reciveData.clear();
                    return;
                }
                // 获取数据部分
                unsigned char value = static_cast<unsigned char>(reciveData.at(3));

                for (int i = 1; i <= 8; ++i)
                {
                    if (value & (1 << (i-1)))
                    {
                        QHash<QString, QVariant> controlDomain;
                        controlDomain.insert("communicationType",CT_LinkageCard);
                        QByteArray tmpByteArray;
                        tmpByteArray.append(static_cast<char>((deviceAddress>>8)&0xFF));   //设备
                        tmpByteArray.append(static_cast<char>(deviceAddress&0xFF));   //设备
                        tmpByteArray.append(static_cast<char>(0x00));   //回路
                        tmpByteArray.append(static_cast<char>(0x00));   //回路
                        tmpByteArray.append(static_cast<char>(((i)>>8)&0xFF));   //点位
                        tmpByteArray.append(static_cast<char>(i&0xFF));        //点位
                        ARTUDIlists.append(tmpByteArray);
                        m_timerARTUDIsend->start(100);
//                        CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
                    }
                }
                reciveData.clear();
            }
            //426和079-K
            else if(CGlobal::instance()->processController()->ARTUType() == 1 ||
                    CGlobal::instance()->processController()->ARTUType() == 3)
            {
                if(reciveData.count() < 9)
                {
                    reciveData.clear();
                    return;
                }
                CMsgNull msgNull;
                QByteArray byte = msgNull.data(NCT_LinkageComStatus);
                CGlobal::instance()->DealEvent(NCT_LinkageComStatus, byte);
                CGlobal::instance()->m_isReceiveLinkageData = true;
                m_timerResetLinkageFlag->start(3000);
                QString data = "ARTUReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file("/home/xfss/root/logfile/ARTUReciveData.txt");

                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << data << '\n';
                    file.close();
                }
                QString filePath = "/home/xfss/root/logfile/ARTUReciveData.txt";
                CGlobal::instance()->controlTxtFileSize(filePath, 1024 * 1024);

                int deviceAddress = CGlobal::instance()->processController()->ARTUAddress();

                if(reciveData.at(0) != deviceAddress || reciveData.at(1) != 0x02)
                {
                    reciveData.clear();
                    return;
                }
                // 获取数据部分
                unsigned int value = static_cast<unsigned int>((static_cast<unsigned char>(reciveData.at(6)) << 24) |
                                                                (static_cast<unsigned char>(reciveData.at(5)) << 16) |
                                                                (static_cast<unsigned char>(reciveData.at(4)) << 8) |
                                                                (static_cast<unsigned char>(reciveData.at(3))));

                for (int i = 1; i <= 32; ++i)
                {
                    if (value & (1 << (i-1)))
                    {
                        QHash<QString, QVariant> controlDomain;
                        controlDomain.insert("communicationType",CT_LinkageCard);
                        QByteArray tmpByteArray;
                        tmpByteArray.append(static_cast<char>((deviceAddress>>8)&0xFF));   //设备
                        tmpByteArray.append(static_cast<char>(deviceAddress&0xFF));   //设备
                        tmpByteArray.append(static_cast<char>(0x00));   //回路
                        tmpByteArray.append(static_cast<char>(0x00));   //回路
                        tmpByteArray.append(static_cast<char>(((i)>>8)&0xFF));   //点位
                        tmpByteArray.append(static_cast<char>(i&0xFF));        //点位
                        ARTUDIlists.append(tmpByteArray);
                        m_timerARTUDIsend->start(100);
//                        CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
                    }
                }
                reciveData.clear();
            }
        }
        //火报通讯
        else
        {
            if(reciveData.count() < 11)
            {
                reciveData.clear();
                return;
            }
            CMsgNull msgNull;
            QByteArray byte = msgNull.data(NCT_LinkageComStatus);
            CGlobal::instance()->DealEvent(NCT_LinkageComStatus, byte);
            CGlobal::instance()->m_isReceiveLinkageData = true;
            m_timerResetLinkageFlag->start(3000);
            QString data = "FasReciveData:  " + reciveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
            QFile file("/home/xfss/root/logfile/FasReciveData.txt");

            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << data << '\n';
                file.close();
            }
            QString filePath = "/home/xfss/root/logfile/FasReciveData.txt";
            CGlobal::instance()->controlTxtFileSize(filePath, 1024 * 1024);

            if(reciveData.at(0) != 0x01 || reciveData.at(1) != 0x03 || reciveData.at(2) != 0x06)
            {
                reciveData.clear();
                return;
            }
            QHash<QString, QVariant> controlDomain;
            controlDomain.insert("communicationType",CT_LinkageCard);

            QByteArray tmpByteArray;
            tmpByteArray.append(reciveData.at(3));   //设备
            tmpByteArray.append(reciveData.at(4));   //设备
            tmpByteArray.append(reciveData.at(5));   //回路
            tmpByteArray.append(reciveData.at(6));   //回路
            tmpByteArray.append(reciveData.at(7));   //点位
            tmpByteArray.append(reciveData.at(8));   //点位

            CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
            reciveData.clear();
        }
    }
}


void CCommunicationManager::handleTestReciveData()
{
    qDebug() << "handleTestReciveData";
    CSerialPort* pSerialPort = m_hashCommunicationLine["testcard"]->pSerialPort;
    QByteArray &receiveData = m_hashCommunicationLine["testcard"]->reciveData;
    if (receiveData.isEmpty())
        return;
    if(receiveData.count() < 6)
    {
        receiveData.clear();
        return;
    }
    if(pSerialPort)
    {
        if(static_cast<unsigned char>(receiveData.at(2)) == 0xFF &&
           static_cast<unsigned char>(receiveData.at(3)) == 0xFF &&
           static_cast<unsigned char>(receiveData.at(4)) == 0xFF)
        {
            QString dataReceive = "FasTestComReceiveData:  " + receiveData.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
            QFile fileReceive("/home/xfss/root/logfile/FasTestData.txt");

            if (fileReceive.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&fileReceive);
                stream << dataReceive << '\n';
                fileReceive.close();
            }
            //火报通讯USB接口发送测试成功
            QHash<QString, QVariant> controlDomain;
            controlDomain.insert("communicationType",CT_TestCard);
            //测试USB火报通讯口接收（中间层火报接口发送）
            QByteArray byteArray;
            int sum = 0;
            byteArray.append(char(0x55));
            byteArray.append(char(0x13));
            byteArray.append(char(0xFF));
            byteArray.append(char(0xFF));
            byteArray.append(char(0xFF));
            for (int ix = 0; ix < byteArray.size(); ix++)
                sum += byteArray.at(ix);
            byteArray.append(sum);
            pSerialPort->sendData(byteArray);
            QString dataSend = "FasTestComSendData:  " + byteArray.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
            QFile fileSend("/home/xfss/root/logfile/FasTestData.txt");

            if (fileSend.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&fileSend);
                stream << dataSend << '\n';
                fileSend.close();
            }
            QByteArray tmpByteArray;
            tmpByteArray.append(char(0x01));
            CGlobal::instance()->processController()->procRecvEvent(0, controlDomain, tmpByteArray);
        }
        receiveData.clear();
    }
}
/*

*/
void CCommunicationManager::handleCan1ReciveData()
{
    CSerialPort* pSerialPort = m_hashCommunicationLine["cancard1"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["cancard1"]->reciveData;

    if (reciveData.isEmpty())
        return;
    if(pSerialPort)
    {
        while (reciveData.size() >= 14)  // 14 最短长度（心跳）
        {
            // 检查是否匹配帧头
            if (reciveData.startsWith(QByteArray::fromHex("55aacc33"))) {
                // 如果匹配帧头，获取数据包长度（假设长度信息在帧头之后）
                int packetLength = 13 + reciveData.at(10);

                // 检查接收到的数据是否包含整个数据包
                if (reciveData.size() >= packetLength) {
                    // 获取整个数据包
                    QByteArray packet = reciveData.left(packetLength);
//                    QString  data = "cancard1ReciveData:  " + packet.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                    QFile file("/home/xfss/root/logfile/receiveCan1data.txt");

//                    if (file.open(QIODevice::Append | QIODevice::Text))
//                    {
//                        QTextStream stream(&file);
//                        stream << data << '\n' << '\n';
//                        file.close();
//                    }

                    // 处理数据包
                    static PackageAnalyzer packAnalyzer;
                    PackageTemplate* pack = packAnalyzer.doAnalysis(packet);

                    // 清除已处理的数据
                    reciveData.remove(0, packetLength);

                    // 继续处理数据包
                    if (pack) {
                        int nInfoType = pack->getInfoType();
                        QByteArray tmpByteArray = pack->getInfo().toByteArray();
                        QHash<QString, QVariant> controlDomain;
                        controlDomain.insert("_portNumber_", pack->getCanId() - 2);
                        controlDomain.insert("recvAddr", pack->getRxAddr());
                        controlDomain.insert("sendAddr", pack->getTxAddr());
                        controlDomain.insert("commandType", pack->getCode());
                        controlDomain.insert("loopAddr", pack->getLoopAddr());
                        controlDomain.insert("deviceAddr", pack->getDeviceAddr());
                        if (nInfoType == 0x61)
                        {
                            QByteArray uid = pack->getSimpleVar();
                            controlDomain.insert("uid", CGlobal::instance()->getUidString(uid, 6));
                        }
                        CGlobal::instance()->processDistribution()->procRecvEvent(nInfoType, controlDomain, tmpByteArray);
                    }
                } else {
                    // 如果接收到的数据不足以构成一个完整的数据包，则退出循环，等待更多数据
                    break;
                }
            } else {
                // 如果没有匹配到帧头，则移除第一个字节，继续查找帧头
                reciveData.remove(0, 1);
            }
        }
    }
}


void CCommunicationManager::handleCan2ReciveData()
{
    CSerialPort* pSerialPort = m_hashCommunicationLine["cancard2"]->pSerialPort;
    QByteArray &reciveData = m_hashCommunicationLine["cancard2"]->reciveData;

    if (reciveData.isEmpty())
        return;

    if(pSerialPort)
    {
        while (reciveData.size() >= 14)  // 14 最短长度（心跳）
        {
            // 检查是否匹配帧头
            if (reciveData.startsWith(QByteArray::fromHex("55aacc33"))) {
                // 如果匹配帧头，获取数据包长度（假设长度信息在帧头之后）
                int packetLength = 13 + reciveData.at(10);

                // 检查接收到的数据是否包含整个数据包
                if (reciveData.size() >= packetLength) {
                    // 获取整个数据包
                    QByteArray packet = reciveData.left(packetLength);
//                    QString  data = "cancard2ReciveData:  " + packet.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//                    QFile file("/home/xfss/root/logfile/receiveCan2data.txt");

//                    if (file.open(QIODevice::Append | QIODevice::Text))
//                    {
//                        QTextStream stream(&file);
//                        stream << data << '\n' << '\n';
//                        file.close();
//                    }

                    // 处理数据包
                    static PackageAnalyzer packAnalyzer;
                    PackageTemplate* pack = packAnalyzer.doAnalysis(packet);

                    // 清除已处理的数据
                    reciveData.remove(0, packetLength);

                    // 继续处理数据包
                    if (pack) {
                        int nInfoType = pack->getInfoType();
                        QByteArray tmpByteArray = pack->getInfo().toByteArray();
                        QHash<QString, QVariant> controlDomain;
                        controlDomain.insert("_portNumber_", pack->getCanId() - 2);
                        controlDomain.insert("recvAddr", pack->getRxAddr());
                        controlDomain.insert("sendAddr", pack->getTxAddr());
                        controlDomain.insert("commandType", pack->getCode());
                        controlDomain.insert("loopAddr", pack->getLoopAddr());
                        controlDomain.insert("deviceAddr", pack->getDeviceAddr());
                        if (nInfoType == 0x61) {
                            QByteArray uid = pack->getSimpleVar();
                            controlDomain.insert("uid", CGlobal::instance()->getUidString(uid, 6));
                        }
                        CGlobal::instance()->processDistribution()->procRecvEvent(nInfoType, controlDomain, tmpByteArray);
                    }
                } else {
                    // 如果接收到的数据不足以构成一个完整的数据包，则退出循环，等待更多数据
                    break;
                }
            } else {
                // 如果没有匹配到帧头，则移除第一个字节，继续查找帧头
                reciveData.remove(0, 1);
            }
        }
    }
}

void CCommunicationManager::canSendDataClear()
{
    QString linename = "cancard1";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 sendDataTableAsType
    m_hashCommunicationLine[linename]->sendDataTableAsType.clear();

    linename = "cancard2";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 sendDataTableAsType
    m_hashCommunicationLine[linename]->sendDataTableAsType.clear();
}

void CCommunicationManager::canReceiveDataClear()
{
    QString linename = "cancard1";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 reciveData
    m_hashCommunicationLine[linename]->reciveData.clear();

    linename = "cancard2";
    if (!m_hashCommunicationLine.contains(linename)) return;

    // 清空 reciveData
    m_hashCommunicationLine[linename]->reciveData.clear();
}

unsigned short CCommunicationManager::usMBCRC16(const unsigned char *pucFrame, unsigned short usLen)
{
    uchar ucCRCHi = 0xFF;
    uchar ucCRCLo = 0xFF;
    int iIndex;
    while(usLen--)
    {
        iIndex = ucCRCLo ^ *(pucFrame++);
        ucCRCLo = (uchar)(ucCRCHi ^ aucCRCHi[iIndex]);
        ucCRCHi = aucCRCLo[iIndex];
    }
    return (ushort)(ucCRCHi << 8 | ucCRCLo);
}

