#include "cclientbusiness.h"
#include "cdataprocessing.h"
#include "communication/ccommunication.h"
#include "widget/cprogramtreeview.h"
#include "widget/cdesigntreeview.h"
#include "widget/cbottomtoolbar.h"
#include "widget/ctoptoolbar.h"
#include "dm/ccontroller.h"
#include "dm/cdm.h"
#include "dm/ccanport.h"
#include "dm/cdistribution.h"
#include "dm/cloop.h"
#include "dm/cdevice.h"
#include "dm/clayer.h"
#include "dialog/dlgadministrator.h"
#include "dialog/dlgdevices.h"
#include "dialog/dlgtimeinterval.h"
#include "dialog/dlgsystemrecord.h"
#include "widget/cprogramdistributionview.h"
#include "widget/cprogramcandeviceview.h"
#include "widget/cprogramdeviceview.h"
#include "widget/cdesignsplashview.h"
#include "graphics/configfilemanager.h"
#include "graphics/deviceForbidFault.h"
#include "graphics/deviceDefaultControl.h"
#include "cglobal.h"
#include "dm/cdbsqlite.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QCoreApplication>
#include <QTimer>
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QApplication>
#include <QTextCodec>
#include <QUuid>

CClientBusiness::CClientBusiness(QObject *parent) :
    QObject(parent), m_strNormal("<span style='color:#60D978;'>正常</span>"),
    m_strFault("<span style='color:#E53333;'>故障</span>"),
    m_strCharging("<span style='color:#00D5FF;'>充电</span>"),
    m_isInitController(false), m_isRecvStatus(false),
    m_currentStatusId(0), m_currentRecvStatusId(0), m_currentRecvStatusNumber(0),
    m_advPassword("6006")
{
    qDebug() << "CClientBusiness::CClientBusiness" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    m_projectPath = QCoreApplication::applicationDirPath(); /*应用程序目录 /opt*/
//    m_communication = new CCommunication(m_projectPath + "/BService.dll");
    m_communication = new CCommunication(m_projectPath + "/libBService.so.1.0.0");
    connect(m_communication, SIGNAL(recvData(int,QByteArray&)), this, SLOT(recvData(int,QByteArray&)));
    m_projectPath = QCoreApplication::applicationDirPath();
    createPath(m_projectPath);        
    setCommunicationConfig();

    m_projectFile = m_projectPath + "/ESSQLiteCE100.db";
    m_checkSet.yearCycle = 365;
    m_checkSet.yearDuration = 30;
    m_checkSet.monthCycle = 30;
    m_checkSet.monthDuration = 30;
    m_strPassword = "0000";
    m_bForceEmergency = true;
    m_xmlheader = "version=\"1.0\" encoding=\"UTF-8\"";
    connect(CGlobal::instance()->dm(), SIGNAL(sigObjectStatusChanged(CObject*,short,unsigned char,unsigned char,uint)), this, SLOT(objectStatusChanged(CObject*,short,unsigned char,unsigned char,uint)));
    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    m_timer->start(5000);
    m_linkageComTimer = new QTimer();
    connect(m_linkageComTimer, SIGNAL(timeout()), this, SLOT(slot_linkageComStatus()));
    m_masterStateUploadFlag = false;
    m_cloudStateUploadFlag = false;
    m_isNotRemoveDistributionLogin = false;
    m_isQueryAllState = false;
    m_isCANconfig = false;

    m_msgLog = new CMsgLog();

    m_mainPowerStoptimer = new QTimer();
    connect(m_mainPowerStoptimer, SIGNAL(timeout()), this, SLOT(mainPowerStop()));

    m_saveLogintimer = new QTimer();
    connect(m_saveLogintimer, SIGNAL(timeout()), this, SLOT(slot_saveLoginData()));

    m_flashTimer = new QTimer();
    connect(m_flashTimer, SIGNAL(timeout()), this, SLOT(slot_flashControl()));
    // 创建 QProcess 对象并连接信号与槽
//    m_process_light = new QProcess(this);
//    QString program = "/home/xfss/root/USBprogramUpdate/lightScreem.sh";  // 脚本的路径
//    m_process_light->start(program);
}

CClientBusiness::~CClientBusiness()
{
    delete m_timer;
    delete m_communication;
    delete m_msgLog;
    delete m_mainPowerStoptimer;
    delete m_saveLogintimer;
    delete m_flashTimer;
    delete m_linkageComTimer;
    m_msg.clear();
    m_emergencyFirePoints.clear();
    m_unknowFirePoints.clear();
}

void CClientBusiness::setCommunicationConfig()
{
    qDebug() << "CClientBusiness::setCommunicationConfig" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    m_communication->CommunicationType(m_projectPath);
    m_communication->InitCommunication();
    QByteArray byte;
    CMsgRouteConfig msg;
    foreach(RouteConfig* card, CGlobal::instance()->m_hashCard)
    {
        if(!card) continue;
        msg.routeConfigs.append(*card);
    }
    byte = msg.data();
    m_communication->ParsePacket(NCT_SetRouteConfig, byte.data(), byte.size());
}

void CClientBusiness::destroyCommunication()
{
    qDebug() << "CClientBusiness::destroyCommunication"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(m_communication) m_communication->DestroyedCommunication();
}

void CClientBusiness::startCommunication()
{
    qDebug() << "CClientBusiness::startCommunication"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(m_communication->StartCommunication(CGlobal::instance()->panelAddress())){
        CGlobal::instance()->dm()->clearStatusObjects(true);
        CGlobal::instance()->m_bStartComm = true;
        CGlobal::instance()->InformationWindow()->hide();
        CGlobal::instance()->setMSgColor(QColor(12, 180, 3));
    }
    m_communication->ShowTest(true);        
}

void CClientBusiness::stopCommunication()
{
    qDebug() << "CClientBusiness::stopCommunication"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(m_communication->StopCommunication()){
        CGlobal::instance()->m_bStartComm = false;
        CGlobal::instance()->m_bInLogin = false;
    }
}

bool CClientBusiness::verifyAdminUser(const int commandType, const QString &password)
{
    qDebug() << "CClientBusiness::verifyAdminUser"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    bool status = false;
    if(commandType == 3){
        if(password == m_advPassword)
            status = true;
    }
    else{
        if(password == m_strPassword)
            status = true;
    }
    if(CGlobal::instance()->m_loginStatus == false){
        if(status)
        {
            QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
            db.setDatabaseName(fileName);
            if(!db.open())
                return false;
            QSqlQuery query(db);
            if(commandType == 0)
            {
                CGlobal::instance()->m_UserType = CGlobal::OnDuty;
                query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('LastLoginName', '%1');").arg("值班员"));
            }
            else if(commandType == 1)
            {
                CGlobal::instance()->m_UserType = CGlobal::Operator;
                query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('LastLoginName', '%1');").arg("操作员"));
            }
            else if(commandType == 2)
            {
                CGlobal::instance()->m_UserType = CGlobal::Administrator;
                query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('LastLoginName', '%1');").arg("管理员"));
            }
            else if(commandType == 3)
            {
                CGlobal::instance()->m_UserType = CGlobal::SuperAdministrator;
                query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('LastLoginName', '%1');").arg("SuperAdmin"));
            }

            db.commit();
            db.close();
            CGlobal::instance()->BottomToolBar()->setAdministrator();
        }

    }
    else
    {
        if(commandType != CGlobal::instance()->m_UserType)
            status = false;
    }
    if((CGlobal::instance()->m_loginStatus == false) && status){
        CGlobal::instance()->m_loginStatus = true;
    }
    return status;
}

void CClientBusiness::setNewPwd(const QString strpwd)
{
    qDebug() << "CClientBusiness::setNewPwd"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    m_strPassword = strpwd;
    CGlobal::instance()->m_strPassWord = strpwd;
}

///用户操作按键时要求验证用户权限
bool CClientBusiness::verifyAdminUser(const int commandType)
{
    qDebug() << "CClientBusiness::verifyAdminUser"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    static bool flag = true;
    if(CGlobal::instance()->m_UserType == CGlobal::User)
    {
        if(flag)
        {
            flag = false;
            dlgAdministrator m_Administrator;
            if(QDialog::Accepted == m_Administrator.exec()) {
                CGlobal::instance()->BottomToolBar()->setAdministrator();
            } else {
                flag = true;
                return false;
            }
            flag = true;
        }
    }
    else if(CGlobal::instance()->m_UserType == CGlobal::Administrator)
    {
        if (commandType == NCT_ForceEmergency)
        {
            if(flag)
            {
                flag = false;
                dlgAdministrator m_Administrator;
                if(QDialog::Accepted == m_Administrator.exec()) {
                    CGlobal::instance()->BottomToolBar()->setAdministrator();
                } else {
                    flag = true;
                    return false;
                }
                flag = true;
            }
        }
    }
    return true;
}

void CClientBusiness::addLog(const QString strUser, const QString strTitle, const QString strArea, const QString strLocation, const QString strRemark,
                             const int CanPort, const int CanDeviceAddress, const int Loop, const int LampDeviceAddress, const QString strType)
{
    qDebug() << "CClientBusiness::addLog"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CMsgLog msgLog;
    msgLog.user = strUser;
    msgLog.time = QDateTime::currentDateTime();
    msgLog.title = strTitle;
    msgLog.type = strType;
    msgLog.User = strUser;
    msgLog.Type = strType;
    msgLog.Time = QDateTime::currentDateTime();
    msgLog.Area = strArea;
    msgLog.Location = strLocation;
    msgLog.Remark = strRemark;
    msgLog.Canport = CanPort;
    msgLog.CanDeviceAddress = CanDeviceAddress;
    msgLog.Loop = Loop;
    msgLog.LampDeviceAddress = LampDeviceAddress;
    exeCommand(NCT_AddLog, &msgLog);
}

void CClientBusiness::showTest(bool bwrite)
{
    qDebug() << "CClientBusiness::showTest"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(m_communication)
        m_communication->ShowTest(bwrite);
}

bool CClientBusiness::exeCommand(int commandType, CMsgStructBase *msgData)
{
    qDebug() << "CClientBusiness::exeCommand"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(!msgData)
        return false;
    QByteArray data = msgData->data(commandType);
    m_communication->ParsePacket(commandType, data.data(), data.size());
    return true;
}

CCanport *CClientBusiness::currentPanel() const
{
    qDebug() << "CClientBusiness::currentPanel"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CCanport* canport = NULL;
    if(CGlobal::instance()->dm()->isLoad())
        canport = CGlobal::instance()->dm()->controllerAt(0)->canportById(CGlobal::instance()->panelAddress());
    return canport;
}

//主电故障应急启动
void CClientBusiness::mainPowerStart()
{
    qDebug() << "CClientBusiness::mainPowerStart"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CMsgNull m_MsgNUll;
    exeCommand(NCT_CancelMute, &m_MsgNUll);
    CGlobal::instance()->DataProcessing()->setSoundIcon(true);
    CGlobal::instance()->m_isEmergency = true;
    if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
        return;
    CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
    exeCommand(NCT_EmergencyStart, &m_MsgNUll);
    Emergency();
    CGlobal::instance()->TimeInterval()->uploadStatusToMqtt();
}

//主电故障应急停止
void CClientBusiness::mainPowerStop()
{
    qDebug() << "CClientBusiness::mainPowerStop"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CMsgNull m_MsgNUll;
    if(exeCommand(NCT_EmergencyStop, &m_MsgNUll))
    {
        CGlobal::instance()->m_EmergencyOperation = CGlobal::Stop;
    }
    else
    {
        CGlobal::instance()->m_HaveDialog = true;
        QFont font;
        font.setPointSize(12); // 设置字体大小为12像素
        // 在QMessageBox中设置字体
        QMessageBox messageBox;
        messageBox.setFont(font);
        QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
        messageBox.setStyleSheet(styleSheet);
        messageBox.setIcon(QMessageBox::NoIcon);
        messageBox.setWindowTitle("信息");
        messageBox.setStandardButtons(QMessageBox::Ok);
        messageBox.button(QMessageBox::Ok)->setText("确定");
        QString log;
        log = "系统应急停止失败！";
        messageBox.setText(log);
        messageBox.exec();
        CGlobal::instance()->m_HaveDialog = false;
    }
}

//对比检查数据库数据是否在线
void CClientBusiness::slotCheckLoginInfo()
{
    qDebug() << "CClientBusiness::slotCheckLoginInfo"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    deviceForbidFault df;
    df.deviceForbidFile();//读取灯具禁用表
    if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
    {
        CGlobal::instance()->DlgDevices()->getDeviceInfo();
    }
    ConfigFileManager cfg;
    cfg.ParseConfigFile();//读取注册文件
    CGlobal::instance()->DataProcessing()->slotcheckLoginInfo();
}

//带电池灯具状态
void CClientBusiness::DeviceBatteryStatus(CDevice* device, int status, int power)
{
    qDebug() << "CClientBusiness::DeviceBatteryStatus"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(device && device->deviceTypeId() < 100){
        QString batteryStatus;
        QString batteryPower;
        if(device->isDeviceForbid())
        {
            batteryStatus = "正常";
        }
        else
        {
            if(status == 0x01)
            {
                batteryStatus = "电池断线";
                device->setStatus(OBJS_DeviceBatteryOffFault,1);
                if(device->getStatus(OBJS_DeviceBatteryShortFault))
                    device->setStatus(OBJS_DeviceBatteryShortFault,0);
            }
            else if(status == 0x02)
            {
                batteryStatus = "电池短路";
                device->setStatus(OBJS_DeviceBatteryShortFault,1);
                if(device->getStatus(OBJS_DeviceBatteryOffFault))
                    device->setStatus(OBJS_DeviceBatteryOffFault,0);
            }
            else
            {
                if(device->getStatus(OBJS_DeviceBatteryOffFault))
                    device->setStatus(OBJS_DeviceBatteryOffFault,0);
                if(device->getStatus(OBJS_DeviceBatteryShortFault))
                    device->setStatus(OBJS_DeviceBatteryShortFault,0);
                if(status == 0)
                    batteryStatus = "正常";
                else if(status == 0x04)
                    batteryStatus = "电池放电";
                else if(status == 0x08)
                    batteryStatus = "电池充电";
            }
        }



        if(power == 0x01)
        {
            if(!device->isDeviceForbid())
            {
                batteryPower = "电池过放电";
                device->setStatus(OBJS_DeviceBatteryOverdischargeFault,1);
            }
            else
            {
                batteryPower = "正常";
            }
        }
        else
        {
            if(device->getStatus(OBJS_DeviceBatteryOverdischargeFault))
                device->setStatus(OBJS_DeviceBatteryOverdischargeFault,0);
            if(power == 0)
                batteryPower = "正常";
            else if(power == 0x02)
                batteryPower = "%25";
            else if(power == 0x04)
                batteryPower = "%50";
            else if(power == 0x08)
                batteryPower = "%75";
        }

        device->setDeviceValue(DEVICE_VALUE_BATTERYSTATUS,batteryStatus);
        device->setDeviceValue(DEVICE_VALUE_BATTERYPOWER,batteryPower);
        if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
        {
            CGlobal::instance()->DlgDevices()->getDeviceInfo();
        }
    }
}

//生成设备唯一码
QString CClientBusiness::generateUniqueID()
{
//    qDebug() << "CClientBusiness::generateUniqueID"
//             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    bool isUniqueID = true;
    QString filePath = "/home/xfss/root/logfile/uniquecode.txt"; // 将文件路径替换为实际的文件路径
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        // 检查文件中的唯一码是否为空
        QString uniqueCode = QString::fromUtf8(data);
        if(uniqueCode.isEmpty())
            isUniqueID = false;
        else
            return uniqueCode;
    }
    else
    {
        // 文件不存在或无法打开
        isUniqueID = false;
    }
    if(!isUniqueID)
    {
        // 执行QUuid::createUuid()方法生成唯一码
        QUuid uuid = QUuid::createUuid();
        QString uniqueCode = uuid.toString();
        // 将唯一码保存到文件中
        QString filePath = "/home/xfss/root/logfile/uniquecode.txt"; // 将文件路径替换为实际的文件路径
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out << uniqueCode;
            file.close();
//            qDebug() << "Data saved to file: " << filePath;
            isUniqueID = true;
            return uniqueCode;
        }
        else
        {
//            qDebug() << "Failed to open file for writing: " << filePath;
        }
    }
    return NULL;
}


//////////wait for deal, deal msg from libBService
void CClientBusiness::recvData(int nMsgType, QByteArray &data)
{
    Q_UNUSED(nMsgType);
    QDataStream stream(&data, QIODevice::ReadOnly);
    CMsgStructBase* msgStruct = NULL;
    int type = NCT_None;
    stream>>type>>&msgStruct;
    QList<QVariant> param;
    qDebug() << "CClientBusiness::recvData, msg type is " << type << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(!msgStruct)
        return;
    switch(type)
    {
        case NCT_ObjectStatus:
        {
            //////////////
            /////////2:distribution login
            /////////3: data
            /////////4:device login
            /////////5: status
            CMsgObjectStatus* msgObjectStatus = static_cast<CMsgObjectStatus*>(msgStruct);
            qDebug() << "CClientBusiness::recvData, NCT_ObjectStatus " << msgObjectStatus->nType  << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
            if(!CGlobal::instance()->dm()->isLoad()) return;
            CController* controller = CGlobal::instance()->controller();
            if(!controller)
                return;
            if(msgObjectStatus->nType == 0x01)
            {
                controller->setStatus(msgObjectStatus->nStatusID, msgObjectStatus->nValue);
            }
            else if(msgObjectStatus->nType == 0x02)
            {
                CCanport* canport = controller->canportByAddress(msgObjectStatus->nCanportAdd);
                if(!canport)
                    return;
                if(msgObjectStatus->strText != "")
                {
                    canport->setCanportValue(OBJECT_VALUE_ONLINE,1);
//                    CDistribution* distribution = canport->distributionByProductId(msgObjectStatus->strText);
                    CDistribution* distribution = canport->distributionByAddress(msgObjectStatus->nDisID);
                    if(!distribution)
                        distribution = createUndefinedDistribution(canport, msgObjectStatus->nDisID, msgObjectStatus->strText);
                    if(distribution)
                    {
                        if(distribution->getStatus(OBJS_DistributionCommunicationFault) == 1)
                        {
                            distribution->setloopCommunication(0);
                            distribution->setStatus(OBJS_DistributionCommunicationFault, 0);
                        }
                        distribution->setDistributionOnline(true);
                        distribution->setStatus(OBJS_Online, 1);
                        distribution->setDistributionValue(DISTRIBUTION_VALUE_ADDR,msgObjectStatus->nDisID);
                        if(msgObjectStatus->nValue >= 252 && msgObjectStatus->nValue < 255)
                            distribution->setDistributionValue(DISTRIBUTION_VALUE_NAME,"B型集中电源");
                        else if(msgObjectStatus->nValue >= 240 && msgObjectStatus->nValue < 250)
                            distribution->setDistributionValue(DISTRIBUTION_VALUE_NAME,"配电箱");
                        else if(msgObjectStatus->nValue >= 200 && msgObjectStatus->nValue < 240)
                            distribution->setDistributionValue(DISTRIBUTION_VALUE_NAME,"A型集中电源");
                        else if(msgObjectStatus->nValue >= 110 && msgObjectStatus->nValue < 130)
                            distribution->setDistributionValue(DISTRIBUTION_VALUE_NAME,"集中电源(MA)");
                        distribution->setDistributionValue(DISTRIBUTION_VALUE_CANPORTADDR, canport->canportAdd());
                        distribution->setDistributionValue(DISTRIBUTION_VALUE_TYPEID,msgObjectStatus->nValue);
                        distribution->setDistributionValue(DISTRIBUTION_VALUE_DESCRIPTION,msgObjectStatus->strText);
                        distribution->setDistributionValue(DISTRIBUTION_VALUE_NAMEDETAIL,tr("地址:%1 %2").arg(distribution->distributionValue(DISTRIBUTION_VALUE_ADDR).toInt())
                                               .arg(distribution->distributionValue(DISTRIBUTION_VALUE_NAME).toString()));
//                        distribution->setDistributionValue(DISTRIBUTION_VALUE_NOLOGIN, 0);
                        distribution->setDistributionLogin(true);
                        CLoop* loop;
                        for(int i=1; i<9; i++){
                            loop = distribution->loopByAdd(i);
                            if(!loop)
                            {
                                loop = createUndefinedLoop(distribution, i);
                                if(!loop)
                                    continue;
                                loop->setloopValue(LOOP_VALUE_ADDR,i);
                                loop->setloopValue(LOOP_VALUE_CANPORTADDR,canport->canportAdd());
                                loop->setLoopOnline(true);
//                                loop->setDeviceOnlineTotal(loop->getDeviceOnlineTotalBak());
                                loop->setLoopLogin(true);
                            }
                        }
                        //注册到的集中电源加入到注册表中,2s后保存
                        if(!CGlobal::instance()->m_bInLogin)
                        {
                            m_saveLogintimer->start(2000);
                        }
                    }
                }
            }
            else if(msgObjectStatus->nType == 0x03)
            {
                QByteArray byte;
                bool ok;
                CCanport* canport = controller->canportByAddress(msgObjectStatus->nCanportAdd);
                if(!canport)
                    return;
                if(msgObjectStatus->strdata != ""){
                    for (int i = 0; i < msgObjectStatus->strdata.size(); i += 2)
                    {
                        byte.append((char)msgObjectStatus->strdata.mid(i, 2).toInt(&ok, 16));
                    }
                    if(byte.count() < 8)
                        return;
                    int type = msgObjectStatus->strdata.mid(12, 2).toInt(&ok, 16);
                    int distributionAddress = msgObjectStatus->strdata.mid(2, 2).toInt(&ok, 16);
                    int loopAddress = msgObjectStatus->strdata.mid(4, 2).toInt(&ok, 16);
                    int deviceAddress = msgObjectStatus->strdata.mid(6, 2).toInt(&ok, 16);
                    if(type == 0x01){//读运行参数
                        CDistribution* distribution = canport->distributionByAddress(distributionAddress);
                        if(distribution){
                            if(loopAddress == 0 && deviceAddress == 0)
                            {
                                if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x01 && byte.count() == 13)
                                {
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_MAINV,
                                                           (double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_OUTV,
                                                           (double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_OUTA,
                                                           (double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/100);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x02 && byte.count() == 13)
                                {
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_EXTERNALV,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BAT1V,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BAT2V,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/10);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x03 && byte.count() == 13)
                                {
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BAT3V,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BAT1T,double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)));
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BAT2T,double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)));
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x04 && byte.count() == 13)
                                {
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BAT3T,double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)));
                                    CLoop* loop = distribution->loopByAdd(1);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/100);
                                    }
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x05 && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(2);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(3);
                                    if(loop)
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/10);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x06 && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(3);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(4);
                                    if(loop)
                                    {
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/100);
                                    }
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x07 && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(5);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(6);
                                    if(loop)
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/10);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x08 && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(6);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(7);
                                    if(loop)
                                    {
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/100);
                                    }
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x09 && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(8);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(9);
                                    if(loop)
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/10);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x0a && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(9);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(10);
                                    if(loop)
                                    {
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/100);
                                    }
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x0b && byte.count() == 13)
                                {
                                    CLoop* loop = distribution->loopByAdd(11);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/10);
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/100);
                                    }
                                    loop = distribution->loopByAdd(12);
                                    if(loop)
                                        loop->setloopValue(LOOP_VALUE_V,(double(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16)))/10);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x0c && byte.count() == 11)
                                {
                                    CLoop* loop = distribution->loopByAdd(12);
                                    if(loop){
                                        loop->setloopValue(LOOP_VALUE_A,(double(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16)))/100);
                                    }
                                    distribution->setDistributionValue(DISTRIBUTION_VALUE_BATV,(double(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)))/10);
                                }
                                else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x3f && byte.count() == 8)
                                {


                                }
                            }
                            else if(loopAddress != 0 && deviceAddress != 0)
                            {
                                if(byte.count() < 13)
                                    return;
                                    CLoop* loop = distribution->loopByAdd(loopAddress);
                                    if(loop){
                                        CDevice* device = loop->deviceByAdd(deviceAddress);
                                        if(device)
                                            DeviceBatteryStatus(device,msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16),msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16));
                                    }
                            }
                        }
                    }else if(type == 0x02){//读保护参数
                        CDistribution* distribution = canport->distributionByAddress(distributionAddress);
                        if(distribution){
                            if(byte.count() < 14)
                                return;
                            distribution->setoutA(msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16));
                            distribution->setlightswitch(msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16));
                            distribution->setCANfaultswitch(msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16));
                            distribution->setlinkageswitch(msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16));
                            distribution->setpowermode(msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16));
                            distribution->setfiretime(msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16));
                            distribution->setunfiretime(msgObjectStatus->strdata.mid(26, 2).toInt(&ok, 16));
                        }
                    }else if(type == 0x08){//读设备信息
                        if(distributionAddress == 0x3f)
                        {
                            if(byte.count() < 10)
                                return;
                            int softwareNumber = msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256 + msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16);
                            double softwareVersion = msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16)/100.0;
                            if(msgObjectStatus->nCanportAdd == 3 || msgObjectStatus->nCanportAdd == 4)
                            {
                                CGlobal::instance()->m_version_can1can2 = QString::number(softwareNumber) + " V" + QString::number(softwareVersion, 'f', 2);;
                            }
                            else if(msgObjectStatus->nCanportAdd == 5 || msgObjectStatus->nCanportAdd == 6)
                            {
                                CGlobal::instance()->m_version_can3can4 = QString::number(softwareNumber) + " V" + QString::number(softwareVersion, 'f', 2);;
                            }
                            else if(msgObjectStatus->nCanportAdd == 7 || msgObjectStatus->nCanportAdd == 8)
                            {
                                CGlobal::instance()->m_version_can5can6 = QString::number(softwareNumber) + " V" + QString::number(softwareVersion, 'f', 2);;
                            }
                            else if(msgObjectStatus->nCanportAdd == 9 || msgObjectStatus->nCanportAdd == 10)
                            {
                                CGlobal::instance()->m_version_can7can8 = QString::number(softwareNumber) + " V" + QString::number(softwareVersion, 'f', 2);;
                            }
                            CGlobal::instance()->TimeInterval()->updateVersion();
                        }
                        else if(loopAddress == 0 && deviceAddress == 0)
                        {
                            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
                            if(!distribution)
                                return;
                            if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x01)
                            {
                                if(byte.count() < 14)
                                    return;
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_CPUVERSION,msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_POWVERSION,msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_LCDVERSION,msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS1VERSION,msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS2VERSION,msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS3VERSION,msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS4VERSION,msgObjectStatus->strdata.mid(26, 2).toInt(&ok, 16));
                            }
                            else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x02)
                            {
                                if(byte.count() < 14)
                                    return;
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS5VERSION,msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS6VERSION,msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS7VERSION,msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS8VERSION,msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS9VERSION,msgObjectStatus->strdata.mid(22, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS10VERSION,msgObjectStatus->strdata.mid(24, 2).toInt(&ok, 16));
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS11VERSION,msgObjectStatus->strdata.mid(26, 2).toInt(&ok, 16));
                            }
                            else if(msgObjectStatus->strdata.mid(8, 2).toInt(&ok, 16) == 0x3f)
                            {
                                if(byte.count() < 8)
                                    return;
                                distribution->setDistributionValue(DISTRIBUTION_VALUE_ABUS12VERSION,msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16));
                            }
                        }
                        else
                        {
                            if(byte.count() < 11)
                                return;
                            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
                            if(!distribution)
                                return;
                            CLoop* loop = distribution->loopByAdd(loopAddress);
                            if(!loop)
                                return;
                            CDevice* device = loop->deviceByAdd(deviceAddress);
                            if(!device)
                                return;
                            device->setDeviceValue(DEVICE_VALUE_SOFTWARENUMBER,msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16));
                            device->setDeviceValue(DEVICE_VALUE_SOFTWAREVERSION,msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16));
                            device->setDeviceValue(DEVICE_VALUE_LOGINTYPE_ID,msgObjectStatus->strdata.mid(20, 2).toInt(&ok, 16));
//                            //服务端回复灯具软件版本信息
//                            serverLampSoftwareInfo(CGlobal::instance()->saveKeyId(OBJT_Device,device->keyId()),
//                                                   msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16)*256+msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16),msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16));
                        }
                    }else if(type == 0x11){
                        CDistribution* distribution = canport->distributionByAddress(distributionAddress);
                        if(distribution){
                            if(loopAddress == 0 && deviceAddress == 0){

                            }else{
                                CLoop* loop = distribution->loopByAdd(loopAddress);
                                if(loop){
                                    if(byte.count() < 10)
                                        return;
                                    CDevice* device = loop->deviceByAdd(deviceAddress);
                                    if(device)
                                        DeviceBatteryStatus(device,msgObjectStatus->strdata.mid(16, 2).toInt(&ok, 16),msgObjectStatus->strdata.mid(18, 2).toInt(&ok, 16));
                                }
                            }
                        }
                    }
                    else if(type == 0x77){
                        if(byte.count() < 10)
                            return;
                        CMsgObjectStatus msg;
                        msg.nDisID = distributionAddress;
                        msg.nLoopID = 0;
                        msg.nCanportAdd = canport->canportAdd();
                        if(msg.nDisID == 0){
                            return;
                        }
                        if(!exeCommand(NCT_LoginInfoLoop, &msg))
                        {
                            CGlobal::instance()->m_HaveDialog = true;
                            QFont font;
                            font.setPointSize(12); // 设置字体大小为12像素
                            // 在QMessageBox中设置字体
                            QMessageBox messageBox;
                            messageBox.setFont(font);
                            QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
                            messageBox.setStyleSheet(styleSheet);
                            messageBox.setIcon(QMessageBox::NoIcon);
                            messageBox.setWindowTitle("信息");
                            messageBox.setStandardButtons(QMessageBox::Ok);
                            messageBox.button(QMessageBox::Ok)->setText("确定");
                            QString log;
                            log = "注册失败！";
                            messageBox.setText(log);
                            messageBox.exec();
                            CGlobal::instance()->m_HaveDialog = false;
                        }
                        else
                        {
                            CGlobal::instance()->m_bInLogin = true;
                            CGlobal::instance()->InformationWindow()->setMovie(":/images/allregedit.png");
                            CGlobal::instance()->InformationWindow()->setDescription(QString("<h1><font color=black>%1</font></h1>").arg("系统注册......!"));
                            CGlobal::instance()->InformationWindow()->show();
                            CGlobal::instance()->InformationWindow()->hideCloseButton();
                            CGlobal::instance()->setMSgColor(QColor(12, 180, 3));
                            CGlobal::instance()->setMsgText("系统注册......!");
                        }
                    }
                    else if(type == 0x78){
                        if(byte.count() < 8)
                            return;
                        CDistribution* distribution = canport->distributionByAddress(distributionAddress);
                        if(distribution)
                            distribution->setloopOutStatus(msgObjectStatus->strdata.mid(14, 2).toInt(&ok, 16));
                    }
                }
            }
            else if(msgObjectStatus->nType == 0x04)
            {  //注册数据
                CCanport* canport = controller->canportByAddress(msgObjectStatus->nCanportAdd);
                if(!canport)
                    return;
                qDebug() << msgObjectStatus->strText << "=======================";
                CDistribution* distribution = canport->distributionByAddress(msgObjectStatus->nDisID);
                if(!distribution)
                {
                    distribution = createUndefinedDistribution(canport, msgObjectStatus->nDisID);
                    if(distribution)
                        distribution->setDistributionValue(DISTRIBUTION_VALUE_CANPORTADDR, canport->canportAdd());
                }
                if(distribution)
                {
                    if(!distribution->isDistributionOnline())
                    {
                        distribution->setDistributionOnline(true);
                        distribution->setStatus(OBJS_Online,1);
                    }
                    CLoop* loop;
                    for(int i=1; i<9; i++){
                        loop = distribution->loopByAdd(i);
                        if(!loop)
                        {
                            loop = createUndefinedLoop(distribution, i);
                            if(!loop)
                                continue;
                            loop->setloopValue(LOOP_VALUE_ADDR,i);
                            loop->setloopValue(LOOP_VALUE_CANPORTADDR,canport->canportAdd());
                            loop->setLoopOnline(true);
//                            loop->setDeviceOnlineTotal(loop->getDeviceOnlineTotalBak());
                            loop->setLoopLogin(true);
                        }
                    }
                    if(distribution->getStatus(OBJS_DistributionCommunicationFault) == 1)
                    {
                        distribution->setloopCommunication(0);
                        distribution->setStatus(OBJS_DistributionCommunicationFault, 0);
                    }
                    loop = distribution->loopByAdd(msgObjectStatus->nLoopID);
                    if(!loop)
                        return;

                    CDevice* device;
                    if(loop && msgObjectStatus->strText != ""){
                        device = loop->deviceByProductionId(msgObjectStatus->strText);
                        if(!device)
                        {
                            device = createUndefinedDevice(loop);
                            if(device) {
                                device->setDeviceLogin(true);
                                device->setDatabaseLogin(true);

                                device->setStatus(msgObjectStatus->nStatusID, msgObjectStatus->nValue);
                                device->setDeviceValue(DEVICE_VALUE_LOGINTYPE_ID, msgObjectStatus->nValue);
                                device->setDeviceValue(DEVICE_VALUE_DESCRIPTION, msgObjectStatus->strText);
                                device->setDeviceValue(DEVICE_VALUE_LOGINADDR, msgObjectStatus->nDeviceID);
//                                device->setDeviceValue(DEVICE_VALUE_ISUSED, msgObjectStatus->nLoginStatus);
                                device->setDeviceValue(DEVICE_VALUE_LOOPADDR, loop->loopAdd());
                                device->setDeviceValue(DEVICE_VALUE_DISTRIBUTIONADDR, distribution->distributionAddress());
                                device->setDeviceValue(DEVICE_VALUE_CANPORTADDR, canport->canportAdd());
                                device->setDeviceValue(DEVICE_VALUE_EMERGENCY, "正常");
                                device->setDeviceValue(DEVICE_VALUE_LIGHT, "正常");
                                if(msgObjectStatus->nCommunicationStatus == OBJS_Online)
                                {
                                    device->setEnableNumberChange(true);
                                    device->setDeviceOnline(true);
                                }
//                                device->setDeviceValue(DEVICE_VALUE_NOLOGIN, 0);
                            }
                        }
                        else
                        {
                            device->setDeviceLogin(true);
                            device->setDatabaseLogin(true);
                            if(!device->isDeviceOnline() || msgObjectStatus->nCommunicationStatus == OBJS_Online)
                            {
                                device->setEnableNumberChange(true);
                                device->setDeviceOnline(true);
                            }
                            if(device->getStatus(OBJS_LightCommunicationFault))
                            {
                                device->setStatus(OBJS_LightCommunicationFault,0);
                            }
                            //设备类型改变，数据库中相关参数需要删除
                            if(device->deviceValue(DEVICE_VALUE_LOGINTYPE_ID).toInt() != msgObjectStatus->nValue)
                            {
                                device->setDeviceValue(DEVICE_VALUE_LOGINTYPE_ID, msgObjectStatus->nValue);
//                                device->setDeviceValue(DEVICE_VALUE_TYPE_ID, msgObjectStatus->nValue);
//                                QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
//                                QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
//                                db.setDatabaseName(fileName);
//                                if(!db.open())
//                                    return;
//                                QSqlQuery query(db);

//                                int id = CGlobal::instance()->saveKeyId(OBJT_Device,device->keyId());
//                                query.exec(QString("DELETE FROM EvacuationPathItem WHERE LampInfoID=%1").arg(id));
//                                query.exec(QString("DELETE FROM LampConnection WHERE StartLampID=%1").arg(id));
//                                query.exec(QString("DELETE FROM LampConnection WHERE EndLampID=%1").arg(id));
//                                query.exec(QString("DELETE FROM LampDefaultDirection WHERE LampInfoID=%1").arg(id));
//                                query.exec(QString("DELETE FROM LampToFirePoint WHERE LampInfoID=%1").arg(id));
//                                query.exec(QString("DELETE FROM LampToLaunchGroup WHERE LampInfoID=%1").arg(id));
//                                if(!query.exec())
//                                {
//                                    qDebug() << query.lastError();
//                                }
//                                db.close();
                            }

                            device->setDeviceValue(DEVICE_VALUE_LOGINADDR, msgObjectStatus->nDeviceID);
                            device->setDeviceValue(DEVICE_VALUE_CHANGETYPE,0);
                        }
                        //注册到的灯具加入到注册表中,2s后保存
                        if(!CGlobal::instance()->m_bInLogin)
                        {
                            m_saveLogintimer->start(2000);
                        }
                    }
                    //该回路注册到灯具
                    loop->setLoopOnline(true);
                    loop->setLoopLogin(true);
                }
            }
            else if(msgObjectStatus->nType == 0x05)
            {   //状态判断数据
                if(msgObjectStatus->nStatusID == OBJS_FireEmergency)
                {
                    bool isFireEmergency = msgObjectStatus->nValue;
                    CFirePoint* firepoint = controller->firePointByAddress(msgObjectStatus->nDisID,
                                                                           msgObjectStatus->nLoopID,msgObjectStatus->nDeviceID);
                    if(firepoint)
                    {
                        firepoint->setStatus(OBJS_FireEmergency,msgObjectStatus->nValue);
                        firepoint->setEmergency(isFireEmergency);
                        m_emergencyFirePoints.append(firepoint);
                        if(CGlobal::instance()->m_startFirepointNumber > 1)
                        {
                            QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
                            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
                            db.setDatabaseName(fileName);
                            if(!db.open())
                                return;
                            QList<int> groups;
                            //该火警点对应分区
                            QSqlQuery queryFirePointGroup(db);
                            queryFirePointGroup.prepare(QString("SELECT g.LaunchGroupID from LampToLaunchGroup g "
                                                               " left join LampToFirePoint f on f.LampInfoID=g.LampInfoID "
                                                               " where f.FirePointID=%1").arg(firepoint->firePointId()));
                            if(!queryFirePointGroup.exec())
                            {
                                qDebug() << "queryFirePointGroup Error:" << queryFirePointGroup.lastError().text();
                                return;
                            }
                            while(queryFirePointGroup.next())
                            {
                                int groupID = queryFirePointGroup.value(0).toInt();
                                if(groups.contains(groupID))
                                    continue;
                                groups.append(groupID);
                                firepoint->setFirePointValue(FIREPOINT_VALUE_GROUP,groupID);
                            }
                            int emergencyFirePointNumber = 0;
                            for(int i=0; i<m_emergencyFirePoints.count(); i++)
                            {
                                if(groups.contains(m_emergencyFirePoints.at(i)->firePointValue(FIREPOINT_VALUE_GROUP).toInt()))
                                    emergencyFirePointNumber = emergencyFirePointNumber + 1;
                            }
                            if(emergencyFirePointNumber < CGlobal::instance()->m_startFirepointNumber)
                            {
                                return;
                            }
                        }
                        controller->setStatus(OBJS_FireEmergency,isFireEmergency);
                        CMsgNull m_MsgNUll;
                        CGlobal::instance()->ClientBusiness()->exeCommand(NCT_CancelMute, &m_MsgNUll);
                        CGlobal::instance()->DataProcessing()->setSoundIcon(true);
                        CGlobal::instance()->ClientBusiness()->exeCommand(NCT_AutoFire, &m_MsgNUll);
                        if(CGlobal::instance()->m_emergencyOnlyDistribution)
                        {
                            CGlobal::instance()->ClientBusiness()->firePointEmergencyByDistribution(firepoint->firePointId());
                        }
                        else
                        {
                            if(CGlobal::instance()->m_nStartRule == RULE_OnlyGroup)
                                CGlobal::instance()->ClientBusiness()->firePointEmergencyByGroup(firepoint->firePointId());
                            else if(CGlobal::instance()->m_nStartRule == RULE_OnlyPage)
                                CGlobal::instance()->ClientBusiness()->firePointEmergencyByLayoutPage(firepoint->firePointId());
                            else
                            {
                                CMsgObjectStatus msgObjectStatus;
                                msgObjectStatus.nValue = isFireEmergency;
                                CGlobal::instance()->ClientBusiness()->exeCommand(NCT_Emergency, &msgObjectStatus);
                            }
                        }
                    }
                    else if(!CGlobal::instance()->m_isShieldUnknownFirePoint)
                    {
                        bool isUnknownFirePointHasContained = false;

                        for(int i=0; i<m_unknowFirePoints.count(); i++)
                        {
                            int address = m_unknowFirePoints.at(i)->firePointAddress();
                            int deviceAddress = m_unknowFirePoints.at(i)->firePointDeviceAddress();
                            int loopAddress = m_unknowFirePoints.at(i)->firePointLoopAddress();
                            if((msgObjectStatus->nDeviceID == deviceAddress) ||
                                    (msgObjectStatus->nDisID == loopAddress) ||
                                    (msgObjectStatus->nDeviceID == address))
                                isUnknownFirePointHasContained = true;
                        }
                        if(!isUnknownFirePointHasContained)
                        {
                            CFirePoint* firepoint = new CFirePoint;
                            firepoint->setFirePointValue(FIREPOINT_VALUE_ADDRESS, msgObjectStatus->nDeviceID);
                            firepoint->setFirePointValue(FIREPOINT_VALUE_DEVICEADDRESS, msgObjectStatus->nDisID);
                            firepoint->setFirePointValue(FIREPOINT_VALUE_LOOPADDRESS, msgObjectStatus->nLoopID);
                            firepoint->setStatus(OBJS_UnknownFireEmergency, isFireEmergency);
                            m_unknowFirePoints.append(firepoint);
                        }

                        if(m_unknowFirePoints.count() >= CGlobal::instance()->m_startFirepointNumber)
                        {
                            CMsgObjectStatus msg;
                            msg.nValue = isFireEmergency;
                            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_Emergency, &msg);
                            controller->setStatus(OBJS_UnknownFireEmergency,isFireEmergency);
                        }
                    }
                }
                else
                {
                    if(msgObjectStatus->nDisID == 0)
                    {
                        QString batteryStatus;
                        if(CGlobal::instance()->m_isHideBatPowerFaultShow && (msgObjectStatus->nStatusID == OBJS_StandbyPowerOff ||
                           msgObjectStatus->nStatusID == OBJS_StandbyPowerShort || msgObjectStatus->nStatusID == OBJS_StandbyPowerUndervoltage))
                            return;
                        controller->setStatus(msgObjectStatus->nStatusID,msgObjectStatus->nValue);
                        if(msgObjectStatus->nStatusID == OBJS_MainPowerFault )
                        {
                            if(msgObjectStatus->nValue)
                            {
                                if(!CGlobal::instance()->m_isShieldMainPowerFaultEmergency)
                                {
                                    mainPowerStart();
                                    m_mainPowerStoptimer->start(10800000);
                                }
                            }
                            else
                            {
                                mainPowerStop();
                                CGlobal::instance()->TopToolBar()->resetSystem();
                                m_mainPowerStoptimer->stop();
                            }
                        }
                        if(controller->getStatus(OBJS_StandbyPowerOff))
                            batteryStatus = "断线";
                        else if(controller->getStatus(OBJS_StandbyPowerShort))
                            batteryStatus = "短路";
                        else if(controller->getStatus(OBJS_StandbyPowerUndervoltage))
                            batteryStatus = "欠压";
                        else
                            batteryStatus = "正常";
                        emit statusSendToMQTT(controller);
                    }
                    else
                    {
                        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(msgObjectStatus->nCanportAdd);
//                        if(!canport)
//                            canport = createUndefinedCanport(CGlobal::instance()->controller(), msgObjectStatus->nCanportAdd);
                        //状态上传前先读取一下注册表，配置CAN设备名称。只在第一次收到CAN设备时执行（防止刚开机时收到CAN设备状态时，CAN设备名称还未配置）
                        if(m_isCANconfig == false)
                        {
                            m_isCANconfig = true;
//                            slotCheckLoginInfo();
                        }
                        if(!canport)
                            return;
                        CDistribution* distribution = canport->distributionByAddress(msgObjectStatus->nDisID);
                        CLoop* loop;
                        if(distribution)
                        {
                            if(msgObjectStatus->nLoopID == 0 && msgObjectStatus->nDeviceID == 0)
                            {
                                //主电故障
                                if(msgObjectStatus->nStatusID == OBJS_MainPowerFault)
                                {
                                    distribution->setmainPowerFault(msgObjectStatus->nValue);
                                    emit statusSendToMQTT(distribution);
                                }
                                //备电断线
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryOffFault)
                                {

                                }
                                //备电短路
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryShortFault)
                                {

                                }
                                //集中电源备电故障
                                else if(msgObjectStatus->nStatusID == OBJS_StandbyPowerFault)
                                {
                                    distribution->setbackupPowerFault(msgObjectStatus->nValue);
                                    emit statusSendToMQTT(distribution);
                                }
                                //集中电源输出过载
                                else if(msgObjectStatus->nStatusID == OBJS_LoopOutOverloadFault)
                                {
                                    distribution->setoverOut(msgObjectStatus->nValue);
                                }
                                //集中电源输出开路
                                else if(msgObjectStatus->nStatusID == OBJS_PowerKaiLuFault)
                                {
                                    distribution->setoutOpen(msgObjectStatus->nValue);
                                }
                                //集中电源备电欠压（通用）
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault)
                                {
                                    distribution->setbatUndervoltage(msgObjectStatus->nValue);
                                }
                                //集中电源电池欠压
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault_1 ||
                                        msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault_2 ||
                                        msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault_3)
                                {
                                    if(msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault_1)
                                        distribution->setbat1Undervoltage(msgObjectStatus->nValue);
                                    else if(msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault_2)
                                        distribution->setbat2Undervoltage(msgObjectStatus->nValue);
                                    else if(msgObjectStatus->nStatusID == OBJS_BatteryLowVoltageFault_3)
                                        distribution->setbat3Undervoltage(msgObjectStatus->nValue);
                                    distribution->setbatUndervoltage(msgObjectStatus->nValue);
                                }
                                //集中电源24/36V输出故障
                                else if(msgObjectStatus->nStatusID == OBJS_PowerOutputFault)
                                {
                                    distribution->set36vOut(msgObjectStatus->nValue);
                                }
                                //集中电源系统故障
                                else if(msgObjectStatus->nStatusID == OBJS_SystemFault)
                                {
                                    distribution->setsystemFault(msgObjectStatus->nValue);
                                }
                                //集中电源充电器故障
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryOverDischargeFault)
                                {
                                    distribution->setchargeFault(msgObjectStatus->nValue);
                                }
                                //集中电源过放电故障
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryLowQuantityFault)
                                {
                                    distribution->setoverDischargeFault(msgObjectStatus->nValue);
                                }
                                //集中电源电池高温报警
                                else if(msgObjectStatus->nStatusID == OBJS_BatteryOverheating)
                                {
                                    distribution->setbatOverheating(msgObjectStatus->nValue);
                                }
                                //集中电源运行模式
                                else if(msgObjectStatus->nStatusID == OBJS_RunMode)
                                {
                                    distribution->setrunMode(msgObjectStatus->nValue);
                                }
                                //集中电源充电
                                else if(msgObjectStatus->nStatusID == OBJS_ChargeStatus)
                                {
                                    distribution->setchargeStatus(msgObjectStatus->nValue);
                                }
                                //集中电源应急
                                else if(msgObjectStatus->nStatusID == OBJS_ManualEmergency ||
                                        msgObjectStatus->nStatusID == OBJS_ForceEmergency ||
                                        msgObjectStatus->nStatusID == OBJS_DIEmergency ||
                                        msgObjectStatus->nStatusID == OBJS_TestEmergency ||
                                        msgObjectStatus->nStatusID == OBJS_SystemEmergency ||
                                        msgObjectStatus->nStatusID == OBJS_UndervoltageEmergency ||
                                        msgObjectStatus->nStatusID == OBJS_AutoEmergency)
                                {
                                    if(distribution->getemergencyStatus() != msgObjectStatus->nValue)
                                    {
                                        distribution->setemergencyStatus(msgObjectStatus->nValue);
                                        emit statusSendToMQTT(distribution, true);
                                    }

//                                    QList<CLoop*> loops = distribution->loops();
//                                    for(int i=0; i<loops.count(); i++){
//                                        CLoop* loop = loops.at(i);
//                                        //回路存在、通讯正常、注册表该回路有灯具
//                                        if(loop && !loop->getStatus(OBJS_LoopCommunicationFault) &&
//                                                loop->isLoopOnline() && loop->isLoopLogin())
//                                        {
//                                            QList<CDevice*> devices = loop->devices();
//                                            for(int m=0; m<devices.count(); m++){
//                                                CDevice* device = devices.at(m);
//                                                if(device && (!device->getStatus(OBJS_DistributionCommunicationFault) || device->deviceTypeId() < 100))
//                                                {
//                                                    device->setStatus(msgObjectStatus->nStatusID,msgObjectStatus->nValue);
//                                                    if(msgObjectStatus->nValue == 1)
//                                                        device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"应急");
//                                                    else
//                                                        device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"正常");
//                                                    //上传灯具状态到云平台/客户端
//                                                    uploadLampStatus(device);
//                                                }
//                                                QApplication::processEvents();
//                                            }
//                                            devices.clear();
//                                        }
//                                    }
//                                    loops.clear();
                                    //列表视图界面灯具状态更新
                                    if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
                                    {
                                        CGlobal::instance()->DlgDevices()->getDeviceInfo();
                                    }
                                    //布局视图界面灯具状态更新
                                    CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
                                }
//                                //服务端上报集中电源状态
//                                serverCentralizedPowerStateUpload(distribution);

                                if(msgObjectStatus->nStatusID != OBJS_DistributionCommunicationFault)
                                    distribution->setStatus(msgObjectStatus->nStatusID,msgObjectStatus->nValue);
                            }
                            //集中电源通讯故障
                            if(msgObjectStatus->nStatusID == OBJS_DistributionCommunicationFault
                                    && (distribution->getStatus(OBJS_DistributionCommunicationFault) != msgObjectStatus->nValue))
                            {
                                if(CGlobal::instance()->m_isShieldCanDeviceComFault)
                                    return;
                                emit statusSendToMQTT(distribution, true);
                                if(msgObjectStatus->nValue)
                                {
                                    distribution->setDistributionOnline(false);
                                    distribution->setStatus(OBJS_Online, 0);
                                }
                                else
                                {
                                    distribution->setDistributionOnline(true);
                                    distribution->setStatus(OBJS_Online, 1);
                                }
                                distribution->setStatus(OBJS_DistributionCommunicationFault, msgObjectStatus->nValue);
                                if(!msgObjectStatus->nValue)
                                {
                                    distribution->setloopCommunication(0);
                                }
                                else
                                {
                                    distribution->setloopCommunication(0xFF);
                                }
                                QList<CLoop*> loops = distribution->loops();
                                for(int i=0; i<loops.count(); i++){
                                    CLoop* loop = loops.at(i);
                                    //回路存在、通讯正常、注册表该回路有灯具
                                    if(loop)
                                    {
                                        if(msgObjectStatus->nValue)
                                        {
                                            loop->setLoopOnline(false);
                                            //回路通讯故障时灯具数量备份后清零
                                            loop->setDeviceOnlineTotalBak(loop->getDeviceOnlineTotal());
                                            loop->setDeviceOnlineTotal(0);
                                        }
                                        else
                                        {
                                            loop->setLoopOnline(true);
                                            //回路通讯正常复位灯具数量
                                            loop->setDeviceOnlineTotal(loop->getDeviceOnlineTotalBak());
                                        }
                                    }
                                }
                                loops.clear();
                                //列表视图界面灯具状态更新
                                if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
                                {
                                    CGlobal::instance()->DlgDevices()->getDeviceInfo();
                                }
                                //布局视图界面灯具状态更新
                                CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
                            }
                            //回路通讯故障
                            if(msgObjectStatus->nStatusID == OBJS_LoopCommunicationFault)
                            {
                                loop = distribution->loopByAdd(msgObjectStatus->nLoopID);
                                if(!loop)
                                    return;
                                if((loop->getStatus(OBJS_LoopCommunicationFault) != msgObjectStatus->nValue) && (loop->deviceCount() > 0))
                                {
                                    loop->setStatus(OBJS_LoopCommunicationFault, msgObjectStatus->nValue);
                                    if(msgObjectStatus->nValue)
                                    {
                                        loop->setLoopOnline(false);
                                        //回路通讯故障时灯具数量备份后清零
                                        loop->setDeviceOnlineTotalBak(loop->getDeviceOnlineTotal());
                                        loop->setDeviceOnlineTotal(0);
                                    }
                                    else
                                    {
                                        loop->setLoopOnline(true);
                                        //回路通讯正常复位灯具数量
                                        loop->setDeviceOnlineTotal(loop->getDeviceOnlineTotalBak());
                                    }
                                    if(msgObjectStatus->nValue)
                                        distribution->setloopCommunication(distribution->getloopCommunication() | (0x01 << (loop->loopAdd()-1)));
                                    else
                                        distribution->setloopCommunication(distribution->getloopCommunication() & (~(0x01 << (loop->loopAdd()-1))));
                                    //列表视图界面灯具状态更新
                                    if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
                                    {
                                        CGlobal::instance()->DlgDevices()->getDeviceInfo();
                                    }
                                    //布局视图界面灯具状态更新
                                    CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
                                    emit statusSendToMQTT(loop);
                                }  
                            }
                            //集中电源回路输出开路
                            else if(msgObjectStatus->nStatusID == OBJS_OutLoopFault)
                            {
                                QList<CLoop*> loops = distribution->loops();
                                for(int i=0; i<loops.count(); i++)
                                {
                                    CLoop* loop = loops.at(i);
                                    if(loop)
                                    {
                                        if((loop->loopAdd() == msgObjectStatus->nLoopID) || (msgObjectStatus->nLoopID == 0))
                                        {
                                            loop->setStatus(msgObjectStatus->nStatusID,msgObjectStatus->nValue);
                                            if(msgObjectStatus->nValue)
                                                distribution->setloopOpen(distribution->getloopOpen() | (0x01 << (loop->loopAdd()-1)));
                                            else
                                                distribution->setloopOpen(distribution->getloopOpen() & (~(0x01 << (loop->loopAdd()-1))));
                                        }
                                    }
                                }
                                loops.clear();
                                //列表视图界面灯具状态更新
                                if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
                                {
                                    CGlobal::instance()->DlgDevices()->getDeviceInfo();
                                }
                                //布局视图界面灯具状态更新
                                CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
                            }
                            //灯具通讯故障
                            else if(msgObjectStatus->nStatusID == OBJS_LightCommunicationFault)
                            {
                                loop = distribution->loopByAdd(msgObjectStatus->nLoopID);
                                if(loop)
                                {
                                    CDevice* device = loop->deviceByAdd(msgObjectStatus->nDeviceID);
                                    //配置过的灯具才会报故障
                                    if(device && (device->getStatus(OBJS_LightCommunicationFault) != msgObjectStatus->nValue) &&
//                                            (device->deviceValue(DEVICE_VALUE_ISUSED) == 1 || device->deviceValue(DEVICE_VALUE_ISUSED) == 0))
                                            device->isDeviceConfig())
                                    {
                                        if(CGlobal::instance()->m_isShieldLampComFault)
                                            return;
                                        if(!device->isDeviceForbid() && device->isDeviceLogin())
                                        {
                                            if(msgObjectStatus->nValue)
                                            {
                                                device->setEnableNumberChange(true);
                                                device->setDeviceOnline(false);
                                            }
                                            else
                                            {
                                                device->setEnableNumberChange(true);
                                                device->setDeviceOnline(true);
                                            }
                                            device->setStatus(OBJS_LightCommunicationFault, msgObjectStatus->nValue);
                                            if(msgObjectStatus->nValue == true)
                                            {
                                                device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"正常");
                                                device->setDeviceValue(DEVICE_VALUE_LIGHT,"正常");
                                            }
                                        }
                                        emit statusSendToMQTT(device);

                                        //列表视图界面灯具状态更新
                                        if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
                                        {
                                            CGlobal::instance()->DlgDevices()->getDeviceInfo();
                                        }
                                        //布局视图界面灯具状态更新
                                        CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
                                    }
                                } 
                            }
                            //灯具光源故障
                            else if(msgObjectStatus->nStatusID == OBJS_LightFault)
                            {
                                loop = distribution->loopByAdd(msgObjectStatus->nLoopID);
                                if(loop)
                                {
                                    CDevice* device = loop->deviceByAdd(msgObjectStatus->nDeviceID);
                                    //配置过的灯具才会报故障
                                    if(device && (!device->getStatus(OBJS_LightCommunicationFault)) &&
                                            device->isDeviceConfig())
                                    {
                                        if((deviceType(device->deviceTypeId()) == NCT_LightType && CGlobal::instance()->m_isShieldLightLampLightFault)
                                                || (deviceType(device->deviceTypeId()) == NCT_ArrowType && CGlobal::instance()->m_isShieldArrowLampLightFault)
                                                || (deviceType(device->deviceTypeId()) == NCT_UndergroundType && CGlobal::instance()->m_isShieldUndergroundLampLightFault))
                                            return;
                                        if(device->getStatus(OBJS_LightFault) == msgObjectStatus->nValue)
                                            return;
                                        if(!device->isDeviceForbid())
                                        {
                                            device->setStatus(OBJS_LightFault, msgObjectStatus->nValue);
                                            if(msgObjectStatus->nValue == 1)
                                                device->setDeviceValue(DEVICE_VALUE_LIGHT,"光源故障");
                                            else
                                                device->setDeviceValue(DEVICE_VALUE_LIGHT,"正常");
                                            emit statusSendToMQTT(device);
                                            //列表视图界面灯具状态更新
                                            if(CGlobal::instance()->centerFrameContainer()->currentWidget() == CGlobal::instance()->DlgDevices())
                                            {
                                                CGlobal::instance()->DlgDevices()->getDeviceInfo();
                                            }
                                            //布局视图界面灯具状态更新
                                            CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break;
        }
        case NCT_PowerInfo:
        {

            break;
        }
        case NCT_Log:
        {
            CMsgLog* msgLog = static_cast<CMsgLog*>(msgStruct);
            CMsgLog *tempMsgLog = new CMsgLog;
            tempMsgLog->EventTypeID = msgLog->EventTypeID;
            tempMsgLog->User = msgLog->User;
            tempMsgLog->Time = msgLog->Time;
            tempMsgLog->Remark = msgLog->Remark;
            tempMsgLog->Type = msgLog->Type;
            tempMsgLog->Canport = msgLog->Canport;
            tempMsgLog->CanDeviceAddress = msgLog->CanDeviceAddress;
            tempMsgLog->Loop = msgLog->Loop;
            tempMsgLog->LampDeviceAddress = msgLog->LampDeviceAddress;
            tempMsgLog->Area = msgLog->Area;
            tempMsgLog->Location = msgLog->Location;
            emit commandResult(type, tempMsgLog);
            break;
        }
        case NCT_Reset://reset button
        {
            if(verifyAdminUser(type)){
                CGlobal::instance()->dm()->clearStatusObjects(true);
                exeCommand(type, msgStruct);
                m_faultObjects.clear();
                m_startObjects.clear();
//                CMsgLedInfo msgLed;
//                msgLed.nLedID = 6;
//                msgLed.nLedStatus = m_faultObjects.isEmpty()?0:1;
//                exeCommand(NCT_LedStatus, &msgLed);
            }
            break;
        }
        case NCT_Mute://mute button
        {
            param.append(true);
            emit notifyInformation(NIT_Mute, param);
            exeCommand(type, msgStruct);
            break;
        }
        case NCT_CancelMute:
        {
            param.append(false);
            emit notifyInformation(NIT_Mute, param);
            exeCommand(type, msgStruct);
            break;
        }
        case NCT_InputEmergency://开关量应急
        {
            if(CGlobal::instance()->m_EmergencyOperation != CGlobal::Start)
            {
                if(CGlobal::instance()->m_EvacuationMode == CGlobal::Manual)
                {
                    dlgAdministrator m_Administrator;
                    m_Administrator.setWindowTitle("用户验证");
                    m_Administrator.setUserDisabled(true);
                    if(QDialog::Accepted == m_Administrator.exec())
                    {
                        InputEmergency();
                    }
                }
                else
                {
                    InputEmergency();
                }
            }
            break;
        }
        case NCT_ActiveInputEmergency://有源输入应急
        {
            if(CGlobal::instance()->m_EmergencyOperation != CGlobal::Start)
            {
                if(CGlobal::instance()->m_EvacuationMode == CGlobal::Manual)
                {
                    dlgAdministrator m_Administrator;
                    m_Administrator.setWindowTitle("用户验证");
                    m_Administrator.setUserDisabled(true);
                    if(QDialog::Accepted == m_Administrator.exec())
                    {
                        ActiveInputEmergency();
                    }
                }
                else
                {
                    ActiveInputEmergency();
                }
            }
            break;
        }
        case NCT_PassiveInputEmergency://无源输入应急
        {
            if(CGlobal::instance()->m_EmergencyOperation != CGlobal::Start)
            {
                if(CGlobal::instance()->m_EvacuationMode == CGlobal::Manual)
                {
                    dlgAdministrator m_Administrator;
                    m_Administrator.setWindowTitle("用户验证");
                    m_Administrator.setUserDisabled(true);
                    if(QDialog::Accepted == m_Administrator.exec())
                    {
                        PassiveInputEmergency();
                    }
                }
                else
                {
                    PassiveInputEmergency();
                }
            }
            break;
        }
        case NCT_ForceEmergency://强启按钮
        {
            ForceEmergency();
            break;
        }
        case NCT_ControllerParam:
        {
            QString paramdata = static_cast<CMsgObjectStatus*>(msgStruct)->strdata;
            bool ok;
            if(paramdata.count() < 7)
                return;
            CController* controller = CGlobal::instance()->controller();
            double mainPower = (paramdata.mid(0, 2).toInt(&ok, 16) + paramdata.mid(2, 2).toInt(&ok, 16)*256)/100.0;   //主电电压
            double batPower = (paramdata.mid(4, 2).toInt(&ok, 16) + paramdata.mid(6, 2).toInt(&ok, 16)*256)/100.0;    //备电电压
            controller->setControllerValue(CONTROLLER_VALUE_MAINPOWER, mainPower);
            controller->setControllerValue(CONTROLLER_VALUE_BATPOWER, batPower);
            //灯键板软件版本
            int softwareNumber =  paramdata.mid(8, 2).toInt(&ok, 16) + paramdata.mid(10, 2).toInt(&ok, 16)*256;
            double softwareVersion =  paramdata.mid(12, 2).toInt(&ok, 16)/100.0;
            QString version_ledkey = QString::number(softwareNumber) + " V" + QString::number(softwareVersion, 'f', 2);;
            if(version_ledkey != CGlobal::instance()->m_version_ledkey)
            {
                CGlobal::instance()->m_version_ledkey = version_ledkey;
                CGlobal::instance()->TimeInterval()->updateVersion();
            }
            break;
        }
        case NCT_TestLinkageCom:
        {
            CGlobal::instance()->TimeInterval()->setTestLinkageComResult("成功！");
            break;
        }
        case NCT_LinkageComStatus:
        {
            CGlobal::instance()->TimeInterval()->setLinkageComStatus("已连接");
            m_linkageComTimer->start(2000);
            break;
        }
        case NCT_AutomaticEvacuation://auto button
            CGlobal::instance()->TopToolBar()->slotAuto();
            break;
        case NCT_ManualEvacuation://manual button
            CGlobal::instance()->TopToolBar()->slotManual();
            break;
        case NCT_CheckTimeSync:
        {
            CMsgCheckTime* checkTime = static_cast<CMsgCheckTime*>(msgStruct);
            param.append(checkTime->monthCheckTime);
            param.append(checkTime->yearCheckTime);
            param.append(checkTime->speedMonthCheckTime);
            param.append(checkTime->speedYearCheckTime);
            param.append(checkTime->systemCurrentTime);
            emit notifyInformation(NIT_CheckTimeUpdate, param);
            break;
        }
        case NCT_PrintSet:
        {
            CMsgPrintSet* printSet = static_cast<CMsgPrintSet*>(msgStruct);
            m_printSet.printLendon = printSet->printLendon;
            m_printSet.printFault = printSet->printFault;
            m_printSet.printOther = printSet->printOther;
            break;
        }
        case NCT_CheckSet:
        {
            CMsgCheckSet* checkSet = static_cast<CMsgCheckSet*>(msgStruct);
            m_checkSet.yearCycle = checkSet->yearCycle;
            m_checkSet.yearDuration = checkSet->yearDuration;
            m_checkSet.monthCycle = checkSet->monthCycle;
            m_checkSet.monthDuration = checkSet->monthDuration;
            break;
        }
        case NCT_FactoryReset:
        {
            if(CGlobal::instance()->dm()->isLoad())
                CGlobal::instance()->programTreeView()->closeController();
            clearProjectFile();
            if(!CGlobal::instance()->dm()->isLoad())
            {
                CGlobal::instance()->dm()->loadDefault();
                CController* controller = CGlobal::instance()->dm()->controllerAt(0);
                CGlobal::instance()->programTreeView()->setController(controller);
                CGlobal::instance()->designTreeView()->setController(controller);
                CGlobal::instance()->designTreeView()->setCurrentView(1);
            }
            break;
        }
        case NCT_CanportInfo:
        {
            CMsgCanportInfo* msgCanportInfo = static_cast<CMsgCanportInfo*>(msgStruct);
            m_canportInfo.address = msgCanportInfo->address;
            m_canportInfo.netType = msgCanportInfo->netType;
            qDebug()<<"CanportInfo:"<<m_canportInfo.address<<m_canportInfo.netType;
            break;
        }
        case NCT_SelfCheckStart://self check button
        {
            emit notifyInformation(NIT_SelfCheckStart, QList<QVariant>());
            break;
        }
        case NCT_SelfCheckStop:
        {
            emit notifyInformation(NIT_SelfCheckStop, QList<QVariant>());
            break;
        }
        case NCT_StartCommunication:
        {
            if(!m_isInitController)
            {
                InitController();
                param.append(CGlobal::instance()->panelAddress());
                emit notifyInformation(NIT_Start, param);
            }
            break;
        }
        case NCT_StopCommunication:
        {
            param.append(CGlobal::instance()->panelAddress());
            emit notifyInformation(NIT_Stop, param);
            break;
        }
        case NCT_MonthCheckBegin:
        {
            qDebug()<<"NCT_MonthCheckBegin";
            CGlobal::instance()->m_isMonthEmergency = true;
            CMsgObjectStatus* objectStatus = static_cast<CMsgObjectStatus*>(msgStruct);
            int time = objectStatus->nValue;
            if(time == CGlobal::instance()->m_MonthCheckSpanSecond)
            {
                emit notifyInformation(NIT_MonthCheckBegin, param);
            }
            else
            {
                int min = time/60;
                int sec = time%60;
                QString str = QString("%1分 %2秒")
                        .arg(min, 2, 10, QChar('0'))  // 格式化分钟数，宽度2，用'0'填充
                        .arg(sec, 2, 10, QChar('0')); // 格式化秒数，宽度2，用'0'填充
                CGlobal::instance()->InformationWindow()->setLiftTime(str);
            }
            break;
        }
        case NCT_MonthCheckEnd:
        {
            qDebug()<<"NCT_MonthCheckEnd";
            CGlobal::instance()->m_isMonthEmergency = false;
            emit notifyInformation(NIT_MonthCheckEnd, param);
            break;
        }
        case NCT_YearCheckBegin:
        {
            CMsgObjectStatus* objectStatus = static_cast<CMsgObjectStatus*>(msgStruct);
            CGlobal::instance()->m_isYearEmergency = true;
            int time = objectStatus->nValue;
            if(time == CGlobal::instance()->m_YearCheckSpanSecond * 60)
            {
                emit notifyInformation(NIT_YearCheckBegin, param);
            }
            else
            {
                int min = time/60;
                int sec = time%60;
                QString str = QString("%1分 %2秒")
                        .arg(min, 2, 10, QChar('0'))  // 格式化分钟数，宽度2，用'0'填充
                        .arg(sec, 2, 10, QChar('0')); // 格式化秒数，宽度2，用'0'填充
                CGlobal::instance()->InformationWindow()->setLiftTime(str);
            }
            break;
        }
        case NCT_YearCheckEnd:
        {
            CGlobal::instance()->m_isYearEmergency = false;
            emit notifyInformation(NIT_YearCheckEnd, param);
            break;
        }
        case NCT_UndefinedObject:
        {
            break;
        }
        case NCT_ClientReset:
        {
            reset();
            break;
        }
        case NCT_HasFASSystem:
        {
            qDebug()<<"NCT_HasFASSystem";
            emit notifyInformation(NIT_HasFASSystem, param);
            break;
        }
        case NCT_ExitProgram:
        {
            qDebug()<<"NCT_ExitProgram";
            emit notifyInformation(NIT_ExitProgram, param);
            break;
        }
        case NCT_StartSpeedUp:
        {
            qDebug()<<"NCT_StartSpeedUp";
            emit notifyInformation(NIT_StartSpeedUp, param);
            break;
        }
        case NCT_StopSpeedUp:
        {
            qDebug()<<"NCT_StopSpeedUp";
            emit notifyInformation(NIT_StopSpeedUp, param);
            break;
        }
        case NCT_Relogin:
        {
            emit notifyInformation(NIT_Relogin, param);
//            CGlobal::instance()->DlgDevices()->getDeviceInfo();
            CGlobal::instance()->m_bInLogin = false;
            CGlobal::instance()->setMSgColor(QColor(12, 180, 3));
            CGlobal::instance()->setMsgText("系统运行！");
            //更新回路是否清除注册状态
            updateIsLoopRemoveLogin();
            break;
        }
        case NCT_RecordPage:
        {
            CGlobal::instance()->SystemRecord()->setPage(1);//返回第一页
            break;
        }
        default:
            break;
    }
    delete msgStruct;
}

void CClientBusiness::DeviceResetStatus()
{
    qDebug() << "CClientBusiness::DeviceResetStatus"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    //单控灯具复位
    deviceControl devicecontrol;
    devicecontrol.restDeviceControl();
}

void CClientBusiness::DeviceDefaultResetStatus()
{
    qDebug() << "CClientBusiness::DeviceDefaultResetStatus"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    //默认方向单控灯具复位
    deviceDefaultControl defaultcontrol;
    defaultcontrol.restDeviceDefaultControl();
}

void CClientBusiness::FirepointResetStatus()
{
    QList<CFirePoint*> firepoints = CGlobal::instance()->controller()->firepoints();
    for(int i=0; i<firepoints.count(); i++)
    {
        CFirePoint* firepoint = firepoints.at(i);
        if(firepoint)
        {
            if(firepoint->isSimulateEmergency())
            {
                firepoint->setSimulateEmergency(false);
                firepoint->setStatus(OBJS_SimulateFireEmergency,0);
            }
            if(firepoint->isEmergency())
            {
                firepoint->setEmergency(false);
                firepoint->setStatus(OBJS_FireEmergency,0);
            }
        }
    }
    m_emergencyFirePoints.clear();
    m_unknowFirePoints.clear();
}

void CClientBusiness::ForceEmergency()
{
    qDebug() << "CClientBusiness::ForceEmergency"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(CGlobal::instance()->m_HaveDialog)
        return;
    dlgAdministrator m_Administrator;
    m_Administrator.setWindowTitle("用户验证");
    m_Administrator.setUserDisabled(true);
    if(QDialog::Accepted == m_Administrator.exec())
    {
        CMsgNull m_MsgNUll;
        exeCommand(NCT_CancelMute, &m_MsgNUll);
        CGlobal::instance()->DataProcessing()->setSoundIcon(true);
        if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
            return;
        CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
        exeCommand(NCT_ForceEmergency, &m_MsgNUll);
        Emergency();
    }
}

void CClientBusiness::InputEmergency()
{
    qDebug() << "CClientBusiness::InputEmergency"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CMsgNull m_MsgNUll;
    exeCommand(NCT_CancelMute, &m_MsgNUll);
    CGlobal::instance()->DataProcessing()->setSoundIcon(true);
    if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
        return;
    CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
    exeCommand(NCT_InputEmergency, &m_MsgNUll);
    Emergency();
}

void CClientBusiness::ActiveInputEmergency()
{
    qDebug() << "CClientBusiness::ActiveInputEmergency"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CMsgNull m_MsgNUll;
    exeCommand(NCT_CancelMute, &m_MsgNUll);
    CGlobal::instance()->DataProcessing()->setSoundIcon(true);
    if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
        return;
    CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
    exeCommand(NCT_ActiveInputEmergency, &m_MsgNUll);
    Emergency();
}

void CClientBusiness::PassiveInputEmergency()
{
    qDebug() << "CClientBusiness::PassiveInputEmergency"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
        return;
    CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
    CMsgNull m_MsgNUll;
    exeCommand(NCT_PassiveInputEmergency, &m_MsgNUll);
    Emergency();
}

void CClientBusiness::slot_flashControl()
{
    foreach (CMsgObjectStatus* msg, m_msg)
    {
        exeCommand(NCT_FlashControl, msg);
        if(CGlobal::instance()->m_lampEmergencyType & 0x02)
        {
            //发送应急指令
            exeCommand(NCT_Emergency, msg);
        }
    }
    m_msg.clear();
    if(CGlobal::instance()->m_nStartRule == RULE_AllStart)
    {
        CMsgObjectStatus msgObjectStatus;
        msgObjectStatus.nValue = true;
        exeCommand(NCT_Emergency, &msgObjectStatus);
    }
    m_flashTimer->stop();
}

void CClientBusiness::slot_linkageComStatus()
{
    CGlobal::instance()->TimeInterval()->setLinkageComStatus("未连接");
}

void CClientBusiness::lampControl(CDevice* device, bool isDoubleDirection, bool isLeft)
{
    int direction = 0;
    bool isReverse = false;
    if(device->deviceValue(DEVICE_VALUE_ISREVERSE).toInt() == 0x01)
        isReverse = true;

    CMsgObjectStatus* msgObjectStatus = new CMsgObjectStatus(); // 动态分配对象
    msgObjectStatus->nCanportAdd = device->canportAdd();
    msgObjectStatus->nDisID = device->distributionAdd();
    msgObjectStatus->nLoopID = device->loopAdd();
    msgObjectStatus->nDeviceID = device->deviceAdd();
//    int lamptypeID = device->deviceTypeId();
    if(isDoubleDirection)
    {
        if(!isLeft || (isLeft && isReverse))
        {
            direction |= 0x06;
            DeviceStartStatus(device, "右向", QDateTime::currentDateTime());
        }
        else
        {
            direction |= 0x05;
            DeviceStartStatus(device, "左向", QDateTime::currentDateTime());
        }
    }
    else
    {
        direction |= 0x07;
    }

    if(device->isMAtype())
    {
        //非可变状态灯
        if(device->deviceTypeId() != 146)
        {
            direction |= 0x08;
            //发送方向控制指令
            msgObjectStatus->nValue = direction;
            exeCommand(NCT_DeviceDirection, msgObjectStatus);
            //双向灯方向控制标志
            device->setDeviceControl(true);
        }
        //双向灯方向控制标志
        if(isDoubleDirection)
            device->setDeviceControl(true);
        return;
    }

    if(CGlobal::instance()->m_TwinkleControl)
    {
        if(CGlobal::instance()->m_lampEmergencyType == 0)
        {
            direction |= 0x08;
            //发送方向控制指令
            msgObjectStatus->nValue = direction;
            exeCommand(NCT_DeviceDirection, msgObjectStatus);
            //双向灯方向控制标志
            device->setDeviceControl(true);
        }
        else if(CGlobal::instance()->m_lampEmergencyType & 0x01)
        {
            if(CGlobal::instance()->m_isOldLampEmergencyParam)
            {
                if(isDoubleDirection)
                {
                    //发送默认方向控制指令
                    msgObjectStatus->nValue = direction;
                    exeCommand(NCT_DeviceDefaultDirection, msgObjectStatus);
                    //双向灯默认方向控制标志
                    device->setDeviceDefaultControl(true);

                    //延时发送闪烁指令
                    msgObjectStatus->nValue = 0x01;
                    m_msg.append(msgObjectStatus);
                    m_flashTimer->start(2000);
                }
                else
                {
                    //发送闪烁指令
                    msgObjectStatus->nValue = 0x01;
                    exeCommand(NCT_FlashControl, msgObjectStatus);
                    if(CGlobal::instance()->m_lampEmergencyType & 0x02)
                    {
                        //发送应急指令
                        exeCommand(NCT_Emergency, msgObjectStatus);
                    }
                }
            }
            else
            {
                if(isDoubleDirection)
                {
                    //发送方向控制指令
                    msgObjectStatus->nValue = direction;
                    exeCommand(NCT_DeviceDirection, msgObjectStatus);
                    //双向灯方向控制标志
                    device->setDeviceControl(true);
                }
                //发送闪烁指令
                msgObjectStatus->nValue = 0x01;
                exeCommand(NCT_FlashControl, msgObjectStatus);
                if(CGlobal::instance()->m_lampEmergencyType & 0x02)
                {
                    //发送应急指令
                    exeCommand(NCT_Emergency, msgObjectStatus);
                }
            }
        }
        else if(CGlobal::instance()->m_lampEmergencyType & 0x02)
        {
            if(isDoubleDirection)
            {
                direction |= 0x08;
                //发送方向控制指令
                msgObjectStatus->nValue = direction;
                exeCommand(NCT_DeviceDirection, msgObjectStatus);
                //双向灯方向控制标志
                device->setDeviceControl(true);
            }
            else
            {
                //发送闪烁指令
                msgObjectStatus->nValue = 0x01;
                exeCommand(NCT_FlashControl, msgObjectStatus);
                //发送应急指令
                exeCommand(NCT_Emergency, msgObjectStatus);
            }
        }
    }
    else
    {
        if(isDoubleDirection)
        {
            if(CGlobal::instance()->m_isOldLampEmergencyParam)
            {
                //发送默认方向控制指令
                msgObjectStatus->nValue = direction;
                exeCommand(NCT_DeviceDefaultDirection, msgObjectStatus);
                //双向灯默认方向控制标志
                device->setDeviceDefaultControl(true);
            }
            else
            {
                //发送方向控制指令
                msgObjectStatus->nValue = direction;
                exeCommand(NCT_DeviceDirection, msgObjectStatus);
                //双向灯方向控制标志
                device->setDeviceControl(true);
            }
        }
        m_flashTimer->start(2000);
    }
}

void CClientBusiness::Emergency()
{
    qDebug() << "CClientBusiness::Emergency"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
    CDBSqlite db(fileName);
    if(!db.open())
        return;
    //所有灯
    QSqlQuery query = db.query(QString("SELECT l.Address,c.Loop,a.CanPort,a.Address,r.Number from LampInfo l "
                                       " left join ChannelInfo c on l.ChannelInfoID = c.ID "
                                       " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
                                       " left join LampType r on l.LampTypeID=r.ID "));
    //query.value(0)代表第0列
    //第0列:l.Address        灯具地址
    //第1列:c.Loop           回路地址
    //第2列:a.CanPort        CAN地址
    //第3列:a.Address        集中电源地址
    //第4列:r.Number         灯具型号
    while(query.next())
    {
        int canAddress = query.value(2).toInt()+2;
        int distributionAddress = query.value(3).toInt();
        int loopAddress = query.value(1).toInt();
        int deviceAddress = query.value(0).toInt();
        int lamptypeID = query.value(4).toInt();

        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
        if(!canport)
            continue;
        CDistribution* distribution = canport->distributionByAddress(distributionAddress);
        if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
            continue;
        CLoop* loop = distribution->loopByAdd(loopAddress);
        if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
            continue;
        CDevice* device = loop->deviceByAdd(deviceAddress);
        if(!device || device->getStatus(OBJS_LightCommunicationFault))
            continue;
//        device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"应急");
        if(CGlobal::instance()->programDeviceView()->type(lamptypeID) == NCT_LightType)
            continue;
        CMsgObjectStatus msgObjectStatus;
        msgObjectStatus.nCanportAdd = canport->canportAdd();
        msgObjectStatus.nDisID = distribution->distributionAddress();
        msgObjectStatus.nLoopID = loop->loopAdd();
        msgObjectStatus.nDeviceID = device->deviceAdd();
        //双向灯和地埋灯除外
        if(isDoubleLamp(lamptypeID))
            continue;
        //灯具控制
        lampControl(device);
        //可变状态灯
        if(lamptypeID == 109 || lamptypeID == 11 || lamptypeID == 146)   //109/11/146代表可变状态灯
        {
            msgObjectStatus.nValue = true;
            exeCommand(NCT_ChangeControl, &msgObjectStatus);
            DeviceStartStatus(device, "禁止入内", QDateTime::currentDateTime());
        }
    }
    //方向控制(双向灯具或地埋灯)
    QSqlQuery querylampcontrol = db.query(QString("SELECT l.LampDirection,r.Remark,r.Address,c.Loop,a.CanPort,a.Address,r.id,r.LampTypeID,r.IsReverse from EvacuationPathItem l "
                                       " left join LampInfo r on l.LampInfoID=r.ID "
                                       " left join ChannelInfo c on r.ChannelInfoID = c.ID "
                                       " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
                                       " where l.FirePointID is Null "));
    //query.value(0)代表第0列
    //第0列:l.LampDirection  灯具方向
    //第1列:r.Remark         灯具产品编号
    //第2列:r.Address        灯具地址
    //第3列:c.Loop           回路地址
    //第4列:a.CanPort        CAN地址
    //第5列:a.Address        集中电源地址
    //第6列:r.ID             灯具ID
    //第7列:r.LampTypeID     灯具型号ID
    //第8列:r.IsReverse      灯具是否反接
    while(querylampcontrol.next())
    {
        int lampDirection = querylampcontrol.value(0).toInt();
        int canAddress = querylampcontrol.value(4).toInt()+2;
        int distributionAddress = querylampcontrol.value(5).toInt();
        int loopAddress = querylampcontrol.value(3).toInt();
        int deviceAddress = querylampcontrol.value(2).toInt();
        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
        if(!canport)
            continue;
        CDistribution* distribution = canport->distributionByAddress(distributionAddress);
        if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
            continue;
        CLoop* loop = distribution->loopByAdd(loopAddress);
        if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
            continue;
        CDevice* device = loop->deviceByAdd(deviceAddress);
        if(!device || device->getStatus(OBJS_LightCommunicationFault))
            continue;

        if(!isDoubleLamp(device->deviceTypeId()))
        {
            continue;
        }
        if(lampDirection & 0x01)
        {
            lampControl(device, true, true);
        }
        else if(lampDirection & 0x02)
        {
            lampControl(device, true, false);
        }
    }
    deviceControl devicecontrol;
    devicecontrol.saveDeviceControlFile();//保存灯具控制表
    if(CGlobal::instance()->m_isOldLampEmergencyParam)
    {
        deviceDefaultControl defaultcontrol;
        defaultcontrol.saveDeviceDefaultControlFile();//保存灯具默认方向控制表
    }
    db.close();

    //布局视图界面灯具状态更新
    CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
}
//火警点协议联动应急(按分组启动)
void CClientBusiness::firePointEmergencyByGroup(int firePointID)
{
    qDebug() << "CClientBusiness::firePointEmergencyByGroup"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CFirePoint* firepoint = CGlobal::instance()->controller()->firePointByID(firePointID);
    firepoint->setSimulateEmergency(true);
    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.open())
        return;
    QSqlQuery queryGroup(db);
    QSet<int> groups;
    //该火警点对应分组
    queryGroup.prepare(QString("SELECT g.LaunchGroupID from LampToLaunchGroup g "
                                       " left join LampToFirePoint f on f.LampInfoID=g.LampInfoID "
                                       " where f.FirePointID=%1").arg(firePointID));
    if (!queryGroup.exec())
    {
        qDebug() << "queryGroup Error:" << queryGroup.lastError().text();
        return;
    }
    while(queryGroup.next())
    {
        groups.insert(queryGroup.value(0).toInt());
    }
    // 遍历输出结果
    for (QSet<int>::const_iterator it = groups.begin(); it != groups.end(); ++it) {
        //该火警点对应分组的所有灯
        QSqlQuery query(db);
        query.prepare(QString("SELECT l.Address,c.Loop,a.CanPort,a.Address,r.Number from LampInfo l "
                                   " left join ChannelInfo c on l.ChannelInfoID = c.ID "
                                   " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
                                   " left join LampType r on l.LampTypeID=r.ID "
                                   " left join LampToLaunchGroup g on l.ID=g.LampInfoID "
                                   " where g.LaunchGroupID=%1").arg(*it));
        if (!query.exec())
        {
            qDebug() << "firePointEmergencyByGroup Error:" << query.lastError().text();
            return;
        }
        //query.value(0)代表第0列
        //第0列:l.Address        灯具地址
        //第1列:c.Loop           回路地址
        //第2列:a.CanPort        CAN地址
        //第3列:a.Address        集中电源地址
        //第4列:r.Number         灯具型号
        while(query.next())
        {
            int canAddress = query.value(2).toInt()+2;
            int distributionAddress = query.value(3).toInt();
            int loopAddress = query.value(1).toInt();
            int deviceAddress = query.value(0).toInt();
            int lamptypeID = query.value(4).toInt();
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
            if(!canport)
                continue;
            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
            if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
                continue;
            CLoop* loop = distribution->loopByAdd(loopAddress);
            if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
                continue;
            CDevice* device = loop->deviceByAdd(deviceAddress);
            if(!device || device->getStatus(OBJS_LightCommunicationFault))
                continue;
            device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"应急");
            CMsgObjectStatus msgObjectStatus;
            msgObjectStatus.nCanportAdd = canAddress;
            msgObjectStatus.nDisID = distributionAddress;
            msgObjectStatus.nLoopID = loopAddress;
            msgObjectStatus.nDeviceID = deviceAddress;
            if(CGlobal::instance()->programDeviceView()->type(lamptypeID) == NCT_LightType)
            {
                msgObjectStatus.nValue = true;
                exeCommand(NCT_Emergency, &msgObjectStatus);
                device->setDeviceControl(true);
                continue;
            }
            //双向灯和地埋灯除外
            if(isDoubleLamp(lamptypeID))
                continue;
            //灯具控制
            lampControl(device);
            //可变状态灯
            if(lamptypeID == 109 || lamptypeID == 11 || lamptypeID == 146)   //109/11/146代表可变状态灯
            {
                msgObjectStatus.nValue = true;
                exeCommand(NCT_ChangeControl, &msgObjectStatus);
                DeviceStartStatus(device, "禁止入内", QDateTime::currentDateTime());
            }

            device->setDeviceControl(true);
        }

        //方向控制(该火警点对应分组的双向灯具或地埋灯)
        QSqlQuery querylampcontrol(db);
        querylampcontrol.prepare(QString("SELECT l.LampDirection,r.Remark,r.Address,c.Loop,a.CanPort,a.Address,r.id,r.LampTypeID,r.IsReverse,l.FirePointID from EvacuationPathItem l "
                                           " left join LampInfo r on l.LampInfoID=r.ID "
                                           " left join ChannelInfo c on r.ChannelInfoID = c.ID "
                                           " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
                                           " left join LampToLaunchGroup g on l.LampInfoID=g.LampInfoID "
                                           " where g.LaunchGroupID=%1 and l.FirePointID=%2").arg(*it).arg(firePointID));
        if (!querylampcontrol.exec())
        {
            qDebug() << "querylampcontrol Error:" << querylampcontrol.lastError().text();
            return;
        }
        //query.value(0)代表第0列
        //第0列:l.LampDirection  灯具方向
        //第1列:r.Remark         灯具产品编号
        //第2列:r.Address        灯具地址
        //第3列:c.Loop           回路地址
        //第4列:a.CanPort        CAN地址
        //第5列:a.Address        集中电源地址
        //第6列:r.ID             灯具ID
        //第7列:r.LampTypeID     灯具型号ID
        //第8列:r.IsReverse      灯具是否反接

        while(querylampcontrol.next())
        {
            int lampDirection = querylampcontrol.value(0).toInt();
            int canAddress = querylampcontrol.value(4).toInt()+2;
            int distributionAddress = querylampcontrol.value(5).toInt();
            int loopAddress = querylampcontrol.value(3).toInt();
            int deviceAddress = querylampcontrol.value(2).toInt();
//            int lampID = querylampcontrol.value(6).toInt();
//            int lamptypeID = querylampcontrol.value(7).toInt();
//            int lampIsReverse = querylampcontrol.value(8).toInt();
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
            if(!canport)
                continue;
            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
            if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
                continue;
            CLoop* loop = distribution->loopByAdd(loopAddress);
            if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
                continue;
            CDevice* device = loop->deviceByAdd(deviceAddress);
            if(!device || device->getStatus(OBJS_LightCommunicationFault))
                continue;
            if(!isDoubleLamp(device->deviceTypeId()))
            {
                continue;
            }
            if(lampDirection & 0x01)
            {
                lampControl(device, true, true);
            }
            else if(lampDirection & 0x02)
            {
                lampControl(device, true, false);
            }
        }
    }
    deviceControl devicecontrol;
    devicecontrol.saveDeviceControlFile();//保存灯具控制表
    if(CGlobal::instance()->m_isOldLampEmergencyParam)
    {
        deviceDefaultControl defaultcontrol;
        defaultcontrol.saveDeviceDefaultControlFile();//保存灯具默认方向控制表
    }
    db.close();

    //布局视图界面灯具状态更新
    CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
}

//火警点协议联动应急(按页面启动)
void CClientBusiness::firePointEmergencyByLayoutPage(int firePointID)
{
    qDebug() << "CClientBusiness::firePointEmergencyByLayoutPage"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CFirePoint* firepoint = CGlobal::instance()->controller()->firePointByID(firePointID);
    firepoint->setSimulateEmergency(true);
    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.open())
        return;
    QSqlQuery queryLayoutPage(db);
    QSet<int> layoutPages;
    //该火警点对应页面
    queryLayoutPage.prepare(QString("SELECT c.LayoutPageID from Coordinate c "
                                       " left join LampToFirePoint f on f.LampInfoID=c.LampInfoID "
                                       " where f.FirePointID=%1").arg(firePointID));
    if (!queryLayoutPage.exec())
    {
        qDebug() << "firePointEmergencyByLayoutPage Error:" << queryLayoutPage.lastError().text();
        return;
    }
    while(queryLayoutPage.next())
    {
        layoutPages.insert(queryLayoutPage.value(0).toInt());
    }
    // 遍历输出结果
    for (QSet<int>::const_iterator it = layoutPages.begin(); it != layoutPages.end(); ++it) {
        //该页面所有灯
        QSqlQuery query(db);
        query.prepare(QString("SELECT l.Address,c.Loop,a.CanPort,a.Address,r.Number,p.layoutPageID from LampInfo l "
                                           " left join ChannelInfo c on l.ChannelInfoID = c.ID "
                                           " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
                                           " left join LampType r on l.LampTypeID=r.ID "
                                           " left join Coordinate p on l.ID=p.LampInfoID "
                                           " where p.layoutPageID=%1").arg(*it));
        if (!query.exec())
        {
            qDebug() << "firePointEmergencyByLayoutPage Error:" << query.lastError().text();
            return;
        }
        //query.value(0)代表第0列
        //第0列:l.Address        灯具地址
        //第1列:c.Loop           回路地址
        //第2列:a.CanPort        CAN地址
        //第3列:a.Address        集中电源地址
        //第4列:r.Number         灯具型号
        while(query.next())
        {
            int canAddress = query.value(2).toInt()+2;
            int distributionAddress = query.value(3).toInt();
            int loopAddress = query.value(1).toInt();
            int deviceAddress = query.value(0).toInt();
            int lamptypeID = query.value(4).toInt();
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
            if(!canport)
                continue;
            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
            if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
                continue;
            CLoop* loop = distribution->loopByAdd(loopAddress);
            if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
                continue;
            CDevice* device = loop->deviceByAdd(deviceAddress);
            if(!device || device->getStatus(OBJS_LightCommunicationFault))
                continue;
            CMsgObjectStatus msgObjectStatus;
            msgObjectStatus.nCanportAdd = canAddress;
            msgObjectStatus.nDisID = distributionAddress;
            msgObjectStatus.nLoopID = loopAddress;
            msgObjectStatus.nDeviceID = deviceAddress;
            device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"应急");
            if(CGlobal::instance()->programDeviceView()->type(lamptypeID) == NCT_LightType)
            {
                msgObjectStatus.nValue = true;
                exeCommand(NCT_Emergency, &msgObjectStatus);
                device->setDeviceControl(true);
                continue;
            }
            //双向灯和地埋灯除外
            if(isDoubleLamp(lamptypeID))
                continue;
            //灯具控制
            lampControl(device);
            //可变状态灯
            if(lamptypeID == 109 || lamptypeID == 11 || lamptypeID == 146)   //109/11/146代表可变状态灯
            {
                msgObjectStatus.nValue = true;
                exeCommand(NCT_ChangeControl, &msgObjectStatus);
                DeviceStartStatus(device, "禁止入内", QDateTime::currentDateTime());
            }

//            //方向灯闪烁配置
//            msgObjectStatus.nValue = CGlobal::instance()->m_TwinkleControl;
//            exeCommand(NCT_FlashConfig, &msgObjectStatus);
            device->setDeviceControl(true);
        }
        //方向控制(该火警点对应页面的双向灯具或地埋灯)
        QSqlQuery querylampcontrol(db);
        querylampcontrol.prepare(QString("SELECT l.LampDirection,r.Remark,r.Address,c.Loop,a.CanPort,a.Address,r.id,r.LampTypeID,r.IsReverse,l.FirePointID from EvacuationPathItem l "
                                           " left join LampInfo r on l.LampInfoID=r.ID "
                                           " left join ChannelInfo c on r.ChannelInfoID = c.ID "
                                           " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
                                           " left join Coordinate p on l.LampInfoID=p.LampInfoID "
                                           " where p.LayoutPageID=%1 and l.FirePointID=%2").arg(*it).arg(firePointID));
        if (!querylampcontrol.exec())
        {
            qDebug() << "querylampcontrol Error:" << querylampcontrol.lastError().text();
            return;
        }
        //query.value(0)代表第0列
        //第0列:l.LampDirection  灯具方向
        //第1列:r.Remark         灯具产品编号
        //第2列:r.Address        灯具地址
        //第3列:c.Loop           回路地址
        //第4列:a.CanPort        CAN地址
        //第5列:a.Address        集中电源地址
        //第6列:r.ID             灯具ID
        //第7列:r.LampTypeID     灯具型号ID
        //第8列:r.IsReverse      灯具是否反接
        while(querylampcontrol.next())
        {
            int lampDirection = querylampcontrol.value(0).toInt();
            int canAddress = querylampcontrol.value(4).toInt()+2;
            int distributionAddress = querylampcontrol.value(5).toInt();
            int loopAddress = querylampcontrol.value(3).toInt();
            int deviceAddress = querylampcontrol.value(2).toInt();
//            int lampID = querylampcontrol.value(6).toInt();
//            int lamptypeID = querylampcontrol.value(7).toInt();
//            int lampIsReverse = querylampcontrol.value(8).toInt();
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
            if(!canport)
                continue;
            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
            if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
                continue;
            CLoop* loop = distribution->loopByAdd(loopAddress);
            if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
                continue;
            CDevice* device = loop->deviceByAdd(deviceAddress);
            if(!device || device->getStatus(OBJS_LightCommunicationFault))
                continue;
            if(!isDoubleLamp(device->deviceTypeId()))
            {
                continue;
            }
            if(lampDirection & 0x01)
            {
                lampControl(device, true, true);
            }
            else if(lampDirection & 0x02)
            {
                lampControl(device, true, false);
            }
        }
    }
    deviceControl devicecontrol;
    devicecontrol.saveDeviceControlFile();//保存灯具控制表
    if(CGlobal::instance()->m_isOldLampEmergencyParam)
    {
        deviceDefaultControl defaultcontrol;
        defaultcontrol.saveDeviceDefaultControlFile();//保存灯具默认方向控制表
    }
    db.close();

    //布局视图界面灯具状态更新
    CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
}

//火警点协议联动应急(按集中电源启动)
void CClientBusiness::firePointEmergencyByDistribution(int firePointID)
{
    qDebug() << "CClientBusiness::firePointEmergencyByDistribution"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
//    int direction = 0;
    CFirePoint* firepoint = CGlobal::instance()->controller()->firePointByID(firePointID);
    firepoint->setSimulateEmergency(true);
    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if(!db.open())
        return;
    QSqlQuery queryDistribution(db);
//    QSet< QPair<int,int> > distrbutionPairs;
    //该火警点对应集中电源
    queryDistribution.prepare(QString("SELECT c.CanPort,c.Address from CanDeviceInfo c "
                                       " left join ChannelInfo l on l.CanDeviceInfoID=c.ID "
                                       " left join LampInfo d on d.ChannelInfoID=l.ID "
                                       " left join LampToFirePoint f on f.LampInfoID=d.ID "
                                       " where f.FirePointID=%1").arg(firePointID));
    if (!queryDistribution.exec())
    {
        qDebug() << "firePointEmergencyByDistribution Error:" << queryDistribution.lastError().text();
        return;
    }
    while(queryDistribution.next())
    {
        int canport = queryDistribution.value(0).toInt();
        int distributionAddress = queryDistribution.value(1).toInt();
//        distrbutionPairs.insert(QPair<int,int>(canport,distributionAddress));
        CMsgObjectStatus msgObjectStatus;
        msgObjectStatus.nCanportAdd = canport+2;
        msgObjectStatus.nDisID = distributionAddress;
        msgObjectStatus.nValue = true;
        exeCommand(NCT_Emergency, &msgObjectStatus);
    }
    // 遍历输出结果
//    for (QSet< QPair<int,int> >::const_iterator it = distrbutionPairs.begin(); it != distrbutionPairs.end(); ++it) {
//         const QPair<int, int>& pair= *it;
//        //该集中电源所有灯
//        QSqlQuery query = db.query(QString("SELECT l.Address,c.Loop,a.CanPort,a.Address,r.Number from LampInfo l "
//                                           " left join ChannelInfo c on l.ChannelInfoID = c.ID "
//                                           " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
//                                           " left join LampType r on l.LampTypeID=r.ID "
//                                           " where a.CanPort=%1 and a.Address=%2").arg(pair.first).arg(pair.second));
//        //query.value(0)代表第0列
//        //第0列:l.Address        灯具地址
//        //第1列:c.Loop           回路地址
//        //第2列:a.CanPort        CAN地址
//        //第3列:a.Address        集中电源地址
//        //第4列:r.Number         灯具型号
//        while(query.next())
//        {
//            int canAddress = query.value(2).toInt()+2;
//            int distributionAddress = query.value(3).toInt();
//            int loopAddress = query.value(1).toInt();
//            int deviceAddress = query.value(0).toInt();
//            int lamptypeID = query.value(4).toInt();
//            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
//            if(!canport)
//                continue;
//            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
//            if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
//                continue;
//            CLoop* loop = distribution->loopByAdd(loopAddress);
//            if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
//                continue;
//            CDevice* device = loop->deviceByAdd(deviceAddress);
//            if(!device || device->getStatus(OBJS_LightCommunicationFault))
//                continue;
//            CMsgObjectStatus msgObjectStatus;
//            msgObjectStatus.nCanportAdd = canAddress;
//            msgObjectStatus.nDisID = distributionAddress;
//            msgObjectStatus.nLoopID = loopAddress;
//            msgObjectStatus.nDeviceID = deviceAddress;
//            device->setDeviceValue(DEVICE_VALUE_EMERGENCY,"应急");
//            direction = 0x07;
//            if(CGlobal::instance()->programDeviceView()->type(lamptypeID) == NCT_LightType)
//            {
////                msgObjectStatus.nValue = true;
////                exeCommand(NCT_Emergency, &msgObjectStatus);
////                device->setDeviceControl(true);
//                continue;
//            }
//            //闪烁(双向灯和地埋灯除外,它们在方向控制时闪烁）
//            if(!isDoubleLamp(lamptypeID))
//            {
//                lampControl(device);
//            }

//            //可变状态灯
//            if(lamptypeID == 109 || lamptypeID == 11 || lamptypeID == 146)   //109/11/146代表可变状态灯
//            {
//                msgObjectStatus.nValue = true;
//                exeCommand(NCT_ChangeControl, &msgObjectStatus);
//                DeviceStartStatus(device, "禁止入内", QDateTime::currentDateTime());
//            }

////            //方向灯闪烁配置
////            msgObjectStatus.nValue = CGlobal::instance()->m_TwinkleControl;
////            exeCommand(NCT_FlashConfig, &msgObjectStatus);
//            device->setDeviceControl(true);
//        }
//        //方向控制(该该集中电源的双向灯具或地埋灯)
//        QSqlQuery querylampcontrol = db.query(QString("SELECT l.LampDirection,r.Remark,r.Address,c.Loop,a.CanPort,a.Address,r.id,r.LampTypeID,r.IsReverse,l.FirePointID from EvacuationPathItem l "
//                                           " left join LampInfo r on l.LampInfoID=r.ID "
//                                           " left join ChannelInfo c on r.ChannelInfoID = c.ID "
//                                           " left join CanDeviceInfo a on c.CanDeviceInfoID = a.ID "
//                                           " where a.CanPort=%1 and a.Address=%2 and l.FirePointID=%3").arg(pair.first).arg(pair.second).arg(firePointID));
//        //query.value(0)代表第0列
//        //第0列:l.LampDirection  灯具方向
//        //第1列:r.Remark         灯具产品编号
//        //第2列:r.Address        灯具地址
//        //第3列:c.Loop           回路地址
//        //第4列:a.CanPort        CAN地址
//        //第5列:a.Address        集中电源地址
//        //第6列:r.ID             灯具ID
//        //第7列:r.LampTypeID     灯具型号ID
//        //第8列:r.IsReverse      灯具是否反接
//        while(querylampcontrol.next())
//        {
//            int lampDirection = querylampcontrol.value(0).toInt();
//            int canAddress = querylampcontrol.value(4).toInt()+2;
//            int distributionAddress = querylampcontrol.value(5).toInt();
//            int loopAddress = querylampcontrol.value(3).toInt();
//            int deviceAddress = querylampcontrol.value(2).toInt();
////            int lampID = querylampcontrol.value(6).toInt();
////            int lamptypeID = querylampcontrol.value(7).toInt();
////            int lampIsReverse = querylampcontrol.value(8).toInt();
//            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canAddress);
//            if(!canport)
//                continue;
//            CDistribution* distribution = canport->distributionByAddress(distributionAddress);
//            if(!distribution || distribution->getStatus(OBJS_DistributionCommunicationFault))
//                continue;
//            CLoop* loop = distribution->loopByAdd(loopAddress);
//            if(!loop || loop->getStatus(OBJS_LoopCommunicationFault) || !loop->isLoopLogin())
//                continue;
//            CDevice* device = loop->deviceByAdd(deviceAddress);
//            if(!device || device->getStatus(OBJS_LightCommunicationFault))
//                continue;
//            if(!isDoubleLamp(device->deviceTypeId()))
//            {
//                continue;
//            }
//            if(lampDirection & 0x01)
//            {
//                lampControl(device, true, true);
//            }
//            else if(lampDirection & 0x02)
//            {
//                lampControl(device, true, false);
//            }
//            device->setDeviceControl(true);
//        }
//    }
//    deviceControl devicecontrol;
//    devicecontrol.saveDeviceControlFile();//保存灯具控制表
    db.close();

    //布局视图界面灯具状态更新
    CGlobal::instance()->designSplashView()->setPageStateUpdate(true);
}

//判断是否为非智能型灯具
bool CClientBusiness::isUCLamp(int ID)//ID为数据库中LampType表中ID
{
    qDebug() << "CClientBusiness::isUCLamp"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if((ID >= 34) && (ID <= 42))//集中电源型
        return true;
    else if((ID >= 65) && (ID <= 72))//自带电池型
        return true;
    else
        return false;
}

//判断是否为双向或地埋灯具
bool CClientBusiness::isDoubleLamp(int lamptypeID)
{
    qDebug() << "CClientBusiness::isDoubleLamp"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(lamptypeID == 102 || lamptypeID == 106 || lamptypeID == 3 || lamptypeID == 9 ||
       lamptypeID == 17 || lamptypeID == 44 || lamptypeID == 117 || lamptypeID == 144 ||
       lamptypeID == 132 || lamptypeID == 136 || lamptypeID == 32 || lamptypeID == 36 ||
       lamptypeID == 121 || lamptypeID == 123)
        return true;
    else
        return false;
}


//判断是否为照明灯
bool CClientBusiness::isLightLamp(int lamptypeID)
{
    qDebug() << "CClientBusiness::isLightLamp"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if((lamptypeID >= 150 && lamptypeID < 200) || (lamptypeID >= 50 && lamptypeID < 100))
        return true;
    else
        return false;
}

//判断是否为可变状态灯
bool CClientBusiness::isChangeLamp(int lamptypeID)
{
    qDebug() << "CClientBusiness::isChangeLamp"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(lamptypeID == 109 || lamptypeID == 11 || lamptypeID == 146 || lamptypeID == 46)
        return true;
    else
        return false;
}

void CClientBusiness::timeOut()
{
    qDebug() << "CClientBusiness::timeOut"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(!m_isRecvStatus && CGlobal::instance()->dm()->isLoad())
    {
        CMsgObjectStatusInfo msgObjectStatusInfo;
        msgObjectStatusInfo.statusId = m_currentStatusId;
    }
    else
    {
        static int notRecvStatusCount = 0;
        static int lastRecvStatusNumber = 0;
        if(lastRecvStatusNumber == m_currentRecvStatusNumber)
            notRecvStatusCount++;
        lastRecvStatusNumber = m_currentRecvStatusNumber;
        if(notRecvStatusCount > 10)
        {
            notRecvStatusCount = 0;
            lastRecvStatusNumber = 0;
            m_isRecvStatus = false;
            m_currentRecvStatusNumber = 0;
        }
    }
}

//void CClientBusiness::driveDeviceDirection(CPointDeviceItem *item, uchar direction, uchar delay, bool isFlow)
//{
//    CDevice* device = static_cast<CDevice*>(item->device());
//    CLoop* loop = device->loop();
//    CDistribution* distribution = loop->distribution();
//    CMsgObjectStatus objectStatus;
//    objectStatus.nType = isFlow?1:0;
//    objectStatus.nPanelID = CGlobal::instance()->panelAddress();
//    objectStatus.nDisID = distribution->distributionId();
//    objectStatus.nLoopID = loop->loopId();
//    objectStatus.nDeviceID = device->deviceId();
//    objectStatus.nStatusID = direction;
//    objectStatus.nValue = delay;
//    objectStatus.nTimes = 0;
//    exeCommand(NCT_ObjectStatus, &objectStatus);
//}

void CClientBusiness::objectStatusChanged(CObject* object, short status, unsigned char oldValue, unsigned char newValue, unsigned int time)
{
    qDebug() << "CClientBusiness::objectStatusChanged" << object->type() << status << oldValue << newValue
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    Q_UNUSED(oldValue);

    if(!object)
        return;
    QString objectType = object->type();
    if(objectType != CController::type_s && objectType != CDistribution::type_s  &&
            objectType != CFirePoint::type_s && objectType != CLoop::type_s && objectType != CDevice::type_s)
        return;
    if(object->isFaultStatus())
        m_faultObjects.insert(object->keyId());
    else
        m_faultObjects.remove(object->keyId());
    if(object->isEmergencyStatus())
        m_startObjects.insert(object->keyId());
    else
        m_startObjects.remove(object->keyId());
    QString strType = "";
    if(status == OBJS_LoginDeviceType)
        object->setValue("device_typeId",newValue);
    m_statusInfo.keyId = object->keyId();
    m_statusInfo.statusId = status;
    m_statusInfo.type = object->typeStr();
    m_statusInfo.time = time ? QDateTime::fromTime_t(time) : QDateTime::currentDateTime();
    m_statusInfo.layer = "";

//    if(status == OBJS_None && newValue == OBJS_None)
//    {
//        emit statusRecord(m_statusInfo, SRT_ALL, SRO_DelAll);
//        return;
//    }
    int type = 0;
    if(status == OBJS_Fire)
        type = SRT_Start;
    else if(CGlobal::instance()->isEmergencyStatus(status))
        type = SRT_Emergency;
    else if(CGlobal::instance()->isFaultStatus(status))
        type = SRT_Fault;
    else
        return;
    QString strtext = CGlobal::instance()->getObjectStatusDescription(object, status, newValue);
    if(objectType == CController::type_s)
    {
        strType = "系统";
        m_msgLog->User = strType;
        m_msgLog->Type = (type==SRT_Emergency?"启动":"故障");
        m_msgLog->Time = QDateTime::currentDateTime();
        m_msgLog->Remark = "控制器" + CGlobal::instance()->getObjectStatusStr(status) + CGlobal::instance()->getObjectStatusSuffix(status, newValue);
        m_msgLog->title = m_msgLog->Remark;
        if(type != SRT_Emergency)
            exeCommand(NCT_AddLog, m_msgLog);
        else
            type = SRT_Start;

        if(status == OBJS_SimulateFireEmergency)
            exeCommand(NCT_AddLog, m_msgLog);
        m_statusInfo.distributionId = "";
        m_statusInfo.loopID = 0;
        m_statusInfo.deviceID = 0;
        m_statusInfo.status = CGlobal::instance()->getObjectStatusStr(status) + CGlobal::instance()->getObjectStatusSuffix(status, newValue);
    }
    else if(objectType == CFirePoint::type_s)
    {
        strType = "火警点";
        CFirePoint* firepoint = static_cast<CFirePoint*>(object);
        m_msgLog->User = strType;
        m_msgLog->Type = "启动";
        m_msgLog->Time = QDateTime::currentDateTime();
        m_msgLog->Area = firepoint->firePointValue(FIREPOINT_VALUE_AREA).toString();
        m_msgLog->Location = firepoint->firePointValue(FIREPOINT_VALUE_LOCATION).toString();
        m_msgLog->Remark = CGlobal::instance()->getObjectStatusStr(status) + CGlobal::instance()->getObjectStatusSuffix(status, newValue);
        m_msgLog->Canport = 0;
        m_msgLog->CanDeviceAddress = firepoint->firePointDeviceAddress();
        m_msgLog->Loop = firepoint->firePointLoopAddress();
        m_msgLog->LampDeviceAddress = firepoint->firePointAddress();
        m_msgLog->title = strtext;
        type = SRT_Start;
        exeCommand(NCT_AddLog, m_msgLog);

        m_statusInfo.distributionId = QString::number(m_msgLog->CanDeviceAddress);
        m_statusInfo.loopID = m_msgLog->Loop;
        m_statusInfo.deviceID = m_msgLog->LampDeviceAddress;
        m_statusInfo.area = m_msgLog->Area;
        m_statusInfo.location = m_msgLog->Location;
        m_statusInfo.status = m_msgLog->Remark;
    }
    else if(objectType == CDistribution::type_s)
    {
        CDistribution* distribution = static_cast<CDistribution*>(object);
        strType = distribution->distributionValue((DISTRIBUTION_VALUE_NAME)).toString();
        m_msgLog->User = strType;
        if(type==SRT_Start)
            m_msgLog->Type = "启动";
        else if(type==SRT_Emergency)
            m_msgLog->Type = "应急";
        else
            m_msgLog->Type = "故障";
        m_msgLog->Time = QDateTime::currentDateTime();
        m_msgLog->Area = distribution->distributionValue(DISTRIBUTION_VALUE_AREA).toString();
        m_msgLog->Location = distribution->distributionValue(DISTRIBUTION_VALUE_LOCATION).toString();
        if(CGlobal::instance()->getObjectStatusStr(status) == "通讯故障" && newValue)
            m_msgLog->Remark = CGlobal::instance()->getObjectStatusStr(status) + "(所属回路、灯具通讯故障)";
        else
            m_msgLog->Remark = CGlobal::instance()->getObjectStatusStr(status);
        m_msgLog->Remark = m_msgLog->Remark + CGlobal::instance()->getObjectStatusSuffix(status, newValue);
        m_msgLog->Canport = distribution->canportAddress()-2;
        m_msgLog->CanDeviceAddress = distribution->distributionAddress();
        m_msgLog->Loop = 0;
        m_msgLog->LampDeviceAddress = 0;
        m_msgLog->title = strtext;
        exeCommand(NCT_AddLog, m_msgLog);

        m_statusInfo.distributionId = "CAN" + QString::number(distribution->canportAddress()-2)
                                      + "-" + QString::number(distribution->distributionAddress());
        m_statusInfo.loopID = 0;
        m_statusInfo.deviceID = 0;
        m_statusInfo.area = m_msgLog->Area;
        m_statusInfo.location = m_msgLog->Location;
        m_statusInfo.status = m_msgLog->Remark;
    }
    else if(objectType == CLoop::type_s)
    {
        strType = "回路";
        CLoop* loop = static_cast<CLoop*>(object);
        m_msgLog->User = strType;
        m_msgLog->Type = (type==SRT_Start?"启动":"故障");
        m_msgLog->Time = QDateTime::currentDateTime();
        m_msgLog->Area = "";
        m_msgLog->Location = "";
        if(CGlobal::instance()->getObjectStatusStr(status) == "通讯故障" && newValue)
            m_msgLog->Remark = CGlobal::instance()->getObjectStatusStr(status) + "(所属灯具通讯故障)";
        else
            m_msgLog->Remark = CGlobal::instance()->getObjectStatusStr(status);
        m_msgLog->Remark = m_msgLog->Remark + CGlobal::instance()->getObjectStatusSuffix(status, newValue);
        m_msgLog->Canport = loop->canportAdd()-2;
        m_msgLog->CanDeviceAddress = loop->distributionAdd();
        m_msgLog->Loop = loop->loopAdd();
        m_msgLog->LampDeviceAddress = 0;
        m_msgLog->title = strtext;
        if(type != SRT_Emergency)
            exeCommand(NCT_AddLog, m_msgLog);
        m_statusInfo.distributionId = "CAN" + QString::number(loop->canportAdd()-2)
                                      + "-" + QString::number(loop->distributionAdd());
        m_statusInfo.loopID = m_msgLog->Loop;
        m_statusInfo.deviceID = 0;
        m_statusInfo.area = "";
        m_statusInfo.location = "";
        m_statusInfo.status = m_msgLog->Remark;
    }
    else if(objectType == CDevice::type_s)
    {
        strType = "灯具";
        CDevice* device = static_cast<CDevice*>(object);
        m_msgLog->User = strType;
        m_msgLog->Type = (type==SRT_Start?"启动":"故障");
        m_msgLog->Time = QDateTime::currentDateTime();
        m_msgLog->Area = device->deviceValue(DEVICE_VALUE_AREA).toString();
        m_msgLog->Location = device->deviceValue(DEVICE_VALUE_LOCATION).toString();
        m_msgLog->Remark = CGlobal::instance()->getObjectStatusStr(status) + CGlobal::instance()->getObjectStatusSuffix(status, newValue);
        m_msgLog->Canport = device->canportAdd()-2;
        m_msgLog->CanDeviceAddress = device->distributionAdd();
        m_msgLog->Loop = device->loopAdd();
        m_msgLog->LampDeviceAddress = device->deviceAdd();
        m_msgLog->title = strtext;
        if(type != SRT_Emergency)
            exeCommand(NCT_AddLog, m_msgLog);

        m_statusInfo.distributionId = "CAN" + QString::number(device->canportAdd()-2)
                                      + "-" + QString::number(device->distributionAdd());
        m_statusInfo.loopID = m_msgLog->Loop;
        m_statusInfo.deviceID = m_msgLog->LampDeviceAddress;
        m_statusInfo.area = m_msgLog->Area;
        m_statusInfo.location = m_msgLog->Location;
        m_statusInfo.status = m_msgLog->Remark;
    }
    int opr = newValue ? SRO_Add : SRO_Del;
    CGlobal::instance()->DataProcessing()->slotStateInformation(m_statusInfo, type, opr);
    qDebug() << "CClientBusiness::objectStatusChanged" << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
}

void CClientBusiness::DeviceStartStatus(CDevice* device, QString directionStatus, QDateTime time)
{
    qDebug() << "CClientBusiness::DeviceStartStatus"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    StatusInfo statusInfo;
    if(device)
    {
        int type = CGlobal::instance()->programDeviceView()->type(device->deviceTypeId());
        if(type == NCT_ArrowDoubleType)
        {
            if(directionStatus == "左向")
            {
                device->setDeviceValue(DEVICE_VALUE_RIGHTCLOSE,1);
                device->setDeviceValue(DEVICE_VALUE_LEFTCLOSE,0);
            }
            else if(directionStatus == "右向")
            {
                device->setDeviceValue(DEVICE_VALUE_LEFTCLOSE,1);
                device->setDeviceValue(DEVICE_VALUE_RIGHTCLOSE,0);
            }
        }
        statusInfo.keyId = device->keyId();
//                statusInfo.code = device->codeStr();
        statusInfo.type = device->typeStr();
//                statusInfo.description = device->descriptionStr();
        statusInfo.time = time;
        statusInfo.status = directionStatus;
        statusInfo.layer = "";
        statusInfo.distributionId = "CAN" + QString::number(device->canportAdd()-2)
                                      + "-" + QString::number(device->distributionAdd());
        statusInfo.loopID = device->deviceValue(DEVICE_VALUE_LOOPADDR).toInt();
        statusInfo.deviceID = device->deviceValue(DEVICE_VALUE_ADDR).toInt();
        statusInfo.area = device->deviceValue(DEVICE_VALUE_AREA).toString();
        statusInfo.location = device->deviceValue(DEVICE_VALUE_LOCATION).toString();
        emit statusRecord(statusInfo, SRT_Start, SRO_Add);
    }
}


bool CClientBusiness::hasStandbyPowerFault(CCanport *canport) const
{
    qDebug() << "CClientBusiness::hasStandbyPowerFault"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(canport->getStatus(OBJS_StandbyPowerFault) ||
            canport->getStatus(OBJS_BatteryLowQuantityFault) ||
            canport->getStatus(OBJS_BatteryLowVoltageFault) ||
            canport->getStatus(OBJS_BatteryOverDischargeFault) ||
            canport->getStatus(OBJS_BatteryLineFault) ||
            canport->getStatus(OBJS_ChargerFault) ||
            canport->getStatus(OBJS_PowerOutputFault))
        return true;
    else
        return false;
}

void CClientBusiness::createPath(const QString &path) const
{
    qDebug() << "CClientBusiness::createPath"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    QDir dir(path);
    if(!dir.exists())
        dir.mkpath(path);
}

void CClientBusiness::InitController()
{
    qDebug() << "CClientBusiness::InitController"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(m_isInitController)
        return;
    if(!CGlobal::instance()->dm()->isLoad()){
        CGlobal::instance()->setWorkspaces(m_projectPath);
        CProgramTreeView *programTreeView = CGlobal::instance()->programTreeView();
        programTreeView ->openController();

    }
    if(!CGlobal::instance()->dm()->isLoad())
    {
        CGlobal::instance()->dm()->loadDefault();
        CController* controller = CGlobal::instance()->dm()->controllerAt(0);
        CGlobal::instance()->programTreeView()->setController(controller);
        CGlobal::instance()->designTreeView()->setController(controller);
        CGlobal::instance()->designTreeView()->setCurrentView(1);
    }
    QList<QVariant> param;
    param.append(0);
    emit notifyInformation(NIT_InitControllerResult, param);
    m_faultObjects.clear();
    m_startObjects.clear();
    m_isInitController = true;
}

void CClientBusiness::clearExpectObject(const int type)
{
    qDebug() << "CClientBusiness::clearExpectObject"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(type == SRT_ALL)
    {
        m_faultObjects.clear();
        m_startObjects.clear();
    }
    else if(type == SRT_Start)
    {
        m_startObjects.clear();
    }
    else if(type == SRT_Fault)
    {
        m_faultObjects.clear();
    }

}

void CClientBusiness::updateIsLoopRemoveLogin()
{
    qDebug() << "CClientBusiness::updateIsLoopRemoveLogin"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
    {
        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
        if(canport){
            QList<CDistribution*> list = canport->distributions();
            for(int i=0; i<list.count(); i++){
                CDistribution* distribution = list.at(i);
                if(!distribution)
                    continue;
                if(distribution->isDistributionOnline())
                {
                    QList<CLoop*> loops = distribution->loops();
                    for(int i=0; i<loops.count(); i++){
                        CLoop* loop = loops.at(i);
                        if(!loop)
                            continue;
                    }
                }
            }
        }
    }
}

void CClientBusiness::removeLoginObject(int canportAdd, int distributionAdd, int loopAdd)
{
    qDebug() << "CClientBusiness::removeLoginObject"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if(!canportAdd && !distributionAdd && !loopAdd)
    {
        for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
        {
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
            if(canport){
//                canport->setCanportValue(OBJECT_VALUE_ONLINE,0);
                QList<CDistribution*> list = canport->distributions();
                for(int i=0; i<list.count(); i++){
                    CDistribution* distribution = list.at(i);
                    if(distribution)
                    {
                        distribution->setDistributionOnline(false);
                        distribution->setStatus(OBJS_Online, 0);
                        QList<CLoop*> loops = distribution->loops();
                        for(int i=0; i<loops.count(); i++){
                            CLoop* loop = loops.at(i);
                            //清除回路状态
                            if(loop)
                            {
                                QList<CDevice*> devices = loop->devices();
                                for(int m=0; m<devices.count(); m++){
                                    CDevice* device = devices.at(m);
                                    if(device)
                                    {
                                        device->setDeviceLogin(false);
                                        device->setDatabaseLogin(false);
                                        device->setDeviceOnline(false);
//                                        device->setDeviceValue(DEVICE_VALUE_NOLOGIN,1);
//                                        device->setDeviceValue(OBJECT_VALUE_ONLINE,0);
//                                        //配置且注册
//                                        if(device->deviceValue(DEVICE_VALUE_ISUSED) == 1)
//                                        {
//                                            //仅配置
//                                            device->setDeviceValue(DEVICE_VALUE_ISUSED, 0);
//                                        }
//                                        //仅注册
//                                        else if(device->deviceValue(DEVICE_VALUE_ISUSED) == 2)
//                                        {
//                                            //未定义
//                                            device->setDeviceValue(DEVICE_VALUE_ISUSED, 3);
//                                        }
                                    }
                                }
                                loop->setLoopLogin(false);
//                                loop->setloopValue(LOOP_VALUE_NOLOGIN,1);
                                //清除注册回路灯具数量置零
                                loop->setDeviceOnlineTotal(0);
                                loop->resetLoopPower();
//                                loop->setDeviceOnlineTotalBak(0);
                                devices.clear();
                            }
                        }
                        loops.clear();
                    }
                }
                list.clear();
                CGlobal::instance()->InformationWindow()->hide();
            }
        }
    }
    else
    {
        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(canportAdd);
        if(canport){
            if(distributionAdd == 0)
            {
                canport->setCanportValue(OBJECT_VALUE_ONLINE,0);
            }
            QList<CDistribution*> list = canport->distributions();
            for(int i=0; i<list.count(); i++){
                CDistribution* distribution = list.at(i);
                if(distribution)
                {
                    if((distributionAdd == 0) || (distribution->distributionAddress() == distributionAdd)){
                        if(!m_isNotRemoveDistributionLogin && (loopAdd == 0))
                        {
                            distribution->setDistributionOnline(false);
                            distribution->setDistributionLogin(false);
                            distribution->setStatus(OBJS_Online, 0);
                        }
                        m_isNotRemoveDistributionLogin = false;
                        QList<CLoop*> loops = distribution->loops();
                        for(int i=0; i<loops.count(); i++){
                            CLoop* loop = loops.at(i);
                            if(!loop)
                                continue;
                            //当回路为0（清除整个集中电源）或者回路地址正确时清除回路状态
                            if((loopAdd == 0) || (loopAdd == loop->loopAdd())){
                                QList<CDevice*> devices = loop->devices();
                                for(int m=0; m<devices.count(); m++){
                                    CDevice* device = devices.at(m);
                                    if(device)
                                    {
                                        device->setDatabaseLogin(false);
                                        device->setDeviceLogin(false);
                                        device->setDeviceOnline(false);
//                                        device->setDeviceValue(DEVICE_VALUE_NOLOGIN,1);
//                                        device->setDeviceValue(OBJECT_VALUE_ONLINE,0);
//                                        //配置且注册
//                                        if(device->deviceValue(DEVICE_VALUE_ISUSED) == 1)
//                                        {
//                                            //仅配置
//                                            device->setDeviceValue(DEVICE_VALUE_ISUSED, 0);
//                                        }
//                                        //仅注册
//                                        else if(device->deviceValue(DEVICE_VALUE_ISUSED) == 2)
//                                        {
//                                            //未定义
//                                            device->setDeviceValue(DEVICE_VALUE_ISUSED, 3);
//                                        }
                                    }
                                }
//                                loop->setloopValue(LOOP_VALUE_NOLOGIN,1);
                                loop->setLoopLogin(false);
                                //清除注册回路灯具数量置零
                                loop->setDeviceOnlineTotal(0);
                                loop->resetLoopPower();
//                                loop->setDeviceOnlineTotalBak(0);
                                devices.clear();
                            }
                        }
                        loops.clear();
                    }
                }

            }
            list.clear();
            CGlobal::instance()->InformationWindow()->hide();
        }
    }
    ConfigFileManager cfg;
    cfg.SaveConfigFile();//写入配置文件
}

void CClientBusiness::closeController()
{
    qDebug() << "CClientBusiness::closeController"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CGlobal::instance()->programTreeView()->closeController();
    m_currentStatusId = 0;
    m_currentRecvStatusId = 0;
    m_currentRecvStatusNumber = 0;
}

void CClientBusiness::clearProjectFile()
{
    qDebug() << "CClientBusiness::clearProjectFile"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    QFile file(m_projectFile);
    file.remove();
}

void CClientBusiness::reset()
{
    qDebug() << "CClientBusiness::reset"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    QList<QVariant> param;
    m_bForceEmergency = true;
    emit notifyInformation(NIT_Reset, param);
}

void CClientBusiness::clearStatusObject(bool reserveLogin)
{
    qDebug() << "CClientBusiness::clearStatusObject"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    m_currentStatusId = 0;
    m_currentRecvStatusId = 0;
    m_currentRecvStatusNumber = 0;
    CGlobal::instance()->dm()->clearStatusObjects(reserveLogin);
}



CCanport *CClientBusiness::createUndefinedCanport(CController *controller, int address, int keyId)
{
    qDebug() << "CClientBusiness::createUndefinedCanport"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CCanport* canport = new CCanport(keyId);
    if(!canport)
        return NULL;
    canport->setCanportId(address);
    canport->setIsUndefined(true);
    canport->setCanportValue(CANPORT_VALUE_NAME, canport->canportValue(CANPORT_VALUE_NAME).toString().append(QString::number(address)));
    if(!controller->addCanport(canport))
    {
        delete canport;
        canport = NULL;
    }
    return canport;
}

CDistribution *CClientBusiness::createUndefinedDistribution(CCanport *canport, int address, QString str, int keyId)
{
    qDebug() << "CClientBusiness::createUndefinedDistribution"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CDistribution* distribution = new CDistribution(keyId);
    if(!distribution)
        return NULL;
    distribution->setDistributionId(address);
    distribution->setIsUndefined(true);
    distribution->setDistributionValue(DISTRIBUTION_VALUE_DESCRIPTION,str);
    distribution->setDistributionValue(DISTRIBUTION_VALUE_ADDR,address);
    int canportID = canport->canportValue(CANPORT_VALUE_PORT).toInt();
//    distribution->setDistributionValue(DISTRIBUTION_VALUE_NAME, distribution->distributionValue(DISTRIBUTION_VALUE_NAME).toString().append(QString::number(address)));
    //1为工程，63为控制器，100-1000为集中电源(CAN1为101-200，CAN2为201-300......)，1000-2000为回路，大于2000为灯具
    for(int i = 101; i<1000; i++)
    {
        if(canport->isdistributionByKeyId(i+(canportID-1)*100) == true)
        {
            distribution->setKeyId(i+(canportID-1)*100);
            break;
        }
    }
    if(!canport->addDistribution(distribution))
    {
        delete distribution;
        distribution = NULL;
    }
    return distribution;
}

CLoop *CClientBusiness::createUndefinedLoop(CDistribution* distribution, int address, int keyId)
{
    qDebug() << "CClientBusiness::createUndefinedLoop"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    CLoop* loop = new CLoop(keyId);
    if(!loop)
        return NULL;
    loop->setLoopId(address);
    loop->setIsUndefined(true);
    loop->setloopValue(LOOP_VALUE_NAME, loop->loopValue(LOOP_VALUE_NAME).toString().append(QString::number(address)));
    //1为工程，63为控制器，100-1000为集中电源，1000-2000为回路，大于2000为灯具
    for(int i = 1001; i<2000; i++)
    {
        if(distribution->loopByKeyId(i) == true)
        {
            loop->setKeyId(i);
            break;
        }
    }

    if(!distribution->addLoop(loop))
    {
        delete loop;
        loop = NULL;
    }
    return loop;
}

CDevice *CClientBusiness::createUndefinedDevice(CLoop* loop)
{
    qDebug() << "CClientBusiness::createUndefinedDevice"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    loop->initDevices();
    QList<CDevice*> devices = loop->devices();
    CDevice* device = devices.at(loop->deviceCount()-1);
    if(!device)
        return NULL;
    //1为工程，63为控制器，100-1000为集中电源，1000-2000为回路，大于2000为灯具
    for(int i = 2001; i<10000; i++)
    {
        if(loop->deviceByKeyId(i) == true)
        {
            device->setKeyId(i);
            break;
        }
    }
    devices.clear();
    return device;
}

void CClientBusiness::slot_saveLoginData()
{
    qDebug() << "CClientBusiness::slot_saveLoginData"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    ConfigFileManager cfg;
    cfg.SaveConfigFile();//写入配置文件
}

int CClientBusiness::deviceType(int typeId)
{
    qDebug() << "CClientBusiness::deviceType"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    if((typeId >= 150 && typeId < 200) || (typeId >= 50 && typeId < 100))
        return NCT_LightType;
    else if(typeId >= 120 && typeId <= 124)
        return NCT_ArrowType;
    else
        return NCT_UndergroundType;
}

//void CClientBusiness::slot_ledStatusSend()
//{
//    CMsgLedInfo msgLed;
//    msgLed.nLedID = 4;
//    msgLed.nLedStatus = m_faultObjects.isEmpty()?0:1;
//    exeCommand(NCT_LedStatus, &msgLed);
//    msgLed.nLedID = 5;
//    msgLed.nLedStatus = m_startObjects.isEmpty()?0:1;
//    exeCommand(NCT_LedStatus, &msgLed);
//}

void CClientBusiness::ParsePacket(int nMsgType, const char *data, int nLen)
{
    qDebug() << "CClientBusiness::ParsePacket"
             << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss:zzz");
    m_communication->ParsePacket(nMsgType, data, nLen);
}
