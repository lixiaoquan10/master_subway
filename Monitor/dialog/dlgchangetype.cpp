#include "ui_dlgchangetype.h"
#include "dlgchangetype.h"
#include "cglobal.h"

dlgChangeType::dlgChangeType(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgChangeType)
{
    int count = 0;
    ui->setupUi(this);
    QString styleSheet =
            "QScrollBar:vertical {"
            "    border: 1px solid #999999;"
            "    background: #f0f0f0;"
            "    width: 20px; /* 设置滚动条的宽度 */"
            "    margin: 0px 0px 0px 0px;"
            "}"
            "QScrollBar::handle:vertical {"
            "    background: #666666;"
            "    min-height: 20px; /* 设置滚动条手柄的最小高度 */"
            "}"
            "QScrollBar::add-line:vertical {"
            "    border: 1px solid #999999;"
            "    background: #e0e0e0; /* 按钮的背景颜色 */"
            "    height: 20px; /* 按钮的高度 */"
            "    subcontrol-position: bottom;"
            "    subcontrol-origin: margin;"
            "}"
            "QScrollBar::sub-line:vertical {"
            "    border: 1px solid #999999;"
            "    background: #e0e0e0; /* 按钮的背景颜色 */"
            "    height: 20px; /* 按钮的高度 */"
            "    subcontrol-position: top;"
            "    subcontrol-origin: margin;"
            "}";
    ui->comboBox->view()->verticalScrollBar()->setStyleSheet(styleSheet);
    m_device = CGlobal::instance()->programDeviceView()->getDevice();
    if(!m_device)
        return;
    CDeviceType* devType;
    for (int i=0; i<256; ++i)
    {
        devType = CGlobal::instance()->deviceType(i);
        if(devType)
        {
            int lampType = devType->type();
            int deviceTypeId = m_device->deviceValue(DEVICE_VALUE_LOGINTYPE_ID).toInt();
            if(deviceTypeId == 119 && (lampType < 115 || (lampType > 119 && lampType < 140) || lampType > 147))
                continue;
            if(deviceTypeId == 124 && (lampType < 122 || lampType > 124))
                continue;
            if(deviceTypeId == 19 && (lampType < 15 || (lampType > 19 && lampType < 40) || lampType > 47))
                continue;
            if(!m_device->isMAtype())
            {
                if((lampType >= 15 && lampType <= 19) || (lampType >= 40 && lampType <= 47)
                        || lampType == 79 || (lampType >= 115 && lampType <= 119) || (lampType >= 122 && lampType <= 124)
                        || (lampType >= 140 && lampType <= 147) || lampType == 179)
                    continue;
            }

            ui->comboBox->addItem(devType->name());
            if(lampType == deviceTypeId)
                ui->comboBox->setCurrentIndex(count);
            count++;
        }
    }
}

dlgChangeType::~dlgChangeType()
{
    delete ui;
}

void dlgChangeType::on_pushButton_clicked()
{
    qDebug() << "dlgChangeType::on_pushButton_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    CMsgObjectStatus msgobjectstatus;
    if(!m_device)
        return;
    msgobjectstatus.nCanportAdd = m_device->canportAdd();
    msgobjectstatus.nDisID = m_device->distributionAdd();
    msgobjectstatus.nLoopID = m_device->loopAdd();
    msgobjectstatus.nDeviceID = m_device->deviceAdd();
    msgobjectstatus.nType = m_device->deviceValue(DEVICE_VALUE_LOGINTYPE_ID).toInt();
    CDeviceType* devType;
    for (int i=0; i<255; ++i)
    {
        devType = CGlobal::instance()->deviceType(i);
        if(devType)
        {
            if(devType->name() == ui->comboBox->currentText())
                msgobjectstatus.nValue = devType->type();
        }
    }
    if(msgobjectstatus.nType != msgobjectstatus.nValue)
    {
//        m_device->setDeviceValue(DEVICE_VALUE_TYPE_ID,msgobjectstatus.nValue);
        //更新列表视图
//        CGlobal::instance()->DlgDevices()->getDeviceInfo();
        if(msgobjectstatus.nType == 119 || m_device->deviceTypeId() == 124 || m_device->deviceTypeId() == 19)
        {
            QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(fileName);
            if(!db.open())
                return;
            QSqlQuery queryTypeId(db);
            queryTypeId.prepare(QString("SELECT ID,number from lamptype where number=%1"
                                                ).arg(msgobjectstatus.nValue));
            if (!queryTypeId.exec())
            {
                qDebug() << "queryTypeId Error:" << queryTypeId.lastError().text();
                return;
            }
            QSqlRecord record = queryTypeId.record();
            int lampTypeId;
            while(queryTypeId.next())
            {
                lampTypeId = queryTypeId.value(record.indexOf("ID")).toInt();
            }
            // 绑定参数
            QSqlQuery query(db);
            query.prepare("UPDATE LampInfo SET LampTypeID=:LampTypeID WHERE ID=:id");
            query.bindValue(":LampTypeID", lampTypeId);
            query.bindValue(":id", CGlobal::instance()->saveKeyId(OBJT_Device,m_device->keyId()));
            // 执行 SQL 语句
            query.exec();
            db.close();
        }
        else
        {
            m_device->setDeviceValue(DEVICE_VALUE_CHANGETYPE,1);
            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_DeviceType, &msgobjectstatus);

            QString fileName = CGlobal::instance()->workspaces() + "/" + "ESSQLiteCE100.db";
            QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");;
            db.setDatabaseName(fileName);
            if(!db.open())
                return;
            QSqlQuery query(db);

            int id = CGlobal::instance()->saveKeyId(OBJT_Device,m_device->keyId());
            query.exec(QString("DELETE FROM EvacuationPathItem WHERE LampInfoID=%1").arg(id));
            query.exec(QString("DELETE FROM LampConnection WHERE StartLampID=%1").arg(id));
            query.exec(QString("DELETE FROM LampConnection WHERE EndLampID=%1").arg(id));
            query.exec(QString("DELETE FROM LampDefaultDirection WHERE LampInfoID=%1").arg(id));
            query.exec(QString("DELETE FROM LampToFirePoint WHERE LampInfoID=%1").arg(id));
            query.exec(QString("DELETE FROM LampToLaunchGroup WHERE LampInfoID=%1").arg(id));
            if(!query.exec())
            {
                qDebug() << query.lastError();
            }
            db.close();
        }
        QFont font;
        font.setPointSize(12); // 设置字体大小为12像素
        // 在QMessageBox中设置字体
        QMessageBox messageBox;
        messageBox.setFont(font);
        QString styleSheet = "QMessageBox { border: 1px solid #333333; }";
        messageBox.setStyleSheet(styleSheet);
        messageBox.setIcon(QMessageBox::NoIcon);
        messageBox.setWindowTitle("信息");
        messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        messageBox.setDefaultButton(QMessageBox::No);
        messageBox.button(QMessageBox::Yes)->setText("是");
        messageBox.button(QMessageBox::No)->setText("否");
        QString log;
        log = "是否清除注册并重新注册?";
        messageBox.setText(log);
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes)
        {
            //获取当前点击的回路地址
            CMsgObjectStatus msg;
            msg.nDisID = CGlobal::instance()->m_nDistriAddress;
            msg.nLoopID = CGlobal::instance()->m_nLoopAddress;
            msg.nCanportAdd = CGlobal::instance()->m_nCanportAddress;
            //清除注册
            CGlobal::instance()->ClientBusiness()->removeLoginObject(CGlobal::instance()->m_nCanportAddress,CGlobal::instance()->m_nDistriAddress,
                                                                     CGlobal::instance()->m_nLoopAddress);
            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_UnLoginLoop, &msg);
            //重新注册
            CGlobal::instance()->ClientBusiness()->exeCommand(NCT_LoginInfoLoop, &msg);
        }
    }
    this->close();
}

void dlgChangeType::on_pushButton_cancel_clicked()
{
    qDebug() << "dlgChangeType::on_pushButton_cancel_clicked"
             << QDateTime::currentDateTime().toString("HH:mm:ss:zzz");
    this->close();
}
