#include "cglobal.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_iDelayCut = 0;
    CGlobal::instance()->m_widget = this;
    CGlobal::instance()->m_checkLabel = new QLabel;
    CGlobal::instance()->m_checkLabel->setWindowFlags(Qt::WindowStaysOnTopHint);
    QFont ft;
    ft.setPointSize(50);
    CGlobal::instance()->m_checkLabel->setFont(ft);
    CGlobal::instance()->m_checkLabel->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    CGlobal::instance()->m_checkLabel->setText(QString("<font color=white>%1</font>").arg("正在加载......"));
    CGlobal::instance()->m_checkLabel->setStyleSheet("background-color:black");
    CGlobal::instance()->m_checkLabel->setGeometry(0,0,1366,768);
    CGlobal::instance()->m_checkLabel->showFullScreen();

    CGlobal::instance()->setLoginInformation(new dlgLoginInformation());
    CGlobal::instance()->loginInformation()->setWindowTitle(tr("The registered device information"));
    CGlobal::instance()->loginInformation()->hide();
    CGlobal::instance()->setStatusTabs(new CStatusTabs());
    CGlobal::instance()->setClientBusiness(new CClientBusiness);
    CGlobal::instance()->setInformationWindow(new dlgInformationWindow);
    CGlobal::instance()->setDataProcessing(new CDataProcessing());
    CGlobal::instance()->setCenterFrameContainer(new QStackedWidget);
    CGlobal::instance()->setCenterFrame(new CCenterFrame);
    CGlobal::instance()->setSystemRecord(new dlgSystemRecord);
    CGlobal::instance()->setProgramCanDeviceView(new CProgramCanDeviceView);
    CGlobal::instance()->setDlgDevices(new dlgDevices);
    CGlobal::instance()->setDeviceForbidFault(new dlgdeviceForbidFault);
    CGlobal::instance()->setTimeInterval(new dlgTimeInterval);
    CGlobal::instance()->setAdminParamPage(new dlgadminParamPage);
    CGlobal::instance()->setUseTime(new dlgUseTime);
    CGlobal::instance()->setProcessModbusTcp(new CprocessModbusTcp);
    CGlobal::instance()->centerFrameContainer()->insertWidget(0, CGlobal::instance()->CenterFrame());
    CGlobal::instance()->centerFrameContainer()->setCurrentIndex(0);
    CGlobal::instance()->setBottomToolBar(new CBottomToolBar);
    CGlobal::instance()->setTopToolBar(new CTopToolBar);

    CGlobal::instance()->ClientBusiness()->InitController();
    CGlobal::instance()->ClientBusiness()->startCommunication();
    CGlobal::instance()->ClientBusiness()->setNewPwd(CGlobal::instance()->m_strPassWord);

    topBox = new QDialog;
    topBox->setMaximumHeight(75);
    topBox->setMinimumHeight(75);
    topLayout = new QHBoxLayout;
    topLayout->setContentsMargins(1, 1, 1, 1);
    topLayout->addWidget(CGlobal::instance()->TopToolBar());
    topBox->setLayout(topLayout);

    bottomBox = new QDialog;
    bottomBox->setMaximumHeight(30);
    bottomBox->setMinimumHeight(30);
    bottomLayout = new QHBoxLayout;
    bottomLayout->setContentsMargins(1, 1, 1, 1);
    bottomLayout->addWidget(CGlobal::instance()->BottomToolBar());
    bottomBox->setLayout(bottomLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(topBox);
    mainLayout->addWidget(CGlobal::instance()->centerFrameContainer(),1);
    mainLayout->addWidget(CGlobal::instance()->statusTabs()->m_tabWidget);
    mainLayout->addWidget(bottomBox);
    createTimer();
    setGeometry(0,0,QApplication::desktop()->screen()->width(), QApplication::desktop()->screen()->height());
//    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint); // ??????
    this->hide();
}

Widget::~Widget()
{
    delete CGlobal::instance()->InformationWindow();
    CGlobal::instance()->setClientBusiness(NULL);
    CGlobal::instance()->m_widget = NULL;
    CGlobal::destroy();
}

void Widget::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void Widget::createTimer()
{
    m_timerLED = new QTimer(this);
    connect(m_timerLED, SIGNAL(timeout()), this, SLOT(slotLEDTimer()));
    m_timerLED->start(500);
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_F)
    {
        CGlobal::instance()->TopToolBar()->slotSearchDevice();
    }
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_L)
    {
        if(CGlobal::instance()->SystemRecord() == NULL)
        {
            CGlobal::instance()->setSystemRecord(new dlgSystemRecord(this));
            CGlobal::instance()->SystemRecord()->exec();
        }
    }
}


void Widget::slotLEDTimer()
{
    CGlobal::instance()->BottomToolBar()->setCurrentDateTime();
    if(CGlobal::instance()->m_HaveDialog)
    {
        CGlobal::instance()->m_bMove_Mouse = true;
    }
    if(CGlobal::instance()->m_bCutLayer != CGlobal::instance()->isAutoSwitchLayer())
    {
        CGlobal::instance()->m_bCutLayer = CGlobal::instance()->isAutoSwitchLayer();
    }
    if(!CGlobal::instance()->m_bMove_Mouse) {
        ++m_iDelayCut;
//        exitAdmin();
//        switchLayer();
    } else {
        m_iDelayCut = 0;
    }
    CGlobal::instance()->m_bMove_Mouse = false;
}


void Widget::switchLayer()
{
    if(m_iDelayCut > 2*CGlobal::instance()->m_nTimeCutLayer)
    {
        m_iDelayCut = 0;
        if(CGlobal::instance()->m_bCutLayer)
        {
            static int m_nLayerNum = -1;
            QList<CLayer*> tempLayer = CGlobal::instance()->getLayers(CGlobal::instance()->dm()->controllers());

            if(tempLayer.count()>0)
            {
                ++m_nLayerNum;

                if(m_nLayerNum >= tempLayer.count())
                {
                    m_nLayerNum = 0;
                }

                for(int i=0; i<tempLayer.count(); ++i)
                {
                    if(tempLayer.at(m_nLayerNum)->getStatus(OBJS_Fire))
                    {
                        if(CGlobal::instance()->designTreeView()->currentLayer() != tempLayer.at(m_nLayerNum))
                        {
                            CGlobal::instance()->setLayer(tempLayer.at(m_nLayerNum));
                        }
                        return;
                    }

                    ++m_nLayerNum;
                    if(m_nLayerNum >= tempLayer.count())
                    {
                        m_nLayerNum = 0;
                    }
                }
                m_nLayerNum = normalSwitch(tempLayer, m_nLayerNum);
            }
        }
    }
}
void Widget::slotEventChange()
{
    CGlobal::instance()->m_bMove_Mouse = true;

}

int Widget::normalSwitch(QList<CLayer*> &listLayer, int num)
{
    CLayer* m_Lay = CGlobal::instance()->designTreeView()->currentLayer();//?????????
    if(m_Lay)
    {
        int layNum = listLayer.indexOf(m_Lay);
        if(layNum >= 0)
        {
            num = layNum + 1;
            if(num >= listLayer.count())
            {
                num = 0;
            }
        }
    }
    CGlobal::instance()->setLayer(listLayer.at(num));
    return num;
}


