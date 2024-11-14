#include "ui_dlgtimeinterval.h"
#include "dlgtimeinterval.h"
#include "cglobal.h"
#include <QButtonGroup>
#include "business/cprocessmqtt.h"
#include "business/cprocessntp.h"

dlgTimeInterval::dlgTimeInterval(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgTimeInterval)
{
    ui->setupUi(this);
    this->setWindowTitle("系统设置");
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumWidth(800);
    setMinimumHeight(480);
    CGlobal::instance()->m_HaveDialog = true;
    isThreadRunning = false;

    QButtonGroup *startRuleGroup = new QButtonGroup(this);
    startRuleGroup->addButton(ui->allStartCheckBox);
    startRuleGroup->addButton(ui->onlyStartGroupCheckBox);
    startRuleGroup->addButton(ui->onlyStartPageCheckBox);
    startRuleGroup->setExclusive(true);
    ui->allStartCheckBox->setChecked(true);

    QButtonGroup *CanGroup = new QButtonGroup(this);
    CanGroup->addButton(ui->Can4CheckBox);
    CanGroup->addButton(ui->Can8CheckBox);
    CanGroup->setExclusive(true);
    ui->Can4CheckBox->setChecked(true);

    QButtonGroup *WLANGroup = new QButtonGroup(this);
    WLANGroup->addButton(ui->singleWLAN);
    WLANGroup->addButton(ui->doubleWLAN);
    WLANGroup->setExclusive(true);
    ui->singleWLAN->setChecked(true);

    QButtonGroup *ARTUGroup = new QButtonGroup(this);
    ARTUGroup->addButton(ui->forbidARTUCheckBox);
    ARTUGroup->addButton(ui->ARTU079KCheckBox);
    ARTUGroup->addButton(ui->ARTU079KJCheckBox);
    ARTUGroup->addButton(ui->ARTU426CheckBox);
    ARTUGroup->setExclusive(true);
    ui->forbidARTUCheckBox->setChecked(true);

    ui->EnergyCheckBox->setChecked(CGlobal::instance()->m_energymode);
    ui->EnergyCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");

    ui->DirectionTwinkleOneCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");
    ui->DirectionTwinkleDoubleCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");
    ui->TwinkleConfigCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");

    ui->TwinkleCheckBox->setChecked(CGlobal::instance()->m_TwinkleControl);
    ui->TwinkleCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");
    ui->emergencyOnlyDistributionCheckBox->setChecked(CGlobal::instance()->m_emergencyOnlyDistribution);
    ui->emergencyOnlyDistributionCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");

    ui->autoPageCheckBox->setChecked(CGlobal::instance()->m_isAutoPage);
    ui->autoPageCheckBox->setStyleSheet("QCheckBox::indicator:checked {image:url(:/images/Check.png);}");

    ui->version_ledkey->setText(CGlobal::instance()->m_version_ledkey);
    ui->version_can1can2->setText(CGlobal::instance()->m_version_can1can2);
    ui->version_can3can4->setText(CGlobal::instance()->m_version_can3can4);
    ui->version_can5can6->setText(CGlobal::instance()->m_version_can5can6);
    ui->version_can7can8->setText(CGlobal::instance()->m_version_can7can8);
    int index = ui->comboBox_testLinkageCom->findText(CGlobal::instance()->m_baudRate);
    ui->comboBox_testLinkageCom->setCurrentIndex(index);
    ui->m_linkageStatus->setText("未连接");
    ui->lineEdit_phoneNumber->setText(CGlobal::instance()->m_LinkmanPhoneNumer);
    ui->lineEdit_firepointNumber->setText(QString::number(CGlobal::instance()->m_startFirepointNumber));
    if(CGlobal::instance()->m_LiftTime > 1000)
        ui->UseTime->setText("永久");
    else
        ui->UseTime->setText(QString::number(CGlobal::instance()->m_LiftTime));

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->timeEdit->setCalendarPopup(true);
    ui->timeEdit->setDateTime(QDateTime::currentDateTime());


    m_getTmpip1 = "";
    m_getTmpgateway1 = "";
    m_getTmpmask1 = "255.255.255.0";

    m_getTmpip2 = "";
    m_getTmpgateway2 = "";
    m_getTmpmask2 = "255.255.255.0";

    m_dateTimeStr = "";

    QIcon icon(":/images/startinfo.png"); // 图标路径
    m_triangleButton = new TriangleButton(icon,this);
    // 设置按钮样式表，隐藏按钮的边框和背景
    m_triangleButton->setStyleSheet("border: none; background: none;");
    m_triangleButton->setGeometry(1320,610,32,32);
    connect(m_triangleButton, SIGNAL(clicked()), this, SLOT(on_triangleButton_clicked()));

    ui->m_comStatus->setText("未连接");
    m_mqttClient = new QMqttClient;
    m_processMqtt = new CprocessMqtt(m_mqttClient);
    // 创建MQTT线程
    m_mqttThread = new QThread;
    m_mqttClient->moveToThread(m_mqttThread);
    // 启动MQTT线程
    m_mqttThread->start();
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(statusSendToMQTT(CObject*, bool)),
            m_processMqtt, SLOT(slot_sendDeviceStatusMsg(CObject*, bool)));
    connect(m_processMqtt, SIGNAL(hostControlMsg(int)),
            this, SLOT(slot_setHostControlMsg(int)));
    connect(m_processMqtt, SIGNAL(connectStatus(bool)),
            this, SLOT(slot_setComStatus(bool)));
    connect(this, SIGNAL(uploadStatusToMQTT()),
            m_processMqtt, SLOT(slot_uploadAllDeviceStatus()));

    m_ntpClient = new QUdpSocket;
    m_processNtp = new CprocessNtp("cn.pool.ntp.org", m_ntpClient);
//    // 创建NTP线程
//    m_ntpThread = new QThread;
//    m_processNtp->moveToThread(m_ntpThread);
//    // 启动MQTT线程
//    m_ntpThread->start();
}


dlgTimeInterval::~dlgTimeInterval()
{
    delete ui;
    CGlobal::instance()->setTimeInterval(NULL);
    CGlobal::instance()->m_HaveDialog = false;
    delete m_mqttClient;
    delete m_processMqtt;
    delete m_mqttThread;

    delete m_ntpClient;
    delete m_processNtp;
    delete m_ntpThread;
}


void dlgTimeInterval::saveSqliteData(QString ParamName, QString ParamValue)
{
    qDebug() << "dlgTimeInterval::saveSqliteData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
    db.setDatabaseName(fileName);
    if(!db.open())
        return;
    QSqlQuery query(db);
    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('%1', '%2');").arg(ParamName).arg(ParamValue));

//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('TwinkleControl', '%1');").arg(CGlobal::instance()->m_TwinkleControl));
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('LampEmergencyType', '%1');").arg(CGlobal::instance()->m_lampEmergencyType));
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('EmergencyOnlyDistribution', '%1');").arg(CGlobal::instance()->m_emergencyOnlyDistribution));
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('LinkmanPhoneNumer', '%1');").arg(CGlobal::instance()->m_LinkmanPhoneNumer));
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('StartFirepointNumber', '%1');").arg(CGlobal::instance()->m_startFirepointNumber));
//    if(ui->m_hostip->text() != "")
//        query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('DataServerIP', '%1');").arg(CGlobal::instance()->m_DataServerIP));
//    if(ui->m_com->text() != "")
//        query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('DataServerPort', '%1');").arg(CGlobal::instance()->m_DataServerPort));
    db.commit();
    db.close();
}

void dlgTimeInterval::on_TwinkleCheckBox_clicked()
{
    CGlobal::instance()->m_TwinkleControl = ui->TwinkleCheckBox->isChecked();
    saveSqliteData("TwinkleControl", QString::number(CGlobal::instance()->m_TwinkleControl));
}

void dlgTimeInterval::on_DirectionTwinkleOneCheckBox_clicked()
{
    CGlobal::instance()->m_lampEmergencyType = 0;
    if(ui->DirectionTwinkleOneCheckBox->isChecked())
    {
        ui->DirectionTwinkleDoubleCheckBox->setChecked(false);
        ui->TwinkleConfigCheckBox->setChecked(false);
    }
    saveSqliteData("LampEmergencyType", QString::number(CGlobal::instance()->m_lampEmergencyType));
}

void dlgTimeInterval::on_DirectionTwinkleDoubleCheckBox_clicked()
{
    CGlobal::instance()->m_lampEmergencyType |= 0x01;
    if(ui->DirectionTwinkleDoubleCheckBox->isChecked())
    {
        ui->DirectionTwinkleOneCheckBox->setChecked(false);
    }
    saveSqliteData("LampEmergencyType", QString::number(CGlobal::instance()->m_lampEmergencyType));
}

void dlgTimeInterval::on_TwinkleConfigCheckBox_clicked()
{
    CGlobal::instance()->m_lampEmergencyType |= 0x02;
    if(ui->TwinkleConfigCheckBox->isChecked())
    {
        ui->DirectionTwinkleOneCheckBox->setChecked(false);
    }
    saveSqliteData("LampEmergencyType", QString::number(CGlobal::instance()->m_lampEmergencyType));
}


void dlgTimeInterval::on_emergencyOnlyDistributionCheckBox_clicked()
{
    CGlobal::instance()->m_emergencyOnlyDistribution = ui->emergencyOnlyDistributionCheckBox->isChecked();
    saveSqliteData("EmergencyOnlyDistribution", QString::number(CGlobal::instance()->m_emergencyOnlyDistribution));
}

void dlgTimeInterval::on_allStartCheckBox_clicked()
{
    CGlobal::instance()->m_nStartRule = RULE_AllStart;
}

void dlgTimeInterval::on_onlyStartPageCheckBox_clicked()
{
    CGlobal::instance()->m_nStartRule = RULE_OnlyPage;
}

void dlgTimeInterval::on_onlyStartGroupCheckBox_clicked()
{
    CGlobal::instance()->m_nStartRule = RULE_OnlyGroup;
}

void dlgTimeInterval::on_Can4CheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_Can4CheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
//    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
//    db.setDatabaseName(fileName);
//    if(!db.open())
//        return;
//    QSqlQuery query(db);
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('CanNumber', '%1');").arg(4));
//    db.commit();
//    db.close();
    saveSqliteData("CanNumber", QString::number(4));
}

void dlgTimeInterval::on_Can8CheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_Can8CheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_HaveDialog = true;
    // 创建一个QFont对象并设置字体属性
    QFont font;
    font.setPointSize(12); // 设置字体大小为12像素

    // 在QMessageBox中设置字体
    QMessageBox messageBox;
    messageBox.setFont(font);
    QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
    messageBox.setStyleSheet(styleSheet);
    messageBox.setWindowTitle("软件信息");
    messageBox.setIcon(QMessageBox::NoIcon);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.button(QMessageBox::Ok)->setText("确定");
    QString log = "请确认主机硬件是否支持8路CAN通讯，若不支持，请联系厂家。";
    messageBox.setText(log);
    messageBox.exec();
    CGlobal::instance()->m_HaveDialog = false;
//    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
//    db.setDatabaseName(fileName);
//    if(!db.open())
//        return;
//    QSqlQuery query(db);
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('CanNumber', '%1');").arg(8));
//    db.commit();
//    db.close();
    saveSqliteData("CanNumber", QString::number(8));
}

void dlgTimeInterval::on_singleWLAN_clicked()
{
    qDebug() << "dlgTimeInterval::on_singleWLAN_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_isDoubleWLAN = false;
//    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
//    db.setDatabaseName(fileName);
//    if(!db.open())
//        return;
//    QSqlQuery query(db);
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('DoubleWLAN', '%1');").arg(false));
//    db.commit();
//    db.close();
    saveSqliteData("DoubleWLAN", QString::number(0));
}

void dlgTimeInterval::on_doubleWLAN_clicked()
{
    qDebug() << "dlgTimeInterval::on_doubleWLAN_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_HaveDialog = true;
    // 创建一个QFont对象并设置字体属性
    QFont font;
    font.setPointSize(12); // 设置字体大小为12像素

    // 在QMessageBox中设置字体
    QMessageBox messageBox;
    messageBox.setFont(font);
    QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
    messageBox.setStyleSheet(styleSheet);
    messageBox.setWindowTitle("软件信息");
    messageBox.setIcon(QMessageBox::NoIcon);
    messageBox.setStandardButtons(QMessageBox::Ok);
    messageBox.button(QMessageBox::Ok)->setText("确定");
    QString log = "请确认主机硬件是否支持双网口通讯，若不支持，请联系厂家。";
    messageBox.setText(log);
    messageBox.exec();
    CGlobal::instance()->m_HaveDialog = false;
    CGlobal::instance()->m_isDoubleWLAN = true;
//    QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
//    db.setDatabaseName(fileName);
//    if(!db.open())
//        return;
//    QSqlQuery query(db);
//    query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('DoubleWLAN', '%1');").arg(true));
//    db.commit();
//    db.close();
    saveSqliteData("DoubleWLAN", QString::number(1));
}

void dlgTimeInterval::on_EnergyCheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_EnergyCheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(CGlobal::instance()->m_energymode != ui->EnergyCheckBox->isChecked())
    {
        CGlobal::instance()->m_energymode = ui->EnergyCheckBox->isChecked();
        for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
        {
            CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
            if(!canport)
                return;
            QList<CDistribution*> list = canport->distributions();
            for(int i=0; i<list.count(); i++){
                CDistribution* distribution = list.at(i);
                if(!distribution)
                    continue;
                QList<CLoop*> loops = distribution->loops();
                for(int i=0; i<loops.count(); i++){
                    CLoop* loop = loops.at(i);
                    if(!loop)
                        continue;
                    QList<CDevice*> devices = loop->devices();
                    for(int i=0; i<devices.count(); i++){
                        CDevice* device = devices.at(i);
                        if(!device)
                            continue;
                        if(device->deviceTypeId() < 150)
                        {
                            CMsgObjectStatus msgObjectStatus;
                            msgObjectStatus.nCanportAdd = device->canportAdd();
                            msgObjectStatus.nDisID = device->distributionAdd();
                            msgObjectStatus.nLoopID = device->loopAdd();
                            msgObjectStatus.nDeviceID = device->deviceAdd();
                            msgObjectStatus.nStatusID = CGlobal::instance()->m_energymode;
                            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_EnergyMode, &msgObjectStatus);
                        }
                    }
                    devices.clear();
                }
                loops.clear();
            }
            list.clear();
        }
    }
}


void dlgTimeInterval::on_pushButton_can1can2_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_can1can2_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CMsgObjectStatus msgObjectStatus;
    msgObjectStatus.nCanportAdd = 3;
    msgObjectStatus.nDisID = 63;
    //读设备信息
    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_ReadDeviceInfo,&msgObjectStatus);
}

void dlgTimeInterval::on_pushButton_can3can4_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_can3can4_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CMsgObjectStatus msgObjectStatus;
    msgObjectStatus.nCanportAdd = 5;
    msgObjectStatus.nDisID = 63;
    //读设备信息
    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_ReadDeviceInfo,&msgObjectStatus);
}

void dlgTimeInterval::on_pushButton_can5can6_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_can5can6_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CMsgObjectStatus msgObjectStatus;
    msgObjectStatus.nCanportAdd = 7;
    msgObjectStatus.nDisID = 63;
    //读设备信息
    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_ReadDeviceInfo,&msgObjectStatus);
}

void dlgTimeInterval::on_pushButton_can7can8_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_can7can8_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CMsgObjectStatus msgObjectStatus;
    msgObjectStatus.nCanportAdd = 9;
    msgObjectStatus.nDisID = 63;
    //读设备信息
    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_ReadDeviceInfo,&msgObjectStatus);
}


void dlgTimeInterval::on_pushButton_UseTime_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_UseTime_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    dlgUseTime useTime;
    useTime.exec();
}

void dlgTimeInterval::on_autoPageCheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_autoPageCheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_isAutoPage = ui->autoPageCheckBox->isChecked();
    CGlobal::instance()->designTreeView()->setAutoPage(CGlobal::instance()->m_isAutoPage);
}

void dlgTimeInterval::on_pushButton_phoneNumber_clicked()
{
    qDebug() << "dlgadminParamPage::on_pushButton_phoneNumber_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_LinkmanPhoneNumer = ui->lineEdit_phoneNumber->text();
    saveSqliteData("LinkmanPhoneNumer", CGlobal::instance()->m_LinkmanPhoneNumer);
}

void dlgTimeInterval::on_triangleButton_clicked()
{
    qDebug() << "dlgTimeInterval::on_triangleButton_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(CGlobal::instance()->m_adminParamTime > QDateTime::currentDateTime())
    {
        CGlobal::instance()->AdminParamPage()->updateSqliteData();
        // 替换界面
        CGlobal::instance()->TopToolBar()->changeCenterFrameWidget(CGlobal::instance()->AdminParamPage());
    }
    else
    {
        dlgadminParam adminParam;
        adminParam.exec();
    }
}

void dlgTimeInterval::on_pushButton_testLinkageCom_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_testLinkageCom_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QFont font;
    font.setPointSize(12); // 设置字体大小为12像素
    // 在QMessageBox中设置字体
    QMessageBox messageBox;
    messageBox.setFont(font);
    QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
    messageBox.setStyleSheet(styleSheet);
    messageBox.setIcon(QMessageBox::NoIcon);
    messageBox.setWindowTitle("修改波特率");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);
    messageBox.button(QMessageBox::Yes)->setText("是");
    messageBox.button(QMessageBox::Cancel)->setText("取消");
    QString log = "确定要修改与火灾报警控制器通讯的波特率吗?";
    messageBox.setText(log);
    int ret = messageBox.exec();
    if(ret == QMessageBox::Yes)
    {
        CGlobal::instance()->m_baudRate = ui->comboBox_testLinkageCom->currentText();
//        QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
//        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
//        db.setDatabaseName(fileName);
//        if(!db.open())
//            return;
//        QSqlQuery query(db);
//        query.exec(QString("INSERT OR REPLACE INTO ParamInfo (ParamName, ParamValue) VALUES ('BaudRate', '%1');").arg(CGlobal::instance()->m_baudRate));
//        db.commit();
//        db.close();
        saveSqliteData("BaudRate", CGlobal::instance()->m_baudRate);
        CMsgObjectStatus m_MsgObjectStatus;
        m_MsgObjectStatus.strdata = CGlobal::instance()->m_baudRate;
        CGlobal::instance()->ClientBusiness()->exeCommand(NCT_LinkageComBaudRate, &m_MsgObjectStatus);
    }
    else if(ret == QMessageBox::Cancel)
    {
        int index = ui->comboBox_testLinkageCom->findText(CGlobal::instance()->m_baudRate);
        ui->comboBox_testLinkageCom->setCurrentIndex(index);
    }
}

void dlgTimeInterval::on_testLinkageComButton_clicked()
{
    qDebug() << "dlgTimeInterval::on_testLinkageComButton_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->m_testLinkageComResult->setText("测试中");
    CMsgNull m_MsgNUll;
    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_TestLinkageCom, &m_MsgNUll);
    QTimer::singleShot(5000, this, SLOT(slot_testComResult()));
}

void dlgTimeInterval::slot_testComResult()
{
    qDebug() << "dlgTimeInterval::slot_testComResult"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(ui->m_testLinkageComResult->text() == "测试中")
        ui->m_testLinkageComResult->setText("失败！");
}

void dlgTimeInterval::setTestLinkageComResult(QString str)
{
    qDebug() << "dlgTimeInterval::setTestLinkageComResult"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->m_testLinkageComResult->setText(str);
}

void dlgTimeInterval::setLinkageComStatus(QString str)
{
    qDebug() << "dlgTimeInterval::setLinkageComStatus"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->m_linkageStatus->setText(str);
}

void dlgTimeInterval::on_m_ButtonTimeSet_clicked()
{
    qDebug() << "dlgTimeInterval::on_m_ButtonTimeSet_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QDateTime combinedDateTime(ui->dateEdit->date(), ui->timeEdit->time());
    setSystemTime(combinedDateTime.toString("yyyy-MM-dd hh:mm:ss"));
}

void dlgTimeInterval::setSystemTime(QString dateTime)
{
    m_dateTimeStr = dateTime;
    timeThread *thread = new timeThread(this);
    connect(thread, SIGNAL(timeFinished()), this, SLOT(slot_timeFinished()), Qt::QueuedConnection);
    thread->start();
}

void dlgTimeInterval::slot_timeFinished()
{
    qDebug() << "dlgTimeInterval::slot_timeFinished"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    // 进入 dlgTimeInterval 界面的逻辑
    CGlobal::instance()->TimeInterval()->exec();
    QThread *finishedThread = qobject_cast<QThread*>(sender());
    if (finishedThread) {
        // 等待线程结束，确保线程执行已完成
        finishedThread->wait();
        // 删除线程对象
        finishedThread->deleteLater(); // 推荐使用 deleteLater()，安全删除线程对象
    }
}


void timeThread::run()
{
    qDebug() << "timeThread::run"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    // 创建一个 QProcess 对象
    QProcess process;
    // 设置要执行的 shell 命令
    QStringList args;
    args << "/home/xfss/root/SystemSet/settime.sh" << CGlobal::instance()->TimeInterval()->m_dateTimeStr;

    // 启动 shell 脚本文件并传递参数
    process.start("bash", args);
    if(process.waitForFinished())
    {
        emit timeFinished();  // 发送成功信号
    }
}

void dlgTimeInterval::on_pingButton_clicked()
{
    qDebug() << "dlgTimeInterval::on_pingButton_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->m_pingResult->setText("测试中");
    pingThread *ping = new pingThread(this);
    connect(ping, SIGNAL(pingFinished(double)), this, SLOT(slot_pingFinished(double)), Qt::QueuedConnection);
    if(ui->m_pingIP->text() != NULL)
        ping->setpingIP(ui->m_pingIP->text());
    ping->start();
}

void dlgTimeInterval::slot_pingFinished(double successRate)
{
    qDebug() << "dlgTimeInterval::slot_pingFinished"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QThread *finishedThread = qobject_cast<QThread*>(sender());
    if (finishedThread) {
        // 等待线程结束，确保线程执行已完成
        finishedThread->wait();
        // 删除线程对象
        finishedThread->deleteLater(); // 推荐使用 deleteLater()，安全删除线程对象
    }
    // 进入 dlgTimeInterval 界面的逻辑
    CGlobal::instance()->TimeInterval()->exec();
    QString result = QString::number(successRate) + "%";
    ui->m_pingResult->setText(result);
}

void pingThread::run()
{
    qDebug() << "pingThread::run"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    int receivedPackets = 0; // 收到的数据包数
    double successRate = 0.0;

    // 创建一个 QProcess 对象
    QProcess process;

    // 设置要执行的 shell 命令
    QStringList args;
    args << "/home/xfss/root/SystemSet/ping.sh" << m_pingIP;

    // 启动 shell 脚本文件并传递参数
    process.start("bash", args);

    process.waitForFinished();
    QString output = process.readAllStandardOutput();

    // 解析输出结果并发射信号
    QStringList lines = output.split("\n");// 存储Ping命令输出的每行结果
    foreach (QString line, lines) {
        if (line.contains("bytes from")) {
            receivedPackets++;
        }
    }
    successRate = (static_cast<double>(receivedPackets) / 5) * 100;
    emit pingFinished(successRate);  // 发送成功率信号
}


//设置IP地址
void dlgTimeInterval::setWLANData()
{
    qDebug() << "dlgTimeInterval::setWLANData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ipsetThread *ipset = new ipsetThread(this);
    connect(ipset, SIGNAL(ipsetFinished()), this, SLOT(slot_ipsetFinished()), Qt::QueuedConnection);
    ipset->start();
}

void dlgTimeInterval::slot_ipsetFinished()
{
    qDebug() << "dlgTimeInterval::slot_ipsetFinished"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    // 进入 dlgTimeInterval 界面的逻辑
    CGlobal::instance()->TimeInterval()->exec();
    QThread *finishedThread = qobject_cast<QThread*>(sender());
    if (finishedThread) {
        // 等待线程结束，确保线程执行已完成
        finishedThread->wait();
        // 删除线程对象
        finishedThread->deleteLater(); // 推荐使用 deleteLater()，安全删除线程对象
    }
}

void ipsetThread::run()
{
    qDebug() << "ipsetThread::run"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    // 创建一个 QProcess 对象
    QProcess process;
    // 设置要执行的 shell 命令
    QString scriptPath = "/home/xfss/root/SystemSet/setip.sh";
    // 添加要传递给脚本的参数（如果需要的话）
    QStringList arguments;
    arguments << CGlobal::instance()->TimeInterval()->m_getTmpip1 << CGlobal::instance()->TimeInterval()->m_getTmpmask1
              << CGlobal::instance()->TimeInterval()->m_getTmpgateway1 << CGlobal::instance()->TimeInterval()->m_getTmpip2
              << CGlobal::instance()->TimeInterval()->m_getTmpmask2 << CGlobal::instance()->TimeInterval()->m_getTmpgateway2
              << CGlobal::instance()->m_wlanName;

    // 启动 shell 脚本文件并传递参数
    process.start("bash", QStringList() << scriptPath << arguments);
    if(process.waitForFinished())
    {
        emit ipsetFinished();  // 发送成功信号
        QFile file("/etc/network/interfaces"); // 指定要修改的文件路径
        if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            qDebug() << "无法打开文件";
            return;
        }

        QTextStream in(&file);
        QStringList lines;
        bool shouldAddExtraContent = true; // 指示是否需要添加额外内容
        while (!in.atEnd())
        {
            QString line = in.readLine();
            if (line.contains("iface enp1s0 inet static"))
            {
                shouldAddExtraContent = false;
                lines.append("iface enp1s0 inet static");
                lines.append("address " + CGlobal::instance()->TimeInterval()->m_getTmpip1);
                lines.append("netmask " + CGlobal::instance()->TimeInterval()->m_getTmpmask1);
                if(CGlobal::instance()->TimeInterval()->m_getTmpgateway1 != "")
                    lines.append("gateway " + CGlobal::instance()->TimeInterval()->m_getTmpgateway1);
                lines.append("dns-nameservers 8.8.8.8");
                if(CGlobal::instance()->m_isDoubleWLAN)
                {
                    shouldAddExtraContent = false;
                    lines.append("");
                    QString str = "auto " + CGlobal::instance()->m_wlanName;
                    lines.append(str);
                    str = "iface " + CGlobal::instance()->m_wlanName + " inet static";
                    lines.append(str);
                    lines.append("address " + CGlobal::instance()->TimeInterval()->m_getTmpip2);
                    lines.append("netmask " + CGlobal::instance()->TimeInterval()->m_getTmpmask2);
                    if(CGlobal::instance()->TimeInterval()->m_getTmpgateway2 != "")
                        lines.append("gateway " + CGlobal::instance()->TimeInterval()->m_getTmpgateway2);
                    lines.append("dns-nameservers 8.8.8.8");
                }
            }
            if(shouldAddExtraContent)
            {
                lines.append(line);
            }

        }

        file.resize(0);
        QTextStream out(&file);
        for (int i = 0; i < lines.size(); ++i)
        {
            out << lines.at(i) << "\n"; // 使用 at() 方法获取元素
        }

        file.close();
    }

}


void dlgTimeInterval::on_pushButton_saveWlan_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_saveWlan_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QFile file("home/xfss/root/logfile/IPChangeRecord.txt");

    // 以追加写入模式打开文件，如果文件不存在则新建
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        if(isWLANChanged())
        {
            QString str = "////" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") + "\n" +
                    "网口1地址:" + ui->m_myip1->text() + "\n" +
                    "网口1网关:" + ui->m_gateway1->text() + "\n";
            m_getTmpgateway1 = ui->m_gateway1->text();
            if(CGlobal::instance()->m_isDoubleWLAN)
            {
                str = str + "网口2地址:" + ui->m_myip2->text() + "\n" +
                        "网口2网关:" + ui->m_gateway2->text() + "\n" + "\n";
                m_getTmpgateway2 = ui->m_gateway2->text();
            }
            else
            {
                str = str + "\n";
            }
            out << str;  // 写入数据
        }

        file.close();
    }
    m_getTmpip1 = ui->m_myip1->text();
    m_getTmpip2 = ui->m_myip2->text();
    setWLANData();
}


void dlgTimeInterval::on_pushButton_saveHostAddress_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_saveHostAddress_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");

    if(!isHostAddressChanged())
        return;
    saveSqliteData("MQTTHost", ui->m_hostAddress->text());
    saveSqliteData("MQTTCom", ui->m_com->text());
    CGlobal::instance()->m_mqttHost = ui->m_hostAddress->text();
    CGlobal::instance()->m_mqttCom = ui->m_com->text().toInt();
    m_processMqtt->manualDisconnectToBroker();
    m_processMqtt->manualConnectToBroker(CGlobal::instance()->m_mqttHost,CGlobal::instance()->m_mqttCom);
    QFile file("home/xfss/root/logfile/IPChangeRecord.txt");
    // 以追加写入模式打开文件，如果文件不存在则新建
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        QString str = "////" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss:zzz") + "\n" +
                "MQTT地址:" + ui->m_hostAddress->text() + "\n" +
                "MQTT端口号:" + ui->m_com->text() + "\n" + "\n";
        out << str;  // 写入数据
        file.close();
    }  
}

void dlgTimeInterval::on_pushButton_lampForbidList_clicked()
{
    CGlobal::instance()->dlgDeviceForbidFault()->clearDeviceForbidFaultInfo();
    deviceForbidFault df;
    df.deviceForbidFile();//读取灯具禁用表
    CGlobal::instance()->dlgDeviceForbidFault()->exec();
}

void dlgTimeInterval::on_pushButton_lamptwinkleconfig_clicked()
{
    QFont font;
    font.setPointSize(12); // 设置字体大小为12像素
    // 在QMessageBox中设置字体
    QMessageBox messageBox;
    messageBox.setFont(font);
    QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
    messageBox.setStyleSheet(styleSheet);
    messageBox.setIcon(QMessageBox::NoIcon);
    messageBox.setWindowTitle("信息");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Cancel);
    // 设置按钮显示文字
    messageBox.button(QMessageBox::Yes)->setText("已确认");
    messageBox.button(QMessageBox::Cancel)->setText("取消");
    QString log;
    log = "本操作须联系厂家技术支持确认,未确认前请勿操作!!!";
    messageBox.setText(log);
    int ret = messageBox.exec();
    if(ret == QMessageBox::Yes)
    {
        // 在QMessageBox中设置字体
        QMessageBox messageBox;
        messageBox.setFont(font);
        QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
        messageBox.setStyleSheet(styleSheet);
        messageBox.setIcon(QMessageBox::NoIcon);
        messageBox.setWindowTitle("信息");
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        messageBox.setDefaultButton(QMessageBox::Cancel);
        // 设置按钮显示文字
        messageBox.button(QMessageBox::Yes)->setText("打开");
        messageBox.button(QMessageBox::No)->setText("关闭");
        messageBox.button(QMessageBox::Cancel)->setText("取消");
        QString log;
        log = "执行灯具闪烁配置(0x49)";
        messageBox.setText(log);
        int ret = messageBox.exec();
        CMsgObjectStatus msgObjectStatus;
        if(ret == QMessageBox::Yes)
        {
            //方向灯闪烁配置
            msgObjectStatus.nValue = 0x01;
            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_FlashConfig, &msgObjectStatus);
        }
        else if(ret == QMessageBox::No)
        {
            //方向灯闪烁配置
            msgObjectStatus.nValue = 0x00;
            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_FlashConfig, &msgObjectStatus);
        }
    }
}

void dlgTimeInterval::on_pushButton_firepointNumber_clicked()
{
    qDebug() << "dlgadminParamPage::on_pushButton_firepointNumber_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_startFirepointNumber = ui->lineEdit_firepointNumber->text().toInt();
    saveSqliteData("StartFirepointNumber", QString::number(CGlobal::instance()->m_startFirepointNumber));
}

void dlgTimeInterval::on_forbidARTUCheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_forbidARTUCheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_ARTUType = 0;
    saveSqliteData("ARTUType", QString::number(0));
    systemChanged();
}

void dlgTimeInterval::on_ARTU079KCheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_ARTU079KCheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_ARTUType = 1;
    saveSqliteData("ARTUType", QString::number(1));
    systemChanged();
}

void dlgTimeInterval::on_ARTU079KJCheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_ARTU079KJCheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_ARTUType = 2;
    saveSqliteData("ARTUType", QString::number(2));
    systemChanged();
}

void dlgTimeInterval::on_ARTU426CheckBox_clicked()
{
    qDebug() << "dlgTimeInterval::on_ARTU426CheckBox_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CGlobal::instance()->m_ARTUType = 3;
    saveSqliteData("ARTUType", QString::number(3));
    systemChanged();
}

//系统参数变化
void dlgTimeInterval::systemChanged()
{
    qDebug() << "dlgTimeInterval::systemChanged"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CMsgObjectStatus msgObjectStatus;
    msgObjectStatus.ndata.append(CGlobal::instance()->m_forbidFaultSound);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_forbidEmergencySound);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_forbidMonthcheck);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_forbidYearcheck);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_nCanNumber);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_MonthCheckSpanSecond);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_YearCheckSpanSecond);
    msgObjectStatus.ndata.append(CGlobal::instance()->m_ARTUType);

    CGlobal::instance()->ClientBusiness()->exeCommand(NCT_SystemSet, &msgObjectStatus);
}

//设置显示通讯地址端口号
void dlgTimeInterval::setHostAddressPort(QString ip, QString port)
{
    qDebug() << "dlgTimeInterval::setHostIpPort"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->m_hostAddress->setText(ip);
    ui->m_com->setText(port);
}


//设置显示使用天数
void dlgTimeInterval::setUseTime(int usetime)
{
    qDebug() << "dlgTimeInterval::setUseTime"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->UseTime->setText(QString::number(usetime));
}

//导出寄存器点表
void dlgTimeInterval::on_pushButton_ModbusTCP_clicked()
{
    qDebug() << "dlgTimeInterval::on_pushButton_ModbusTCP_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    QString total;
    QString title = "设备地址	功能码	寄存器16	说明";
    QString Totalhost = "1	04或10H	0000	主机状态与控制。"
                        "当使用功能码0x03读取时，bit0为1表示正在应急启动，bit1为1表示主电故障，bit2为1表示备电故障。"
                        "当使用功能码0x10写入时，写入1控制主机复位。写入2控制主机应急启动。";
    QString distributionData = "bit0为1表示通讯故障，bit1为1表示主电故障，bit2为1表示备电故障，bit3为1表示正在应急启动。";
    QString strDistribution = distributionData + "\n";
    QString deviceData = "bit0为1表示通讯故障，bit1为1表示光源故障，bit2为1表示电池故障，bit3为1表示正在应急启动。";
    QString strDevice = deviceData + "\n";
    total = title + "\n" + Totalhost + "\n";
    QString distributionMsg;
    QString deviceMsg;
    QString TotalDistribution;
    QString TotalDevice;
    for(int i=3; i<=CGlobal::instance()->m_nCanNumber+2; i++)
    {
        CCanport* canport = CGlobal::instance()->controller()->canportByAddress(i);
        if(canport){
            for(int j=1; j<=32; j++)
            {
                QApplication::processEvents();
                CDistribution* distribution = canport->distributionByAddress(j);
                if(distribution)
                {
                    uint16_t modbusDistributionAddress = (uint8_t(i-2)<<8) | (uint8_t(j));
                    QString strModbusDistributionAddress = QString::number(modbusDistributionAddress,16).rightJustified(4,'0').toUpper();
                    distributionMsg = QString("%1	04H	%2	集中电源(%3-%4)状态。")
                            .arg(QString::number(i-2)).arg(strModbusDistributionAddress)
                            .arg(QString::number(i-2)).arg(QString::number(j,10).rightJustified(3,'0').toUpper());
                    TotalDistribution = TotalDistribution + distributionMsg + strDistribution;
                    for(int l=1; l<=8; l++)
                    {
                        CLoop* loop = distribution->loopByAdd(l);
                        if(loop)
                        {
                            for(int m=1; m<=255; m++)
                            {
                                QApplication::processEvents();
                                CDevice* device = loop->deviceByAdd(m);
                                if(device)
                                {
                                    uint16_t modbusDeviceAddress = (uint8_t(8*(j-1) | l)<<8) | (uint8_t(m));
                                    QString strModbusDeviceAddress = QString::number(modbusDeviceAddress,16).rightJustified(4,'0').toUpper();
                                    deviceMsg = QString("%1	03H	%2	灯具(%3-%4-%5-%6)状态。")
                                            .arg(QString::number(i-2)).arg(strModbusDeviceAddress)
                                            .arg(QString::number(i-2)).arg(QString::number(j,10).rightJustified(3,'0').toUpper())
                                            .arg(QString::number(l,10).rightJustified(2,'0').toUpper())
                                            .arg(QString::number(m,10).rightJustified(3,'0').toUpper());
                                    TotalDevice = TotalDevice + deviceMsg + strDevice;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    total = total + TotalDistribution + TotalDevice;
    QFile file("/home/xfss/root/logfile/ModbusTcp.txt");
    if (!file.open(QIODevice::WriteOnly  | QIODevice::Truncate))
    {
        qDebug() << "Open File Failed!";
        return;
    }
    // 关闭文件
    file.close();
    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << total << '\n' << '\n';
        file.close();
    }
}

//设置显示连接设备通讯状态
void dlgTimeInterval::slot_setComStatus(bool enable)
{
    qDebug() << "dlgTimeInterval::setComStatus"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(enable)
        ui->m_comStatus->setText("已连接");
    else
        ui->m_comStatus->setText("未连接");
}

//设置MQTT服务器控制指令
void dlgTimeInterval::slot_setHostControlMsg(int type)
{
    if(type == 1) {   //复位
        CGlobal::instance()->TopToolBar()->resetSystem();
    } else if(type == 2) {   //应急
        CGlobal::instance()->m_isEmergency = true;
        CMsgNull m_MsgNUll;
        CGlobal::instance()->ClientBusiness()->exeCommand(NCT_CancelMute, &m_MsgNUll);
        CGlobal::instance()->DataProcessing()->setSoundIcon(true);
        if(CGlobal::instance()->m_EmergencyOperation == CGlobal::Start)
            return;
        CGlobal::instance()->m_EmergencyOperation = CGlobal::Start;
        CGlobal::instance()->ClientBusiness()->exeCommand(NCT_EmergencyStart, &m_MsgNUll);
        //上传设备状态到MQTT服务器
        uploadStatusToMqtt();
    }
}
//上传设备状态到MQTT服务器
void dlgTimeInterval::uploadStatusToMqtt()
{
    emit uploadStatusToMQTT();
}

bool dlgTimeInterval::isWLANChanged()
{
    qDebug() << "dlgTimeInterval::isWLANChanged"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(ui->m_myip1->text() != m_getTmpip1)
        return true;
    if(ui->m_gateway1->text() != m_getTmpgateway1)
        return true;
    if(ui->m_myip2->text() != m_getTmpip2)
        return true;
    if(ui->m_gateway2->text() != m_getTmpgateway2)
        return true;
    return false;
}


bool dlgTimeInterval::isHostAddressChanged()
{
    qDebug() << "dlgTimeInterval::isHostAddressChanged"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(ui->m_hostAddress->text() != CGlobal::instance()->m_mqttHost)
        return true;
    if(ui->m_com->text() != QString::number(CGlobal::instance()->m_mqttCom))
        return true;
    return false;
}

//更新高级参数按钮位置
void dlgTimeInterval::updateAdminPuttonGeometry()
{
    qDebug() << "dlgTimeInterval::updateAdminPuttonGeometry"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(CGlobal::instance()->DataProcessing()->isStatusTab())
        m_triangleButton->setGeometry(1320,450,32,32);
    else
        m_triangleButton->setGeometry(1320,610,32,32);
}

//更新中间层软件版本
void dlgTimeInterval::updateVersion()
{
    qDebug() << "dlgTimeInterval::updateVersion"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    ui->version_ledkey->setText(CGlobal::instance()->m_version_ledkey);
    ui->version_can1can2->setText(CGlobal::instance()->m_version_can1can2);
    ui->version_can3can4->setText(CGlobal::instance()->m_version_can3can4);
    ui->version_can5can6->setText(CGlobal::instance()->m_version_can5can6);
    ui->version_can7can8->setText(CGlobal::instance()->m_version_can7can8);
}

//更新数据库系统参数数据
void dlgTimeInterval::updateSqliteData()
{
    qDebug() << "dlgTimeInterval::updateSqliteData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(CGlobal::instance()->m_lampEmergencyType == 0)
        ui->DirectionTwinkleOneCheckBox->setChecked(true);
    else
    {
        if(CGlobal::instance()->m_lampEmergencyType & 0x01)
            ui->DirectionTwinkleDoubleCheckBox->setChecked(true);
        if(CGlobal::instance()->m_lampEmergencyType & 0x02)
            ui->TwinkleConfigCheckBox->setChecked(true);
    }
    ui->TwinkleCheckBox->setChecked(CGlobal::instance()->m_TwinkleControl);
    ui->emergencyOnlyDistributionCheckBox->setChecked(CGlobal::instance()->m_emergencyOnlyDistribution);
    ui->lineEdit_phoneNumber->setText(CGlobal::instance()->m_LinkmanPhoneNumer);
    ui->lineEdit_firepointNumber->setText(QString::number(CGlobal::instance()->m_startFirepointNumber));
    if(CGlobal::instance()->m_nCanNumber == 4)
    {
        ui->Can4CheckBox->setChecked(true);
        ui->label_CAN5_6->hide();
        ui->version_can5can6->hide();
        ui->pushButton_can5can6->hide();
        ui->label_CAN7_8->hide();
        ui->version_can7can8->hide();
        ui->pushButton_can7can8->hide();
        ui->VersionBox->setFixedHeight(140);
    }
    else if(CGlobal::instance()->m_nCanNumber == 8)
    {
        ui->Can8CheckBox->setChecked(true);
    }

    if(CGlobal::instance()->m_isDoubleWLAN)
    {
        ui->doubleWLAN->setChecked(true);
    }
    else
    {
        ui->singleWLAN->setChecked(true);
    }

    if(CGlobal::instance()->m_ARTUType == 0)
    {
        ui->forbidARTUCheckBox->setChecked(true);
    }
    else if(CGlobal::instance()->m_ARTUType == 1)
    {
        ui->ARTU079KCheckBox->setChecked(true);
    }
    else if(CGlobal::instance()->m_ARTUType == 2)
    {
        ui->ARTU079KJCheckBox->setChecked(true);
    }
    else if(CGlobal::instance()->m_ARTUType == 3)
    {
        ui->ARTU426CheckBox->setChecked(true);
    }

    int index = ui->comboBox_testLinkageCom->findText(CGlobal::instance()->m_baudRate);
    ui->comboBox_testLinkageCom->setCurrentIndex(index);
    if(CGlobal::instance()->m_LiftTime > 1000)
        ui->UseTime->setText("永久");
    else
        ui->UseTime->setText(QString::number(CGlobal::instance()->m_LiftTime));

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
    ui->timeEdit->setCalendarPopup(true);
    ui->timeEdit->setDateTime(QDateTime::currentDateTime());

    ui->m_hostAddress->setText(CGlobal::instance()->m_mqttHost);
    ui->m_com->setText(QString::number(CGlobal::instance()->m_mqttCom));
    m_processMqtt->manualConnectToBroker(CGlobal::instance()->m_mqttHost, CGlobal::instance()->m_mqttCom);
    m_processNtp->startNtpTimer();
}
//更新WLAN地址相关信息
void dlgTimeInterval::updateWLANData()
{
    qDebug() << "dlgTimeInterval::updateWLANData"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(CGlobal::instance()->m_isDoubleWLAN)
    {
        // 创建一个QProcess对象
        QProcess process;

        // 设置要执行的命令和参数
        QStringList args;
        args << "-a";  // ifconfig -a 命令的参数

        // 启动ifconfig -a命令
        process.start("ifconfig", args);

        // 等待进程完成
        if (process.waitForFinished())
        {
            // 读取命令输出
            QString  output = process.readAllStandardOutput();
            // Split the output into lines and filter for 'enpXs0' pattern
            QStringList lines = output.split("\n", QString::SkipEmptyParts); // Skip empty lines
            QStringList filteredOutput;
            foreach (const QString &line, lines)
            {
                if (line.contains(QRegExp("\\b(enp[2-9]*s0)\\b"))) {
                    filteredOutput.append(line.trimmed());
                }
            }
            if(filteredOutput.count() > 0)
            {
                // Remove leading and trailing spaces
                QString input = filteredOutput.at(0);

                // Find the position of the first space
                int space_pos = input.indexOf(' ');

                // Remove everything from the first space onwards
                QString str;
                if (space_pos != -1) {
                   str = input.left(space_pos);
                } else {
                   str = input; // If no space found, keep the original string
                }
                CGlobal::instance()->m_wlanName = str;
            }
        }
    }

    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface interface, interfaces) {
        if (!interface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            QString interfaceName = interface.name();
            foreach (QNetworkAddressEntry entry, entries) {
                if (entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    qDebug() << "IPv4 Address:" << entry.ip().toString();
                    if(interfaceName == "enp1s0")
                    {
                        m_getTmpip1 = entry.ip().toString();
                        ui->m_myip1->setText(m_getTmpip1);
                    }
                    else if(interfaceName == CGlobal::instance()->m_wlanName)
                    {
                        m_getTmpip2 = entry.ip().toString();
                        ui->m_myip2->setText(m_getTmpip2);
                    }
                }
            }
        }
    }

    // 获取 enp1s0 接口的网关
    m_getTmpgateway1 = getGateway("enp1s0");
    // 获取 enp4s0 接口的网关
    m_getTmpgateway2 = getGateway(CGlobal::instance()->m_wlanName);
    if(m_getTmpgateway1 != "" || m_getTmpgateway2 != "")
    {
        if(m_getTmpgateway1 != "" && m_getTmpgateway2 != "")
        {
            ui->m_gateway1->setText(m_getTmpgateway1);
            ui->m_gateway2->setText(m_getTmpgateway2);
            ui->wlanBox->setFixedHeight(210);
            ui->pingBox->move(40, 370);
        }
        else if(m_getTmpgateway1 != "")
        {
            ui->m_gateway1->setText(m_getTmpgateway1);
            ui->m_gateway2->hide();
            ui->label_gateway2->hide();
            ui->wlanBox->setFixedHeight(180);
            ui->pingBox->move(40, 340);
        }
        else if(m_getTmpgateway2 != "")
        {
            ui->m_gateway2->setText(m_getTmpgateway2);
            ui->m_gateway1->hide();
            ui->label_gateway1->hide();
            ui->wlanBox->setFixedHeight(180);
            ui->pingBox->move(40, 340);
        }
    }
    else
    {
        ui->m_gateway2->hide();
        ui->label_gateway2->hide();
        ui->wlanBox->setFixedHeight(180);
        ui->pingBox->move(40, 340);
    }
    if(!CGlobal::instance()->m_isDoubleWLAN)
    {
        ui->m_myip2->hide();
        ui->label_myip2->hide();
        ui->m_gateway2->hide();
        ui->label_gateway2->hide();
        ui->wlanBox->setFixedHeight(150);
        ui->pingBox->move(40, 310);
    }
}
//获取主机网关
QString dlgTimeInterval::getGateway(const QString &interfaceName)
{
    qDebug() << "dlgTimeInterval::getGateway"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
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


//设置ip和时间以及ping测试是否可见
void dlgTimeInterval::setIpAndTimeHide(bool enable)
{
    qDebug() << "dlgTimeInterval::setIpAndTimeHide"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    if(enable)
    {
        ui->wlanBox->hide();
        ui->hostAddressSetBox->hide();
        ui->timeBox->hide();
        ui->pingBox->hide();
    }
    else
    {
        ui->wlanBox->show();
        ui->hostAddressSetBox->show();
        ui->timeBox->show();
        ui->pingBox->show();
    }
}

