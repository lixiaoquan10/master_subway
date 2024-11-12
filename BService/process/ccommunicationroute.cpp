#include <QDebug>
#include <QVector>
#include <QTextCodec>
#include "struct/cmsgnull.h"
#include "cprocessbase.h"
#include "cprocesscontroller.h"
#include "ccommunicationroute.h"
#include "ccommunicationmanager.h"
#include "cglobal.h"
#include "cserialport.h"

CCommunicationRoute::CCommunicationRoute(QObject *parent) :
    QObject(parent), m_communicationManager(NULL)
{
    initCommunicationManager();
    createCommunication(CT_LedCard);
    createCommunication(CT_LinkageCard);
    createCommunication(CT_TestCard);
}

CCommunicationRoute::~CCommunicationRoute()
{
    delete m_communicationManager;
}

void CCommunicationRoute::initCommunicationManager()
{
    if(!m_communicationManager)
        m_communicationManager = new CCommunicationManager();
    connect(m_communicationManager, SIGNAL(sig_ReciveData(QString,int,QHash<QString,QVariant>,QByteArray)), this, SLOT(procCommunicationRecvEvent(QString,int,QHash<QString,QVariant>,QByteArray)));}

bool CCommunicationRoute::createRoute(CProcessBase *process, const int type, const QHash<QString, QVariant> &control)
{
    QString processName = process->name();
    QString communication = createCommunication(type);
    if(communication.isEmpty())
        return false;
    if(isCommunicationLine(type))
    {
        int port = control.value(INTERFACEBOARD_PORT_NUMBER_STR, QVariant(0)).toInt();
        if(!process->addCardPort(port))
            return false;
        m_communicationManager->setTimeOut(communication, INTERFACEBOARD_TIMEOUT);
        int speed = control.value(INTERFACEBOARD_PORT_SPEED_STR, QVariant(0)).toInt();
        m_interfaceBoardPortSpeed.insert(port, speed);
        if(type == CT_FASCard){
            m_interfaceInfo.insert(INTERFACEBOARD_COMMPNYCODE, control.value(INTERFACEBOARD_COMMPNYCODE, QVariant(0)).toInt());
            m_interfaceInfo.insert(INTERFACEBOARD_PANEL, control.value(INTERFACEBOARD_PANEL, QVariant(0)).toInt());
        }
    }
    if(!m_process.contains(processName)){
        m_process.insert(processName, process);
        m_processCommunication.insert(processName, communication);
        connect(this, SIGNAL(processRecvEvent(QString,int,QHash<QString,QVariant>,QByteArray)), process, SLOT(recvEvent(QString,int,QHash<QString,QVariant>,QByteArray)));
    } else{
        if(!m_processCommunication.values(processName).contains(communication))
            m_processCommunication.insertMulti(processName, communication);
    }
    return true;
}

////create communication line
QString CCommunicationRoute::createCommunication(const int type)
{
    QString communicationName;
    communicationName = getCommunicationName(type);
    if(!communicationName.isEmpty() && m_communicationManager)
    {
        if(!m_communication.contains(communicationName))
        {
            if(!m_communicationManager->createCommunicationLine(communicationName, type))
                return QString();
            m_communication.append(communicationName);
        }
    }
    return communicationName;
}

void CCommunicationRoute::openCommunication()
{
    if(CGlobal::isDebug()) qDebug() << "CCommunicationRoute::openCommunication()" << m_communication.size();
    for(int i = 0; i < m_communication.size(); ++i) /*灯 电源 can1 can2*/
    {
        m_communicationManager->open(m_communication.at(i));
    }
}

void CCommunicationRoute::closeCommunication()
{
    for(int i = 0; i < m_communication.size(); ++i)
    {
        m_communicationManager->close(m_communication.at(i));
    }
}

void CCommunicationRoute::setDebug(const bool enable)
{
    m_communicationManager->setDebugOut(enable);
}

void CCommunicationRoute::canSendDataClear()
{
    m_communicationManager->canSendDataClear();
}

void CCommunicationRoute::canReceiveDataClear()
{
    m_communicationManager->canReceiveDataClear();
}

void CCommunicationRoute::setLedStatus(const int ledStatus1, const int ledStatus2, const int ledStatus3)
{
    QString communicationLed = getCommunicationName(CT_LedCard);
    if(communicationLed.isEmpty())
        return;
    if(communicationIsActive(communicationLed))
    {
        QString linename = "ledcard";
        if(!m_communicationManager->m_hashCommunicationLine.contains(linename)) return;
        CSerialPort* pSerialPort = m_communicationManager->m_hashCommunicationLine[linename]->pSerialPort;
        if(pSerialPort)
        {
            char sum = 0;
            QByteArray byteArray;
            byteArray.append(char(0x55));
            byteArray.append(char(0x13));
            byteArray.append(char(ledStatus1));
            byteArray.append(char(0));
            byteArray.append(char(0));
            byteArray.append(char(0));
            byteArray.append(char(ledStatus2));
            byteArray.append(char(ledStatus3));
            byteArray.append(char(0));
            byteArray.append(char(0));
            byteArray.append(char(0));
            for (int ix = 0; ix < byteArray.size(); ix++)
                sum += byteArray.at(ix);
            byteArray.append(sum);
            pSerialPort->sendData(byteArray);
//            QString data = "handleLedSendData:  " + byteArray.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
//            QFile file("/home/xfss/root/logfile/LedSendData.txt");

//            if (file.open(QIODevice::Append | QIODevice::Text))
//            {
//                QTextStream stream(&file);
//                stream << data << '\n';
//                file.close();
//            }
        }
    }
    else
    {
        m_communicationManager->close("ledcard");
        // 重新打开串口
        QString data;
        if(m_communicationManager->open("ledcard"))
        {
            data ="Led串口重新打开成功!  " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
            // 连接信号与槽等相关操作
        }  else {
            data ="Led串口重新打开失败!  " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
        }
        QFile file("/home/xfss/root/logfile/ledportlog.txt");

        if (file.open(QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&file);
            stream << data << '\n' << '\n';
            file.close();
        }
    }
    if(!m_communicationManager->isSerialportNameSeted())
    {
        QString communicationLinkage = getCommunicationName(CT_LinkageCard);
        if(communicationLinkage.isEmpty())
            return;
        if(communicationIsActive(communicationLinkage))
        {
            QString linename = "linkagecard";
            if(!m_communicationManager->m_hashCommunicationLine.contains(linename)) return;
            CSerialPort* pSerialPort = m_communicationManager->m_hashCommunicationLine[linename]->pSerialPort;
            if(pSerialPort)
            {
                char sum = 0;
                QByteArray byteArray;
                byteArray.append(char(0x55));
                byteArray.append(char(0x13));
                byteArray.append(char(ledStatus1));
                byteArray.append(char(0));
                byteArray.append(char(0));
                byteArray.append(char(0));
                byteArray.append(char(ledStatus2));
                byteArray.append(char(ledStatus3));
                byteArray.append(char(0));
                byteArray.append(char(0));
                byteArray.append(char(0));
                for (int ix = 0; ix < byteArray.size(); ix++)
                    sum += byteArray.at(ix);
                byteArray.append(sum);
                pSerialPort->sendData(byteArray);
                QString data = "LedLinkageData:  " + byteArray.toHex() + " " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz") + "\n";
                QFile file("/home/xfss/root/logfile/LedLinkageData.txt");

                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    stream << data << '\n';
                    file.close();
                }
            }
        }
    }
}

void CCommunicationRoute::testLinkageCom()
{
    //测试USB火报通讯口发送（中间层火报接口接收）
    m_communicationManager->setTestLinkageCom(true);
    QTimer::singleShot(5000, this, SLOT(slot_stopTestLinkageCom()));
    QString communicationLinkage = getCommunicationName(CT_LinkageCard);
    if(communicationLinkage.isEmpty())
        return;
    if(communicationIsActive(communicationLinkage))
    {
        QString linkagelinename = "linkagecard";
        if(!m_communicationManager->m_hashCommunicationLine.contains(linkagelinename)) return;
        CSerialPort* pSerialPort_linkage = m_communicationManager->m_hashCommunicationLine[linkagelinename]->pSerialPort;
        QString testlinename = "testcard";
        if(!m_communicationManager->m_hashCommunicationLine.contains(testlinename)) return;
        CSerialPort* pSerialPort_test = m_communicationManager->m_hashCommunicationLine[testlinename]->pSerialPort;
        if(pSerialPort_test && pSerialPort_linkage)
        {
            if(!pSerialPort_test->serialPort()->open(QIODevice::ReadWrite))
            {
                for(int i=2;i<5;i++)
                {
                    pSerialPort_test->serialPort()->close();
                    pSerialPort_test->serialPort()->setPortName("/dev/ttyUSB"+ QString::number(i));
                    //linkagecard的波特率
                    BaudRateType baudRate = pSerialPort_linkage->serialPort()->baudRate();
                    pSerialPort_test->serialPort()->setBaudRate(baudRate);
                    QObject::connect(pSerialPort_test->serialPort(), SIGNAL(readyRead()), pSerialPort_test->serialPort(), SLOT(doReciveData()));
                    if(pSerialPort_test->serialPort()->open(QIODevice::ReadWrite))
                        break;
                }
            }
            char sum = 0;
            QByteArray byteArray;
            byteArray.append(char(0x55));
            byteArray.append(char(0x13));
            byteArray.append(char(0xFF));
            byteArray.append(char(0xFF));
            byteArray.append(char(0xFF));
            for (int ix = 0; ix < byteArray.size(); ix++)
                sum += byteArray.at(ix);
            byteArray.append(sum);

            pSerialPort_linkage->sendData(byteArray);

            QString  data = "FasTestUSBSendData:  " + byteArray.toHex() + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
            QFile file("/home/xfss/root/logfile/FasTestData.txt");

            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << data << '\n' << '\n';
                file.close();
            }
        }
    }
}

void CCommunicationRoute::slot_stopTestLinkageCom()
{
    m_communicationManager->setTestLinkageCom(false);
}

void CCommunicationRoute::linkageSendData(QByteArray data)
{
    QString communicationLinkage = getCommunicationName(CT_LinkageCard);
    if(communicationLinkage.isEmpty())
        return;
    if(communicationIsActive(communicationLinkage))
    {
        QString linename = "linkagecard";
        if(!m_communicationManager->m_hashCommunicationLine.contains(linename)) return;
        CSerialPort* pSerialPort = m_communicationManager->m_hashCommunicationLine[linename]->pSerialPort;
//        m_communicationManager->sendLinkageData(communicationLinkage, SendFasFire, data);
        if(pSerialPort)
        {
            QByteArray byteArray;
            byteArray.append(data);
            // 计算 CRC 值
            // 获取指向数据的指针和长度
            const unsigned char *dataPtr = reinterpret_cast<const unsigned char *>(data.constData());
            unsigned short length = static_cast<unsigned short>(data.size());
            // 调用 CRC 函数
            unsigned short crc = m_communicationManager->usMBCRC16(dataPtr, length);
            byteArray.append(static_cast<char>(crc & 0xFF));        // 低字节
            byteArray.append(static_cast<char>((crc >> 8) & 0xFF)); // 高字节
            pSerialPort->sendData(byteArray);

            QString  data = "FasSendData:  " + byteArray.toHex() + "   " + QString::number(pSerialPort->serialPort()->baudRate()) + "   " + QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
            QFile file("/home/xfss/root/logfile/FasSendData.txt");

            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << data << '\n' << '\n';
                file.close();
            }
            QString filePath = "/home/xfss/root/logfile/FasSendData.txt";
            CGlobal::instance()->controlTxtFileSize(filePath, 1024 * 1024);
        }
    }
}


void CCommunicationRoute::setLinkageBaudRate(QString baudrateString)
{
    m_communicationManager->setLinkageBaudRate(baudrateString);
    CGlobal::instance()->processController()->startLinkageCom();
}


////get line name from line type
QString CCommunicationRoute::getCommunicationName(const int type)
{
    QString name;
    switch(type)
    {
    case CT_LinkageCard:
        name = "linkagecard";
        break;
    case CT_LedCard:
        name = "ledcard";
        break;
    case CT_CanCard1:
        name = "cancard1";
        break;
    case CT_CanCard2:
        name = "cancard2";
        break;
    case CT_FASCard:
        name = "fascard";
        break;
    case CT_TestCard:
        name = "testcard";
        break;
    default:
        name = "Client";
        break;
    }
    return name;
}

int CCommunicationRoute::getCommunicationType(const QString lineName)
{
    if(lineName.toLower() == "linkagecard") return CT_LinkageCard;
    else if(lineName.toLower() == "ledcard") return CT_LedCard;
    else if(lineName.toLower() == "cancard1") return CT_CanCard1;
    else if(lineName.toLower() == "cancard2") return CT_CanCard2;
    else if(lineName.toLower() == "testcard") return CT_TestCard;
    else if(lineName.toLower() == "fascard") return CT_FASCard;
    else return CT_NoCard;
}

////line type is true line
bool CCommunicationRoute::isCommunicationLine(const int type) const
{
    if(type == CT_CanCard1 || type == CT_CanCard2 || type == CT_LedCard || type == CT_LinkageCard
           || type == CT_TestCard || type == CT_FASCard)
        return true;
    else
        return false;
}

bool CCommunicationRoute::communicationIsActive(const QString &name) const
{
    return m_communicationManager->isActive(name);
}


QString CCommunicationRoute::canNameByAdd(int canportAdd)
{
    if(canportAdd == 3 || canportAdd == 4 || canportAdd == 7 || canportAdd == 8)
        return "cancard1";
    else if(canportAdd == 5 || canportAdd == 6 || canportAdd == 9 || canportAdd == 10)
        return "cancard2";
    return "";
}

int CCommunicationRoute::getIntFromByte(QByteArray data, int start, int len)
{
    if(data.size() < start+len) return 0;
    return (*(unsigned int*)data.mid(start,len).data())&0x0000ffff;;
}

////send data to process
void CCommunicationRoute::procCommunicationRecvEvent(const QString &linename, const int &infoType, const QHash<QString, QVariant> &controlDomain, const QByteArray &data)
{
//    if(CGlobal::isDebug()) qDebug() << "CCommunicationRoute::procCommunicationRecvEvent=====" << linename << infoType << data.toHex();
    if(m_communication.contains(linename))
    {
        QList<QString> processList = m_processCommunication.keys(linename);
        for(int i = 0; i < processList.size(); ++i)
            emit processRecvEvent(processList.at(i), infoType, controlDomain, data);
    }
}
