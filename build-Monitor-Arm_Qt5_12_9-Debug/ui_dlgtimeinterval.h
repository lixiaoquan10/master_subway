/********************************************************************************
** Form generated from reading UI file 'dlgtimeinterval.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGTIMEINTERVAL_H
#define UI_DLGTIMEINTERVAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgTimeInterval
{
public:
    QGroupBox *EnergyModeBox;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *EnergyCheckBox;
    QGroupBox *EmergencyBox;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *TwinkleCheckBox;
    QCheckBox *emergencyOnlyDistributionCheckBox;
    QGroupBox *VersionBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_10;
    QLineEdit *version_ledkey;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_CAN1_2;
    QLineEdit *version_can1can2;
    QPushButton *pushButton_can1can2;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_CAN3_4;
    QLineEdit *version_can3can4;
    QPushButton *pushButton_can3can4;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_CAN5_6;
    QLineEdit *version_can5can6;
    QPushButton *pushButton_can5can6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_CAN7_8;
    QLineEdit *version_can7can8;
    QPushButton *pushButton_can7can8;
    QGroupBox *wlanBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_myip1;
    QLineEdit *m_myip1;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_gateway1;
    QLineEdit *m_gateway1;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_myip2;
    QLineEdit *m_myip2;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_gateway2;
    QLineEdit *m_gateway2;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_saveWlan;
    QGroupBox *UseTimeBox;
    QHBoxLayout *horizontalLayout_14;
    QLineEdit *UseTime;
    QLabel *label_3;
    QPushButton *pushButton_UseTime;
    QGroupBox *timeBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QDateTimeEdit *dateEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QDateTimeEdit *timeEdit;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_ButtonTimeSet;
    QGroupBox *pingBox;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QLineEdit *m_pingIP;
    QPushButton *pingButton;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QLineEdit *m_pingResult;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *hostAddressSetBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_HostAddress;
    QLineEdit *m_hostAddress;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_com;
    QLineEdit *m_com;
    QPushButton *pushButton_saveHostAddress;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_comStatus;
    QLineEdit *m_comStatus;
    QGroupBox *StartRuleBox;
    QVBoxLayout *verticalLayout_15;
    QCheckBox *allStartCheckBox;
    QCheckBox *onlyStartGroupCheckBox;
    QCheckBox *onlyStartPageCheckBox;
    QGroupBox *CanNumberBox;
    QVBoxLayout *verticalLayout_16;
    QCheckBox *Can4CheckBox;
    QCheckBox *Can8CheckBox;
    QGroupBox *controlType;
    QVBoxLayout *verticalLayout_17;
    QCheckBox *singleWLAN;
    QCheckBox *doubleWLAN;
    QGroupBox *AutoPageBox;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *autoPageCheckBox;
    QGroupBox *testLinkageComBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QComboBox *comboBox_testLinkageCom;
    QPushButton *pushButton_testLinkageCom;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_9;
    QLineEdit *m_testLinkageComResult;
    QPushButton *testLinkageComButton;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_15;
    QLineEdit *m_linkageStatus;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_phoneNumber;
    QHBoxLayout *horizontalLayout_26;
    QLineEdit *lineEdit_phoneNumber;
    QPushButton *pushButton_phoneNumber;
    QGroupBox *groupBox_firepointNumber;
    QHBoxLayout *horizontalLayout_27;
    QLineEdit *lineEdit_firepointNumber;
    QPushButton *pushButton_firepointNumber;
    QPushButton *pushButton_lampForbidList;
    QGroupBox *lampEmergencyType;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *DirectionTwinkleOneCheckBox;
    QCheckBox *DirectionTwinkleDoubleCheckBox;
    QCheckBox *TwinkleConfigCheckBox;
    QPushButton *pushButton_lamptwinkleconfig;
    QGroupBox *ARTUBox;
    QVBoxLayout *verticalLayout_18;
    QCheckBox *forbidARTUCheckBox;
    QCheckBox *ARTU079KCheckBox;
    QCheckBox *ARTU079KJCheckBox;
    QCheckBox *ARTU426CheckBox;
    QGroupBox *groupBox_ModbusTCP;
    QPushButton *pushButton_ModbusTCP;

    void setupUi(QDialog *dlgTimeInterval)
    {
        if (dlgTimeInterval->objectName().isEmpty())
            dlgTimeInterval->setObjectName(QString::fromUtf8("dlgTimeInterval"));
        dlgTimeInterval->resize(1366, 768);
        dlgTimeInterval->setMinimumSize(QSize(1366, 768));
        dlgTimeInterval->setMaximumSize(QSize(1366, 768));
        QFont font;
        font.setPointSize(13);
        dlgTimeInterval->setFont(font);
        dlgTimeInterval->setInputMethodHints(Qt::ImhNone);
        EnergyModeBox = new QGroupBox(dlgTimeInterval);
        EnergyModeBox->setObjectName(QString::fromUtf8("EnergyModeBox"));
        EnergyModeBox->setGeometry(QRect(1210, 20, 110, 65));
        QFont font1;
        font1.setPointSize(12);
        EnergyModeBox->setFont(font1);
        EnergyModeBox->setCheckable(false);
        EnergyModeBox->setChecked(false);
        verticalLayout_6 = new QVBoxLayout(EnergyModeBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        EnergyCheckBox = new QCheckBox(EnergyModeBox);
        EnergyCheckBox->setObjectName(QString::fromUtf8("EnergyCheckBox"));
        EnergyCheckBox->setFont(font1);

        verticalLayout_6->addWidget(EnergyCheckBox);

        EmergencyBox = new QGroupBox(dlgTimeInterval);
        EmergencyBox->setObjectName(QString::fromUtf8("EmergencyBox"));
        EmergencyBox->setGeometry(QRect(490, 20, 270, 85));
        EmergencyBox->setFont(font1);
        EmergencyBox->setCheckable(false);
        EmergencyBox->setChecked(false);
        verticalLayout_12 = new QVBoxLayout(EmergencyBox);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        TwinkleCheckBox = new QCheckBox(EmergencyBox);
        TwinkleCheckBox->setObjectName(QString::fromUtf8("TwinkleCheckBox"));
        TwinkleCheckBox->setFont(font1);

        verticalLayout_12->addWidget(TwinkleCheckBox);

        emergencyOnlyDistributionCheckBox = new QCheckBox(EmergencyBox);
        emergencyOnlyDistributionCheckBox->setObjectName(QString::fromUtf8("emergencyOnlyDistributionCheckBox"));
        emergencyOnlyDistributionCheckBox->setFont(font1);

        verticalLayout_12->addWidget(emergencyOnlyDistributionCheckBox);

        VersionBox = new QGroupBox(dlgTimeInterval);
        VersionBox->setObjectName(QString::fromUtf8("VersionBox"));
        VersionBox->setGeometry(QRect(1050, 140, 270, 210));
        VersionBox->setFont(font1);
        VersionBox->setCheckable(false);
        VersionBox->setChecked(false);
        verticalLayout = new QVBoxLayout(VersionBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_10 = new QLabel(VersionBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(65, 28));
        label_10->setMaximumSize(QSize(65, 28));
        label_10->setFont(font1);

        horizontalLayout_22->addWidget(label_10);

        version_ledkey = new QLineEdit(VersionBox);
        version_ledkey->setObjectName(QString::fromUtf8("version_ledkey"));
        version_ledkey->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(version_ledkey->sizePolicy().hasHeightForWidth());
        version_ledkey->setSizePolicy(sizePolicy);
        version_ledkey->setMinimumSize(QSize(110, 28));
        version_ledkey->setMaximumSize(QSize(110, 28));
        version_ledkey->setFont(font1);
        version_ledkey->setReadOnly(true);

        horizontalLayout_22->addWidget(version_ledkey);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_CAN1_2 = new QLabel(VersionBox);
        label_CAN1_2->setObjectName(QString::fromUtf8("label_CAN1_2"));
        label_CAN1_2->setMinimumSize(QSize(65, 28));
        label_CAN1_2->setMaximumSize(QSize(65, 28));
        label_CAN1_2->setFont(font1);

        horizontalLayout_21->addWidget(label_CAN1_2);

        version_can1can2 = new QLineEdit(VersionBox);
        version_can1can2->setObjectName(QString::fromUtf8("version_can1can2"));
        version_can1can2->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can1can2->sizePolicy().hasHeightForWidth());
        version_can1can2->setSizePolicy(sizePolicy);
        version_can1can2->setMinimumSize(QSize(110, 28));
        version_can1can2->setMaximumSize(QSize(110, 28));
        version_can1can2->setFont(font1);
        version_can1can2->setReadOnly(true);

        horizontalLayout_21->addWidget(version_can1can2);

        pushButton_can1can2 = new QPushButton(VersionBox);
        pushButton_can1can2->setObjectName(QString::fromUtf8("pushButton_can1can2"));
        pushButton_can1can2->setMinimumSize(QSize(0, 28));
        pushButton_can1can2->setMaximumSize(QSize(60, 28));
        pushButton_can1can2->setFont(font1);

        horizontalLayout_21->addWidget(pushButton_can1can2);


        verticalLayout->addLayout(horizontalLayout_21);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_CAN3_4 = new QLabel(VersionBox);
        label_CAN3_4->setObjectName(QString::fromUtf8("label_CAN3_4"));
        label_CAN3_4->setMinimumSize(QSize(65, 28));
        label_CAN3_4->setMaximumSize(QSize(65, 28));
        label_CAN3_4->setFont(font1);

        horizontalLayout_20->addWidget(label_CAN3_4);

        version_can3can4 = new QLineEdit(VersionBox);
        version_can3can4->setObjectName(QString::fromUtf8("version_can3can4"));
        version_can3can4->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can3can4->sizePolicy().hasHeightForWidth());
        version_can3can4->setSizePolicy(sizePolicy);
        version_can3can4->setMinimumSize(QSize(110, 28));
        version_can3can4->setMaximumSize(QSize(110, 28));
        version_can3can4->setFont(font1);
        version_can3can4->setReadOnly(true);

        horizontalLayout_20->addWidget(version_can3can4);

        pushButton_can3can4 = new QPushButton(VersionBox);
        pushButton_can3can4->setObjectName(QString::fromUtf8("pushButton_can3can4"));
        pushButton_can3can4->setMinimumSize(QSize(0, 28));
        pushButton_can3can4->setMaximumSize(QSize(60, 28));
        pushButton_can3can4->setFont(font1);

        horizontalLayout_20->addWidget(pushButton_can3can4);


        verticalLayout->addLayout(horizontalLayout_20);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_CAN5_6 = new QLabel(VersionBox);
        label_CAN5_6->setObjectName(QString::fromUtf8("label_CAN5_6"));
        label_CAN5_6->setMinimumSize(QSize(65, 28));
        label_CAN5_6->setMaximumSize(QSize(65, 28));
        label_CAN5_6->setFont(font1);

        horizontalLayout_19->addWidget(label_CAN5_6);

        version_can5can6 = new QLineEdit(VersionBox);
        version_can5can6->setObjectName(QString::fromUtf8("version_can5can6"));
        version_can5can6->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can5can6->sizePolicy().hasHeightForWidth());
        version_can5can6->setSizePolicy(sizePolicy);
        version_can5can6->setMinimumSize(QSize(110, 28));
        version_can5can6->setMaximumSize(QSize(110, 28));
        version_can5can6->setFont(font1);
        version_can5can6->setReadOnly(true);

        horizontalLayout_19->addWidget(version_can5can6);

        pushButton_can5can6 = new QPushButton(VersionBox);
        pushButton_can5can6->setObjectName(QString::fromUtf8("pushButton_can5can6"));
        pushButton_can5can6->setMinimumSize(QSize(0, 28));
        pushButton_can5can6->setMaximumSize(QSize(60, 28));
        pushButton_can5can6->setFont(font1);

        horizontalLayout_19->addWidget(pushButton_can5can6);


        verticalLayout->addLayout(horizontalLayout_19);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_CAN7_8 = new QLabel(VersionBox);
        label_CAN7_8->setObjectName(QString::fromUtf8("label_CAN7_8"));
        label_CAN7_8->setMinimumSize(QSize(65, 28));
        label_CAN7_8->setMaximumSize(QSize(65, 28));
        label_CAN7_8->setFont(font1);

        horizontalLayout_13->addWidget(label_CAN7_8);

        version_can7can8 = new QLineEdit(VersionBox);
        version_can7can8->setObjectName(QString::fromUtf8("version_can7can8"));
        version_can7can8->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can7can8->sizePolicy().hasHeightForWidth());
        version_can7can8->setSizePolicy(sizePolicy);
        version_can7can8->setMinimumSize(QSize(110, 28));
        version_can7can8->setMaximumSize(QSize(110, 28));
        version_can7can8->setFont(font1);
        version_can7can8->setReadOnly(true);

        horizontalLayout_13->addWidget(version_can7can8);

        pushButton_can7can8 = new QPushButton(VersionBox);
        pushButton_can7can8->setObjectName(QString::fromUtf8("pushButton_can7can8"));
        pushButton_can7can8->setMinimumSize(QSize(0, 28));
        pushButton_can7can8->setMaximumSize(QSize(60, 28));
        pushButton_can7can8->setFont(font1);

        horizontalLayout_13->addWidget(pushButton_can7can8);


        verticalLayout->addLayout(horizontalLayout_13);

        wlanBox = new QGroupBox(dlgTimeInterval);
        wlanBox->setObjectName(QString::fromUtf8("wlanBox"));
        wlanBox->setGeometry(QRect(40, 140, 260, 210));
        wlanBox->setFont(font1);
        verticalLayout_3 = new QVBoxLayout(wlanBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_myip1 = new QLabel(wlanBox);
        label_myip1->setObjectName(QString::fromUtf8("label_myip1"));
        label_myip1->setMinimumSize(QSize(83, 28));
        label_myip1->setMaximumSize(QSize(83, 28));
        label_myip1->setFont(font1);

        horizontalLayout->addWidget(label_myip1);

        m_myip1 = new QLineEdit(wlanBox);
        m_myip1->setObjectName(QString::fromUtf8("m_myip1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_myip1->sizePolicy().hasHeightForWidth());
        m_myip1->setSizePolicy(sizePolicy1);
        m_myip1->setMinimumSize(QSize(140, 28));
        m_myip1->setMaximumSize(QSize(140, 28));
        m_myip1->setFont(font1);
        m_myip1->setEchoMode(QLineEdit::Normal);

        horizontalLayout->addWidget(m_myip1);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_gateway1 = new QLabel(wlanBox);
        label_gateway1->setObjectName(QString::fromUtf8("label_gateway1"));
        label_gateway1->setMinimumSize(QSize(83, 28));
        label_gateway1->setMaximumSize(QSize(83, 28));
        label_gateway1->setFont(font1);

        horizontalLayout_15->addWidget(label_gateway1);

        m_gateway1 = new QLineEdit(wlanBox);
        m_gateway1->setObjectName(QString::fromUtf8("m_gateway1"));
        m_gateway1->setEnabled(true);
        sizePolicy1.setHeightForWidth(m_gateway1->sizePolicy().hasHeightForWidth());
        m_gateway1->setSizePolicy(sizePolicy1);
        m_gateway1->setMinimumSize(QSize(140, 28));
        m_gateway1->setMaximumSize(QSize(140, 28));
        m_gateway1->setFont(font1);
        m_gateway1->setEchoMode(QLineEdit::Normal);

        horizontalLayout_15->addWidget(m_gateway1);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_myip2 = new QLabel(wlanBox);
        label_myip2->setObjectName(QString::fromUtf8("label_myip2"));
        label_myip2->setMinimumSize(QSize(83, 28));
        label_myip2->setMaximumSize(QSize(83, 28));
        label_myip2->setFont(font1);

        horizontalLayout_23->addWidget(label_myip2);

        m_myip2 = new QLineEdit(wlanBox);
        m_myip2->setObjectName(QString::fromUtf8("m_myip2"));
        sizePolicy1.setHeightForWidth(m_myip2->sizePolicy().hasHeightForWidth());
        m_myip2->setSizePolicy(sizePolicy1);
        m_myip2->setMinimumSize(QSize(140, 28));
        m_myip2->setMaximumSize(QSize(140, 28));
        m_myip2->setFont(font1);
        m_myip2->setEchoMode(QLineEdit::Normal);

        horizontalLayout_23->addWidget(m_myip2);


        verticalLayout_3->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_gateway2 = new QLabel(wlanBox);
        label_gateway2->setObjectName(QString::fromUtf8("label_gateway2"));
        label_gateway2->setMinimumSize(QSize(83, 28));
        label_gateway2->setMaximumSize(QSize(83, 28));
        label_gateway2->setFont(font1);

        horizontalLayout_24->addWidget(label_gateway2);

        m_gateway2 = new QLineEdit(wlanBox);
        m_gateway2->setObjectName(QString::fromUtf8("m_gateway2"));
        m_gateway2->setEnabled(true);
        sizePolicy1.setHeightForWidth(m_gateway2->sizePolicy().hasHeightForWidth());
        m_gateway2->setSizePolicy(sizePolicy1);
        m_gateway2->setMinimumSize(QSize(140, 28));
        m_gateway2->setMaximumSize(QSize(140, 28));
        m_gateway2->setFont(font1);
        m_gateway2->setEchoMode(QLineEdit::Normal);

        horizontalLayout_24->addWidget(m_gateway2);


        verticalLayout_3->addLayout(horizontalLayout_24);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer);

        pushButton_saveWlan = new QPushButton(wlanBox);
        pushButton_saveWlan->setObjectName(QString::fromUtf8("pushButton_saveWlan"));
        pushButton_saveWlan->setMinimumSize(QSize(0, 28));
        pushButton_saveWlan->setMaximumSize(QSize(16777215, 28));
        pushButton_saveWlan->setFont(font1);

        horizontalLayout_16->addWidget(pushButton_saveWlan);


        verticalLayout_3->addLayout(horizontalLayout_16);

        UseTimeBox = new QGroupBox(dlgTimeInterval);
        UseTimeBox->setObjectName(QString::fromUtf8("UseTimeBox"));
        UseTimeBox->setGeometry(QRect(340, 400, 210, 70));
        UseTimeBox->setFont(font1);
        UseTimeBox->setCheckable(false);
        UseTimeBox->setChecked(false);
        horizontalLayout_14 = new QHBoxLayout(UseTimeBox);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        UseTime = new QLineEdit(UseTimeBox);
        UseTime->setObjectName(QString::fromUtf8("UseTime"));
        UseTime->setEnabled(true);
        UseTime->setMinimumSize(QSize(40, 28));
        UseTime->setMaximumSize(QSize(40, 28));
        UseTime->setFont(font1);
        UseTime->setReadOnly(true);

        horizontalLayout_14->addWidget(UseTime);

        label_3 = new QLabel(UseTimeBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_14->addWidget(label_3);

        pushButton_UseTime = new QPushButton(UseTimeBox);
        pushButton_UseTime->setObjectName(QString::fromUtf8("pushButton_UseTime"));
        pushButton_UseTime->setMinimumSize(QSize(0, 28));
        pushButton_UseTime->setMaximumSize(QSize(16777215, 28));
        pushButton_UseTime->setFont(font1);

        horizontalLayout_14->addWidget(pushButton_UseTime);

        timeBox = new QGroupBox(dlgTimeInterval);
        timeBox->setObjectName(QString::fromUtf8("timeBox"));
        timeBox->setGeometry(QRect(580, 140, 190, 140));
        timeBox->setFont(font1);
        verticalLayout_4 = new QVBoxLayout(timeBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_4 = new QLabel(timeBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 28));
        label_4->setMaximumSize(QSize(16777215, 28));
        label_4->setFont(font1);

        horizontalLayout_7->addWidget(label_4);

        dateEdit = new QDateTimeEdit(timeBox);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setMinimumSize(QSize(115, 28));
        dateEdit->setMaximumSize(QSize(115, 28));
        dateEdit->setFont(font1);

        horizontalLayout_7->addWidget(dateEdit);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_5 = new QLabel(timeBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 28));
        label_5->setMaximumSize(QSize(16777215, 28));
        label_5->setFont(font1);

        horizontalLayout_8->addWidget(label_5);

        timeEdit = new QDateTimeEdit(timeBox);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setMinimumSize(QSize(115, 28));
        timeEdit->setMaximumSize(QSize(115, 28));
        timeEdit->setFont(font1);

        horizontalLayout_8->addWidget(timeEdit);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(40, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        m_ButtonTimeSet = new QPushButton(timeBox);
        m_ButtonTimeSet->setObjectName(QString::fromUtf8("m_ButtonTimeSet"));
        m_ButtonTimeSet->setMinimumSize(QSize(0, 28));
        m_ButtonTimeSet->setMaximumSize(QSize(16777215, 28));
        m_ButtonTimeSet->setFont(font1);

        horizontalLayout_9->addWidget(m_ButtonTimeSet);


        verticalLayout_4->addLayout(horizontalLayout_9);

        pingBox = new QGroupBox(dlgTimeInterval);
        pingBox->setObjectName(QString::fromUtf8("pingBox"));
        pingBox->setGeometry(QRect(40, 370, 270, 100));
        pingBox->setFont(font1);
        verticalLayout_10 = new QVBoxLayout(pingBox);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(pingBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 28));
        label_6->setMaximumSize(QSize(16777215, 28));
        label_6->setFont(font1);

        horizontalLayout_10->addWidget(label_6);

        m_pingIP = new QLineEdit(pingBox);
        m_pingIP->setObjectName(QString::fromUtf8("m_pingIP"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pingIP->sizePolicy().hasHeightForWidth());
        m_pingIP->setSizePolicy(sizePolicy2);
        m_pingIP->setMinimumSize(QSize(140, 28));
        m_pingIP->setMaximumSize(QSize(140, 28));
        m_pingIP->setFont(font1);
        m_pingIP->setEchoMode(QLineEdit::Normal);

        horizontalLayout_10->addWidget(m_pingIP);

        pingButton = new QPushButton(pingBox);
        pingButton->setObjectName(QString::fromUtf8("pingButton"));
        pingButton->setMinimumSize(QSize(0, 28));
        pingButton->setMaximumSize(QSize(45, 28));
        pingButton->setFont(font1);

        horizontalLayout_10->addWidget(pingButton);


        verticalLayout_10->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_8 = new QLabel(pingBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 28));
        label_8->setMaximumSize(QSize(16777215, 28));
        label_8->setFont(font1);

        horizontalLayout_11->addWidget(label_8);

        m_pingResult = new QLineEdit(pingBox);
        m_pingResult->setObjectName(QString::fromUtf8("m_pingResult"));
        sizePolicy2.setHeightForWidth(m_pingResult->sizePolicy().hasHeightForWidth());
        m_pingResult->setSizePolicy(sizePolicy2);
        m_pingResult->setMinimumSize(QSize(60, 28));
        m_pingResult->setMaximumSize(QSize(60, 28));
        m_pingResult->setFont(font1);
        m_pingResult->setEchoMode(QLineEdit::Normal);
        m_pingResult->setReadOnly(true);

        horizontalLayout_11->addWidget(m_pingResult);

        horizontalSpacer_4 = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);


        verticalLayout_10->addLayout(horizontalLayout_11);

        hostAddressSetBox = new QGroupBox(dlgTimeInterval);
        hostAddressSetBox->setObjectName(QString::fromUtf8("hostAddressSetBox"));
        hostAddressSetBox->setGeometry(QRect(330, 140, 220, 140));
        hostAddressSetBox->setFont(font1);
        verticalLayout_5 = new QVBoxLayout(hostAddressSetBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_HostAddress = new QLabel(hostAddressSetBox);
        label_HostAddress->setObjectName(QString::fromUtf8("label_HostAddress"));
        label_HostAddress->setMinimumSize(QSize(50, 28));
        label_HostAddress->setMaximumSize(QSize(50, 28));
        label_HostAddress->setFont(font1);

        horizontalLayout_17->addWidget(label_HostAddress);

        m_hostAddress = new QLineEdit(hostAddressSetBox);
        m_hostAddress->setObjectName(QString::fromUtf8("m_hostAddress"));
        sizePolicy2.setHeightForWidth(m_hostAddress->sizePolicy().hasHeightForWidth());
        m_hostAddress->setSizePolicy(sizePolicy2);
        m_hostAddress->setMinimumSize(QSize(140, 28));
        m_hostAddress->setMaximumSize(QSize(140, 28));
        m_hostAddress->setFont(font1);
        m_hostAddress->setEchoMode(QLineEdit::Normal);

        horizontalLayout_17->addWidget(m_hostAddress);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_com = new QLabel(hostAddressSetBox);
        label_com->setObjectName(QString::fromUtf8("label_com"));
        label_com->setMinimumSize(QSize(50, 28));
        label_com->setMaximumSize(QSize(50, 28));
        label_com->setFont(font1);

        horizontalLayout_5->addWidget(label_com);

        m_com = new QLineEdit(hostAddressSetBox);
        m_com->setObjectName(QString::fromUtf8("m_com"));
        sizePolicy2.setHeightForWidth(m_com->sizePolicy().hasHeightForWidth());
        m_com->setSizePolicy(sizePolicy2);
        m_com->setMinimumSize(QSize(60, 28));
        m_com->setMaximumSize(QSize(60, 28));
        m_com->setFont(font1);
        m_com->setEchoMode(QLineEdit::Normal);

        horizontalLayout_5->addWidget(m_com);

        pushButton_saveHostAddress = new QPushButton(hostAddressSetBox);
        pushButton_saveHostAddress->setObjectName(QString::fromUtf8("pushButton_saveHostAddress"));
        sizePolicy2.setHeightForWidth(pushButton_saveHostAddress->sizePolicy().hasHeightForWidth());
        pushButton_saveHostAddress->setSizePolicy(sizePolicy2);
        pushButton_saveHostAddress->setMinimumSize(QSize(0, 28));
        pushButton_saveHostAddress->setMaximumSize(QSize(80, 28));
        pushButton_saveHostAddress->setFont(font1);

        horizontalLayout_5->addWidget(pushButton_saveHostAddress);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_comStatus = new QLabel(hostAddressSetBox);
        label_comStatus->setObjectName(QString::fromUtf8("label_comStatus"));
        label_comStatus->setMinimumSize(QSize(0, 28));
        label_comStatus->setMaximumSize(QSize(16777215, 28));
        label_comStatus->setFont(font1);

        horizontalLayout_25->addWidget(label_comStatus);

        m_comStatus = new QLineEdit(hostAddressSetBox);
        m_comStatus->setObjectName(QString::fromUtf8("m_comStatus"));
        sizePolicy2.setHeightForWidth(m_comStatus->sizePolicy().hasHeightForWidth());
        m_comStatus->setSizePolicy(sizePolicy2);
        m_comStatus->setMinimumSize(QSize(0, 28));
        m_comStatus->setMaximumSize(QSize(150, 28));
        m_comStatus->setFont(font1);
        m_comStatus->setEchoMode(QLineEdit::Normal);
        m_comStatus->setReadOnly(true);

        horizontalLayout_25->addWidget(m_comStatus);


        verticalLayout_5->addLayout(horizontalLayout_25);

        StartRuleBox = new QGroupBox(dlgTimeInterval);
        StartRuleBox->setObjectName(QString::fromUtf8("StartRuleBox"));
        StartRuleBox->setGeometry(QRect(310, 20, 150, 105));
        StartRuleBox->setFont(font1);
        StartRuleBox->setCheckable(false);
        StartRuleBox->setChecked(false);
        verticalLayout_15 = new QVBoxLayout(StartRuleBox);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        allStartCheckBox = new QCheckBox(StartRuleBox);
        allStartCheckBox->setObjectName(QString::fromUtf8("allStartCheckBox"));
        allStartCheckBox->setFont(font1);

        verticalLayout_15->addWidget(allStartCheckBox);

        onlyStartGroupCheckBox = new QCheckBox(StartRuleBox);
        onlyStartGroupCheckBox->setObjectName(QString::fromUtf8("onlyStartGroupCheckBox"));
        onlyStartGroupCheckBox->setFont(font1);

        verticalLayout_15->addWidget(onlyStartGroupCheckBox);

        onlyStartPageCheckBox = new QCheckBox(StartRuleBox);
        onlyStartPageCheckBox->setObjectName(QString::fromUtf8("onlyStartPageCheckBox"));
        onlyStartPageCheckBox->setFont(font1);

        verticalLayout_15->addWidget(onlyStartPageCheckBox);

        CanNumberBox = new QGroupBox(dlgTimeInterval);
        CanNumberBox->setObjectName(QString::fromUtf8("CanNumberBox"));
        CanNumberBox->setGeometry(QRect(170, 20, 110, 85));
        CanNumberBox->setFont(font1);
        CanNumberBox->setCheckable(false);
        CanNumberBox->setChecked(false);
        verticalLayout_16 = new QVBoxLayout(CanNumberBox);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        Can4CheckBox = new QCheckBox(CanNumberBox);
        Can4CheckBox->setObjectName(QString::fromUtf8("Can4CheckBox"));
        Can4CheckBox->setFont(font1);

        verticalLayout_16->addWidget(Can4CheckBox);

        Can8CheckBox = new QCheckBox(CanNumberBox);
        Can8CheckBox->setObjectName(QString::fromUtf8("Can8CheckBox"));
        Can8CheckBox->setFont(font1);

        verticalLayout_16->addWidget(Can8CheckBox);

        controlType = new QGroupBox(dlgTimeInterval);
        controlType->setObjectName(QString::fromUtf8("controlType"));
        controlType->setGeometry(QRect(40, 20, 100, 85));
        controlType->setFont(font1);
        controlType->setCheckable(false);
        controlType->setChecked(false);
        verticalLayout_17 = new QVBoxLayout(controlType);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        singleWLAN = new QCheckBox(controlType);
        singleWLAN->setObjectName(QString::fromUtf8("singleWLAN"));
        singleWLAN->setFont(font1);

        verticalLayout_17->addWidget(singleWLAN);

        doubleWLAN = new QCheckBox(controlType);
        doubleWLAN->setObjectName(QString::fromUtf8("doubleWLAN"));
        doubleWLAN->setFont(font1);

        verticalLayout_17->addWidget(doubleWLAN);

        AutoPageBox = new QGroupBox(dlgTimeInterval);
        AutoPageBox->setObjectName(QString::fromUtf8("AutoPageBox"));
        AutoPageBox->setGeometry(QRect(1040, 20, 150, 62));
        AutoPageBox->setFont(font1);
        AutoPageBox->setCheckable(false);
        AutoPageBox->setChecked(false);
        verticalLayout_8 = new QVBoxLayout(AutoPageBox);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        autoPageCheckBox = new QCheckBox(AutoPageBox);
        autoPageCheckBox->setObjectName(QString::fromUtf8("autoPageCheckBox"));
        autoPageCheckBox->setFont(font1);

        verticalLayout_8->addWidget(autoPageCheckBox);

        testLinkageComBox = new QGroupBox(dlgTimeInterval);
        testLinkageComBox->setObjectName(QString::fromUtf8("testLinkageComBox"));
        testLinkageComBox->setGeometry(QRect(800, 140, 220, 140));
        testLinkageComBox->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(testLinkageComBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(testLinkageComBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 28));
        label_11->setMaximumSize(QSize(16777215, 28));
        label_11->setFont(font1);

        horizontalLayout_4->addWidget(label_11);

        comboBox_testLinkageCom = new QComboBox(testLinkageComBox);
        comboBox_testLinkageCom->addItem(QString());
        comboBox_testLinkageCom->addItem(QString());
        comboBox_testLinkageCom->addItem(QString());
        comboBox_testLinkageCom->addItem(QString());
        comboBox_testLinkageCom->addItem(QString());
        comboBox_testLinkageCom->addItem(QString());
        comboBox_testLinkageCom->setObjectName(QString::fromUtf8("comboBox_testLinkageCom"));
        comboBox_testLinkageCom->setMinimumSize(QSize(0, 28));
        comboBox_testLinkageCom->setMaximumSize(QSize(16777215, 28));
        comboBox_testLinkageCom->setFont(font1);

        horizontalLayout_4->addWidget(comboBox_testLinkageCom);

        pushButton_testLinkageCom = new QPushButton(testLinkageComBox);
        pushButton_testLinkageCom->setObjectName(QString::fromUtf8("pushButton_testLinkageCom"));
        pushButton_testLinkageCom->setMinimumSize(QSize(0, 28));
        pushButton_testLinkageCom->setMaximumSize(QSize(50, 28));
        pushButton_testLinkageCom->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_testLinkageCom);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_9 = new QLabel(testLinkageComBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 28));
        label_9->setMaximumSize(QSize(16777215, 28));
        label_9->setFont(font1);

        horizontalLayout_12->addWidget(label_9);

        m_testLinkageComResult = new QLineEdit(testLinkageComBox);
        m_testLinkageComResult->setObjectName(QString::fromUtf8("m_testLinkageComResult"));
        sizePolicy2.setHeightForWidth(m_testLinkageComResult->sizePolicy().hasHeightForWidth());
        m_testLinkageComResult->setSizePolicy(sizePolicy2);
        m_testLinkageComResult->setMinimumSize(QSize(60, 28));
        m_testLinkageComResult->setMaximumSize(QSize(80, 28));
        m_testLinkageComResult->setFont(font1);
        m_testLinkageComResult->setEchoMode(QLineEdit::Normal);
        m_testLinkageComResult->setReadOnly(true);

        horizontalLayout_12->addWidget(m_testLinkageComResult);

        testLinkageComButton = new QPushButton(testLinkageComBox);
        testLinkageComButton->setObjectName(QString::fromUtf8("testLinkageComButton"));
        testLinkageComButton->setMinimumSize(QSize(0, 28));
        testLinkageComButton->setMaximumSize(QSize(50, 28));
        testLinkageComButton->setFont(font1);

        horizontalLayout_12->addWidget(testLinkageComButton);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_15 = new QLabel(testLinkageComBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(0, 28));
        label_15->setMaximumSize(QSize(16777215, 28));
        label_15->setFont(font1);

        horizontalLayout_28->addWidget(label_15);

        m_linkageStatus = new QLineEdit(testLinkageComBox);
        m_linkageStatus->setObjectName(QString::fromUtf8("m_linkageStatus"));
        sizePolicy2.setHeightForWidth(m_linkageStatus->sizePolicy().hasHeightForWidth());
        m_linkageStatus->setSizePolicy(sizePolicy2);
        m_linkageStatus->setMinimumSize(QSize(60, 28));
        m_linkageStatus->setMaximumSize(QSize(80, 28));
        m_linkageStatus->setFont(font1);
        m_linkageStatus->setEchoMode(QLineEdit::Normal);
        m_linkageStatus->setReadOnly(true);

        horizontalLayout_28->addWidget(m_linkageStatus);

        horizontalSpacer_5 = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_28);

        groupBox_phoneNumber = new QGroupBox(dlgTimeInterval);
        groupBox_phoneNumber->setObjectName(QString::fromUtf8("groupBox_phoneNumber"));
        groupBox_phoneNumber->setGeometry(QRect(340, 310, 210, 70));
        groupBox_phoneNumber->setFont(font1);
        horizontalLayout_26 = new QHBoxLayout(groupBox_phoneNumber);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        lineEdit_phoneNumber = new QLineEdit(groupBox_phoneNumber);
        lineEdit_phoneNumber->setObjectName(QString::fromUtf8("lineEdit_phoneNumber"));
        lineEdit_phoneNumber->setMinimumSize(QSize(130, 28));
        lineEdit_phoneNumber->setMaximumSize(QSize(130, 28));
        lineEdit_phoneNumber->setFont(font1);

        horizontalLayout_26->addWidget(lineEdit_phoneNumber);

        pushButton_phoneNumber = new QPushButton(groupBox_phoneNumber);
        pushButton_phoneNumber->setObjectName(QString::fromUtf8("pushButton_phoneNumber"));
        pushButton_phoneNumber->setMinimumSize(QSize(50, 28));
        pushButton_phoneNumber->setMaximumSize(QSize(50, 28));
        pushButton_phoneNumber->setFont(font1);

        horizontalLayout_26->addWidget(pushButton_phoneNumber);

        groupBox_firepointNumber = new QGroupBox(dlgTimeInterval);
        groupBox_firepointNumber->setObjectName(QString::fromUtf8("groupBox_firepointNumber"));
        groupBox_firepointNumber->setGeometry(QRect(780, 310, 170, 70));
        groupBox_firepointNumber->setFont(font1);
        horizontalLayout_27 = new QHBoxLayout(groupBox_firepointNumber);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        lineEdit_firepointNumber = new QLineEdit(groupBox_firepointNumber);
        lineEdit_firepointNumber->setObjectName(QString::fromUtf8("lineEdit_firepointNumber"));
        lineEdit_firepointNumber->setMinimumSize(QSize(40, 28));
        lineEdit_firepointNumber->setMaximumSize(QSize(40, 28));
        lineEdit_firepointNumber->setFont(font1);

        horizontalLayout_27->addWidget(lineEdit_firepointNumber);

        pushButton_firepointNumber = new QPushButton(groupBox_firepointNumber);
        pushButton_firepointNumber->setObjectName(QString::fromUtf8("pushButton_firepointNumber"));
        pushButton_firepointNumber->setMinimumSize(QSize(50, 28));
        pushButton_firepointNumber->setMaximumSize(QSize(50, 28));
        pushButton_firepointNumber->setFont(font1);

        horizontalLayout_27->addWidget(pushButton_firepointNumber);

        pushButton_lampForbidList = new QPushButton(dlgTimeInterval);
        pushButton_lampForbidList->setObjectName(QString::fromUtf8("pushButton_lampForbidList"));
        pushButton_lampForbidList->setGeometry(QRect(1040, 100, 150, 28));
        pushButton_lampForbidList->setMinimumSize(QSize(150, 28));
        pushButton_lampForbidList->setMaximumSize(QSize(150, 28));
        pushButton_lampForbidList->setFont(font1);
        lampEmergencyType = new QGroupBox(dlgTimeInterval);
        lampEmergencyType->setObjectName(QString::fromUtf8("lampEmergencyType"));
        lampEmergencyType->setGeometry(QRect(790, 20, 230, 105));
        lampEmergencyType->setFont(font1);
        verticalLayout_7 = new QVBoxLayout(lampEmergencyType);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        DirectionTwinkleOneCheckBox = new QCheckBox(lampEmergencyType);
        DirectionTwinkleOneCheckBox->setObjectName(QString::fromUtf8("DirectionTwinkleOneCheckBox"));
        DirectionTwinkleOneCheckBox->setFont(font1);

        verticalLayout_7->addWidget(DirectionTwinkleOneCheckBox);

        DirectionTwinkleDoubleCheckBox = new QCheckBox(lampEmergencyType);
        DirectionTwinkleDoubleCheckBox->setObjectName(QString::fromUtf8("DirectionTwinkleDoubleCheckBox"));
        DirectionTwinkleDoubleCheckBox->setFont(font1);

        verticalLayout_7->addWidget(DirectionTwinkleDoubleCheckBox);

        TwinkleConfigCheckBox = new QCheckBox(lampEmergencyType);
        TwinkleConfigCheckBox->setObjectName(QString::fromUtf8("TwinkleConfigCheckBox"));
        TwinkleConfigCheckBox->setFont(font1);

        verticalLayout_7->addWidget(TwinkleConfigCheckBox);

        pushButton_lamptwinkleconfig = new QPushButton(dlgTimeInterval);
        pushButton_lamptwinkleconfig->setObjectName(QString::fromUtf8("pushButton_lamptwinkleconfig"));
        pushButton_lamptwinkleconfig->setGeometry(QRect(1210, 100, 110, 28));
        pushButton_lamptwinkleconfig->setMinimumSize(QSize(110, 28));
        pushButton_lamptwinkleconfig->setMaximumSize(QSize(110, 28));
        pushButton_lamptwinkleconfig->setFont(font1);
        ARTUBox = new QGroupBox(dlgTimeInterval);
        ARTUBox->setObjectName(QString::fromUtf8("ARTUBox"));
        ARTUBox->setGeometry(QRect(580, 310, 170, 135));
        ARTUBox->setFont(font1);
        ARTUBox->setCheckable(false);
        ARTUBox->setChecked(false);
        verticalLayout_18 = new QVBoxLayout(ARTUBox);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        forbidARTUCheckBox = new QCheckBox(ARTUBox);
        forbidARTUCheckBox->setObjectName(QString::fromUtf8("forbidARTUCheckBox"));
        forbidARTUCheckBox->setFont(font1);

        verticalLayout_18->addWidget(forbidARTUCheckBox);

        ARTU079KCheckBox = new QCheckBox(ARTUBox);
        ARTU079KCheckBox->setObjectName(QString::fromUtf8("ARTU079KCheckBox"));
        ARTU079KCheckBox->setFont(font1);

        verticalLayout_18->addWidget(ARTU079KCheckBox);

        ARTU079KJCheckBox = new QCheckBox(ARTUBox);
        ARTU079KJCheckBox->setObjectName(QString::fromUtf8("ARTU079KJCheckBox"));
        ARTU079KJCheckBox->setFont(font1);

        verticalLayout_18->addWidget(ARTU079KJCheckBox);

        ARTU426CheckBox = new QCheckBox(ARTUBox);
        ARTU426CheckBox->setObjectName(QString::fromUtf8("ARTU426CheckBox"));
        ARTU426CheckBox->setFont(font1);

        verticalLayout_18->addWidget(ARTU426CheckBox);

        groupBox_ModbusTCP = new QGroupBox(dlgTimeInterval);
        groupBox_ModbusTCP->setObjectName(QString::fromUtf8("groupBox_ModbusTCP"));
        groupBox_ModbusTCP->setGeometry(QRect(780, 400, 170, 80));
        groupBox_ModbusTCP->setFont(font1);
        pushButton_ModbusTCP = new QPushButton(groupBox_ModbusTCP);
        pushButton_ModbusTCP->setObjectName(QString::fromUtf8("pushButton_ModbusTCP"));
        pushButton_ModbusTCP->setGeometry(QRect(20, 40, 130, 28));
        pushButton_ModbusTCP->setMinimumSize(QSize(130, 28));
        pushButton_ModbusTCP->setFont(font1);

        retranslateUi(dlgTimeInterval);

        QMetaObject::connectSlotsByName(dlgTimeInterval);
    } // setupUi

    void retranslateUi(QDialog *dlgTimeInterval)
    {
        dlgTimeInterval->setWindowTitle(QApplication::translate("dlgTimeInterval", "Dialog", nullptr));
        EnergyModeBox->setTitle(QApplication::translate("dlgTimeInterval", "\350\212\202\350\203\275\346\250\241\345\274\217", nullptr));
        EnergyCheckBox->setText(QApplication::translate("dlgTimeInterval", "\350\212\202\350\203\275\346\250\241\345\274\217", nullptr));
        EmergencyBox->setTitle(QApplication::translate("dlgTimeInterval", "\345\272\224\346\200\245\345\217\202\346\225\260", nullptr));
        TwinkleCheckBox->setText(QApplication::translate("dlgTimeInterval", "\346\240\207\345\277\227\347\201\257\345\272\224\346\200\245\351\227\252\347\203\201", nullptr));
        emergencyOnlyDistributionCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\272\224\346\200\245\344\273\205\345\220\257\345\212\250\347\201\257\345\205\267\346\211\200\345\234\250\351\233\206\344\270\255\347\224\265\346\272\220", nullptr));
        VersionBox->setTitle(QApplication::translate("dlgTimeInterval", "\344\270\255\351\227\264\345\261\202\347\211\210\346\234\254\345\217\267", nullptr));
        label_10->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\351\224\256\346\235\277:", nullptr));
        label_CAN1_2->setText(QApplication::translate("dlgTimeInterval", "CAN1/2:", nullptr));
        pushButton_can1can2->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", nullptr));
        label_CAN3_4->setText(QApplication::translate("dlgTimeInterval", "CAN3/4:", nullptr));
        pushButton_can3can4->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", nullptr));
        label_CAN5_6->setText(QApplication::translate("dlgTimeInterval", "CAN5/6:", nullptr));
        pushButton_can5can6->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", nullptr));
        label_CAN7_8->setText(QApplication::translate("dlgTimeInterval", "CAN7/8:", nullptr));
        pushButton_can7can8->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", nullptr));
        wlanBox->setTitle(QApplication::translate("dlgTimeInterval", "\347\275\221\345\217\243", nullptr));
        label_myip1->setText(QApplication::translate("dlgTimeInterval", "\347\275\221\345\217\2431\345\234\260\345\235\200:", nullptr));
        label_gateway1->setText(QApplication::translate("dlgTimeInterval", " \351\273\230\350\256\244\347\275\221\345\205\263: ", nullptr));
        label_myip2->setText(QApplication::translate("dlgTimeInterval", "\347\275\221\345\217\2432\345\234\260\345\235\200:", nullptr));
        label_gateway2->setText(QApplication::translate("dlgTimeInterval", " \351\273\230\350\256\244\347\275\221\345\205\263: ", nullptr));
        pushButton_saveWlan->setText(QApplication::translate("dlgTimeInterval", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
        UseTimeBox->setTitle(QApplication::translate("dlgTimeInterval", "\344\275\277\347\224\250\346\234\237\351\231\220", nullptr));
        label_3->setText(QApplication::translate("dlgTimeInterval", "\345\244\251", nullptr));
        pushButton_UseTime->setText(QApplication::translate("dlgTimeInterval", "\344\277\256\346\224\271\344\275\277\347\224\250\346\234\237\351\231\220", nullptr));
        timeBox->setTitle(QApplication::translate("dlgTimeInterval", "\346\227\266\351\227\264\350\256\276\347\275\256", nullptr));
        label_4->setText(QApplication::translate("dlgTimeInterval", "\346\227\245\346\234\237:", nullptr));
        dateEdit->setDisplayFormat(QApplication::translate("dlgTimeInterval", "yyyy-MM-dd", nullptr));
        label_5->setText(QApplication::translate("dlgTimeInterval", "\346\227\266\351\227\264:", nullptr));
        timeEdit->setDisplayFormat(QApplication::translate("dlgTimeInterval", "HH:mm:ss", nullptr));
        m_ButtonTimeSet->setText(QApplication::translate("dlgTimeInterval", "\344\277\256\346\224\271\346\227\266\351\227\264", nullptr));
        pingBox->setTitle(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\346\265\213\350\257\225(Ping)", nullptr));
        label_6->setText(QApplication::translate("dlgTimeInterval", "IP\345\234\260\345\235\200:", nullptr));
        pingButton->setText(QApplication::translate("dlgTimeInterval", "ping", nullptr));
        label_8->setText(QApplication::translate("dlgTimeInterval", "\346\265\213\350\257\225\346\210\220\345\212\237\347\216\207:", nullptr));
        hostAddressSetBox->setTitle(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\345\234\260\345\235\200", nullptr));
        label_HostAddress->setText(QApplication::translate("dlgTimeInterval", "\345\234\260\345\235\200:", nullptr));
        label_com->setText(QApplication::translate("dlgTimeInterval", "\347\253\257\345\217\243:", nullptr));
        pushButton_saveHostAddress->setText(QApplication::translate("dlgTimeInterval", "\344\277\235\345\255\230\350\256\276\347\275\256", nullptr));
        label_comStatus->setText(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\347\212\266\346\200\201:", nullptr));
        StartRuleBox->setTitle(QApplication::translate("dlgTimeInterval", "\345\220\257\345\212\250\350\247\204\345\210\231", nullptr));
        allStartCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\205\250\351\203\250\345\220\257\345\212\250", nullptr));
        onlyStartGroupCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\210\206\347\273\204\345\220\257\345\212\250", nullptr));
        onlyStartPageCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\345\212\250\346\211\200\345\234\250\351\241\265\351\235\242", nullptr));
        CanNumberBox->setTitle(QApplication::translate("dlgTimeInterval", "CAN\345\233\236\350\267\257\346\225\260", nullptr));
        Can4CheckBox->setText(QApplication::translate("dlgTimeInterval", "4\350\267\257CAN", nullptr));
        Can8CheckBox->setText(QApplication::translate("dlgTimeInterval", "8\350\267\257CAN", nullptr));
        controlType->setTitle(QApplication::translate("dlgTimeInterval", "\344\270\273\346\234\272\347\261\273\345\236\213", nullptr));
        singleWLAN->setText(QApplication::translate("dlgTimeInterval", "\345\215\225\347\275\221\345\217\243", nullptr));
        doubleWLAN->setText(QApplication::translate("dlgTimeInterval", "\345\217\214\347\275\221\345\217\243", nullptr));
        AutoPageBox->setTitle(QApplication::translate("dlgTimeInterval", "\350\207\252\345\212\250\350\275\256\350\257\242\351\241\265\351\235\242", nullptr));
        autoPageCheckBox->setText(QApplication::translate("dlgTimeInterval", "\350\207\252\345\212\250\350\275\256\350\257\242\351\241\265\351\235\242", nullptr));
        testLinkageComBox->setTitle(QApplication::translate("dlgTimeInterval", "RS232/RS485\351\200\232\350\256\257(\347\201\253\346\212\245)", nullptr));
        label_11->setText(QApplication::translate("dlgTimeInterval", "\346\263\242\347\211\271\347\216\207:", nullptr));
        comboBox_testLinkageCom->setItemText(0, QApplication::translate("dlgTimeInterval", "4800", nullptr));
        comboBox_testLinkageCom->setItemText(1, QApplication::translate("dlgTimeInterval", "9600", nullptr));
        comboBox_testLinkageCom->setItemText(2, QApplication::translate("dlgTimeInterval", "19200", nullptr));
        comboBox_testLinkageCom->setItemText(3, QApplication::translate("dlgTimeInterval", "38400", nullptr));
        comboBox_testLinkageCom->setItemText(4, QApplication::translate("dlgTimeInterval", "57600", nullptr));
        comboBox_testLinkageCom->setItemText(5, QApplication::translate("dlgTimeInterval", "115200", nullptr));

        pushButton_testLinkageCom->setText(QApplication::translate("dlgTimeInterval", "\350\256\276\347\275\256", nullptr));
        label_9->setText(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\346\265\213\350\257\225:", nullptr));
        testLinkageComButton->setText(QApplication::translate("dlgTimeInterval", "\346\265\213\350\257\225", nullptr));
        label_15->setText(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\347\212\266\346\200\201:", nullptr));
        groupBox_phoneNumber->setTitle(QApplication::translate("dlgTimeInterval", "\350\201\224\347\263\273\346\226\271\345\274\217", nullptr));
        pushButton_phoneNumber->setText(QApplication::translate("dlgTimeInterval", "\350\256\276\347\275\256", nullptr));
        groupBox_firepointNumber->setTitle(QApplication::translate("dlgTimeInterval", "\345\220\257\345\212\250\347\201\253\350\255\246\347\202\271\344\270\252\346\225\260", nullptr));
        pushButton_firepointNumber->setText(QApplication::translate("dlgTimeInterval", "\350\256\276\347\275\256", nullptr));
        pushButton_lampForbidList->setText(QApplication::translate("dlgTimeInterval", "\346\230\276\347\244\272\347\201\257\345\205\267\347\246\201\347\224\250\345\210\227\350\241\250", nullptr));
        lampEmergencyType->setTitle(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\345\272\224\346\200\245\347\261\273\345\236\213", nullptr));
        DirectionTwinkleOneCheckBox->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\346\226\271\345\220\221\345\222\214\351\227\252\347\203\201\350\277\236\345\217\221", nullptr));
        DirectionTwinkleDoubleCheckBox->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\346\226\271\345\220\221\343\200\201\351\227\252\347\203\201\345\215\225\347\213\254\346\216\247\345\210\266", nullptr));
        TwinkleConfigCheckBox->setText(QApplication::translate("dlgTimeInterval", "\351\227\252\347\203\201\351\205\215\347\275\256\345\236\213\347\201\257\345\205\267", nullptr));
        pushButton_lamptwinkleconfig->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\351\227\252\347\203\201\351\205\215\347\275\256", nullptr));
        ARTUBox->setTitle(QApplication::translate("dlgTimeInterval", "ARTU\350\201\224\345\212\250\346\250\241\345\235\227", nullptr));
        forbidARTUCheckBox->setText(QApplication::translate("dlgTimeInterval", "\347\246\201\347\224\250ARTU", nullptr));
        ARTU079KCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\347\224\250079ARTU-K", nullptr));
        ARTU079KJCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\347\224\250079ARTU-KJ", nullptr));
        ARTU426CheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\347\224\250ARTU-426", nullptr));
        groupBox_ModbusTCP->setTitle(QApplication::translate("dlgTimeInterval", "ModbusTCP\346\234\215\345\212\241", nullptr));
        pushButton_ModbusTCP->setText(QApplication::translate("dlgTimeInterval", "\345\257\274\345\207\272\345\257\204\345\255\230\345\231\250\347\202\271\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgTimeInterval: public Ui_dlgTimeInterval {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGTIMEINTERVAL_H
