/********************************************************************************
** Form generated from reading UI file 'dlgadminParamPage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGADMINPARAMPAGE_H
#define UI_DLGADMINPARAMPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlgadminParamPage
{
public:
    QGroupBox *MYcheckBox;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *MonthCheckBox;
    QCheckBox *YearCheckBox;
    QGroupBox *MYcheckTimeBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_1;
    QLineEdit *lineEdit_month;
    QLabel *label_9;
    QPushButton *pushButton_month;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_year;
    QLabel *label_10;
    QPushButton *pushButton_year;
    QGroupBox *SoundBox;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *SoundFCheckBox;
    QCheckBox *SoundECheckBox;
    QLabel *label;
    QGroupBox *FirePointBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *HideLinkLineCheckBox;
    QCheckBox *HideFirePointCheckBox;
    QCheckBox *ShieldUnknownFirePointCheckBox;
    QGroupBox *LightFaultBox;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *ShieldArrowLampLightFaultCheckBox;
    QCheckBox *ShieldLightLampLightFaultCheckBox;
    QCheckBox *ShieldUndergroundLampLightFaultCheckBox;
    QGroupBox *ComFaultBox;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *ShieldLampComFaultCheckBox;
    QCheckBox *ShieldCanDeviceComFaultCheckBox;
    QCheckBox *ShieldLoginComFaultCheckBox;
    QGroupBox *PowerFaultBox;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *ShieldMainPowerFaultEmergencyCheckBox;
    QCheckBox *HideBatPowerFaultShowCheckBox;
    QGroupBox *groupBox_emergencyParam;
    QVBoxLayout *verticalLayout;
    QCheckBox *OldLampcheckBox;
    QPushButton *pushButton_testMQTT;

    void setupUi(QDialog *dlgadminParamPage)
    {
        if (dlgadminParamPage->objectName().isEmpty())
            dlgadminParamPage->setObjectName(QString::fromUtf8("dlgadminParamPage"));
        dlgadminParamPage->resize(1366, 510);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dlgadminParamPage->sizePolicy().hasHeightForWidth());
        dlgadminParamPage->setSizePolicy(sizePolicy);
        dlgadminParamPage->setMinimumSize(QSize(1366, 0));
        dlgadminParamPage->setMaximumSize(QSize(1366, 510));
        dlgadminParamPage->setStyleSheet(QString::fromUtf8(""));
        MYcheckBox = new QGroupBox(dlgadminParamPage);
        MYcheckBox->setObjectName(QString::fromUtf8("MYcheckBox"));
        MYcheckBox->setGeometry(QRect(220, 60, 120, 90));
        QFont font;
        font.setPointSize(12);
        MYcheckBox->setFont(font);
        MYcheckBox->setCheckable(false);
        MYcheckBox->setChecked(false);
        verticalLayout_5 = new QVBoxLayout(MYcheckBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        MonthCheckBox = new QCheckBox(MYcheckBox);
        MonthCheckBox->setObjectName(QString::fromUtf8("MonthCheckBox"));
        MonthCheckBox->setFont(font);

        verticalLayout_5->addWidget(MonthCheckBox);

        YearCheckBox = new QCheckBox(MYcheckBox);
        YearCheckBox->setObjectName(QString::fromUtf8("YearCheckBox"));
        YearCheckBox->setFont(font);
        YearCheckBox->setTristate(false);

        verticalLayout_5->addWidget(YearCheckBox);

        MYcheckTimeBox = new QGroupBox(dlgadminParamPage);
        MYcheckTimeBox->setObjectName(QString::fromUtf8("MYcheckTimeBox"));
        MYcheckTimeBox->setGeometry(QRect(390, 60, 230, 110));
        MYcheckTimeBox->setFont(font);
        MYcheckTimeBox->setCheckable(false);
        MYcheckTimeBox->setChecked(false);
        layoutWidget = new QWidget(MYcheckTimeBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(19, 27, 197, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_1 = new QLabel(layoutWidget);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setMinimumSize(QSize(0, 28));
        label_1->setMaximumSize(QSize(84, 28));
        label_1->setFont(font);

        horizontalLayout->addWidget(label_1);

        lineEdit_month = new QLineEdit(layoutWidget);
        lineEdit_month->setObjectName(QString::fromUtf8("lineEdit_month"));
        lineEdit_month->setMinimumSize(QSize(40, 28));
        lineEdit_month->setMaximumSize(QSize(40, 28));
        lineEdit_month->setFont(font);

        horizontalLayout->addWidget(lineEdit_month);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 28));
        label_9->setMaximumSize(QSize(84, 28));
        label_9->setFont(font);

        horizontalLayout->addWidget(label_9);

        pushButton_month = new QPushButton(layoutWidget);
        pushButton_month->setObjectName(QString::fromUtf8("pushButton_month"));
        pushButton_month->setMinimumSize(QSize(50, 28));
        pushButton_month->setMaximumSize(QSize(50, 28));
        pushButton_month->setFont(font);

        horizontalLayout->addWidget(pushButton_month);

        layoutWidget1 = new QWidget(MYcheckTimeBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 60, 196, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 28));
        label_2->setMaximumSize(QSize(84, 28));
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2);

        lineEdit_year = new QLineEdit(layoutWidget1);
        lineEdit_year->setObjectName(QString::fromUtf8("lineEdit_year"));
        lineEdit_year->setMinimumSize(QSize(40, 28));
        lineEdit_year->setMaximumSize(QSize(40, 28));
        lineEdit_year->setFont(font);

        horizontalLayout_3->addWidget(lineEdit_year);

        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(0, 28));
        label_10->setMaximumSize(QSize(84, 28));
        label_10->setFont(font);

        horizontalLayout_3->addWidget(label_10);

        pushButton_year = new QPushButton(layoutWidget1);
        pushButton_year->setObjectName(QString::fromUtf8("pushButton_year"));
        pushButton_year->setMinimumSize(QSize(50, 28));
        pushButton_year->setMaximumSize(QSize(50, 28));
        pushButton_year->setFont(font);

        horizontalLayout_3->addWidget(pushButton_year);

        SoundBox = new QGroupBox(dlgadminParamPage);
        SoundBox->setObjectName(QString::fromUtf8("SoundBox"));
        SoundBox->setGeometry(QRect(40, 60, 130, 90));
        SoundBox->setFont(font);
        SoundBox->setCheckable(false);
        SoundBox->setChecked(false);
        verticalLayout_2 = new QVBoxLayout(SoundBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        SoundFCheckBox = new QCheckBox(SoundBox);
        SoundFCheckBox->setObjectName(QString::fromUtf8("SoundFCheckBox"));
        SoundFCheckBox->setFont(font);

        verticalLayout_2->addWidget(SoundFCheckBox);

        SoundECheckBox = new QCheckBox(SoundBox);
        SoundECheckBox->setObjectName(QString::fromUtf8("SoundECheckBox"));
        SoundECheckBox->setFont(font);
        SoundECheckBox->setTristate(false);

        verticalLayout_2->addWidget(SoundECheckBox);

        label = new QLabel(dlgadminParamPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 10, 400, 30));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        FirePointBox = new QGroupBox(dlgadminParamPage);
        FirePointBox->setObjectName(QString::fromUtf8("FirePointBox"));
        FirePointBox->setGeometry(QRect(670, 60, 170, 110));
        FirePointBox->setFont(font);
        FirePointBox->setCheckable(false);
        FirePointBox->setChecked(false);
        verticalLayout_3 = new QVBoxLayout(FirePointBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        HideLinkLineCheckBox = new QCheckBox(FirePointBox);
        HideLinkLineCheckBox->setObjectName(QString::fromUtf8("HideLinkLineCheckBox"));
        HideLinkLineCheckBox->setFont(font);

        verticalLayout_3->addWidget(HideLinkLineCheckBox);

        HideFirePointCheckBox = new QCheckBox(FirePointBox);
        HideFirePointCheckBox->setObjectName(QString::fromUtf8("HideFirePointCheckBox"));
        HideFirePointCheckBox->setFont(font);
        HideFirePointCheckBox->setTristate(false);

        verticalLayout_3->addWidget(HideFirePointCheckBox);

        ShieldUnknownFirePointCheckBox = new QCheckBox(FirePointBox);
        ShieldUnknownFirePointCheckBox->setObjectName(QString::fromUtf8("ShieldUnknownFirePointCheckBox"));
        ShieldUnknownFirePointCheckBox->setFont(font);

        verticalLayout_3->addWidget(ShieldUnknownFirePointCheckBox);

        LightFaultBox = new QGroupBox(dlgadminParamPage);
        LightFaultBox->setObjectName(QString::fromUtf8("LightFaultBox"));
        LightFaultBox->setGeometry(QRect(890, 60, 140, 110));
        LightFaultBox->setFont(font);
        LightFaultBox->setCheckable(false);
        LightFaultBox->setChecked(false);
        verticalLayout_4 = new QVBoxLayout(LightFaultBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ShieldArrowLampLightFaultCheckBox = new QCheckBox(LightFaultBox);
        ShieldArrowLampLightFaultCheckBox->setObjectName(QString::fromUtf8("ShieldArrowLampLightFaultCheckBox"));
        ShieldArrowLampLightFaultCheckBox->setFont(font);

        verticalLayout_4->addWidget(ShieldArrowLampLightFaultCheckBox);

        ShieldLightLampLightFaultCheckBox = new QCheckBox(LightFaultBox);
        ShieldLightLampLightFaultCheckBox->setObjectName(QString::fromUtf8("ShieldLightLampLightFaultCheckBox"));
        ShieldLightLampLightFaultCheckBox->setFont(font);
        ShieldLightLampLightFaultCheckBox->setTristate(false);

        verticalLayout_4->addWidget(ShieldLightLampLightFaultCheckBox);

        ShieldUndergroundLampLightFaultCheckBox = new QCheckBox(LightFaultBox);
        ShieldUndergroundLampLightFaultCheckBox->setObjectName(QString::fromUtf8("ShieldUndergroundLampLightFaultCheckBox"));
        ShieldUndergroundLampLightFaultCheckBox->setFont(font);

        verticalLayout_4->addWidget(ShieldUndergroundLampLightFaultCheckBox);

        ComFaultBox = new QGroupBox(dlgadminParamPage);
        ComFaultBox->setObjectName(QString::fromUtf8("ComFaultBox"));
        ComFaultBox->setGeometry(QRect(1080, 60, 241, 110));
        ComFaultBox->setFont(font);
        ComFaultBox->setCheckable(false);
        ComFaultBox->setChecked(false);
        verticalLayout_6 = new QVBoxLayout(ComFaultBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        ShieldLampComFaultCheckBox = new QCheckBox(ComFaultBox);
        ShieldLampComFaultCheckBox->setObjectName(QString::fromUtf8("ShieldLampComFaultCheckBox"));
        ShieldLampComFaultCheckBox->setFont(font);

        verticalLayout_6->addWidget(ShieldLampComFaultCheckBox);

        ShieldCanDeviceComFaultCheckBox = new QCheckBox(ComFaultBox);
        ShieldCanDeviceComFaultCheckBox->setObjectName(QString::fromUtf8("ShieldCanDeviceComFaultCheckBox"));
        ShieldCanDeviceComFaultCheckBox->setFont(font);
        ShieldCanDeviceComFaultCheckBox->setTristate(false);

        verticalLayout_6->addWidget(ShieldCanDeviceComFaultCheckBox);

        ShieldLoginComFaultCheckBox = new QCheckBox(ComFaultBox);
        ShieldLoginComFaultCheckBox->setObjectName(QString::fromUtf8("ShieldLoginComFaultCheckBox"));
        ShieldLoginComFaultCheckBox->setFont(font);

        verticalLayout_6->addWidget(ShieldLoginComFaultCheckBox);

        PowerFaultBox = new QGroupBox(dlgadminParamPage);
        PowerFaultBox->setObjectName(QString::fromUtf8("PowerFaultBox"));
        PowerFaultBox->setGeometry(QRect(40, 180, 190, 90));
        PowerFaultBox->setFont(font);
        PowerFaultBox->setCheckable(false);
        PowerFaultBox->setChecked(false);
        verticalLayout_7 = new QVBoxLayout(PowerFaultBox);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        ShieldMainPowerFaultEmergencyCheckBox = new QCheckBox(PowerFaultBox);
        ShieldMainPowerFaultEmergencyCheckBox->setObjectName(QString::fromUtf8("ShieldMainPowerFaultEmergencyCheckBox"));
        ShieldMainPowerFaultEmergencyCheckBox->setFont(font);

        verticalLayout_7->addWidget(ShieldMainPowerFaultEmergencyCheckBox);

        HideBatPowerFaultShowCheckBox = new QCheckBox(PowerFaultBox);
        HideBatPowerFaultShowCheckBox->setObjectName(QString::fromUtf8("HideBatPowerFaultShowCheckBox"));
        HideBatPowerFaultShowCheckBox->setFont(font);
        HideBatPowerFaultShowCheckBox->setTristate(false);

        verticalLayout_7->addWidget(HideBatPowerFaultShowCheckBox);

        groupBox_emergencyParam = new QGroupBox(dlgadminParamPage);
        groupBox_emergencyParam->setObjectName(QString::fromUtf8("groupBox_emergencyParam"));
        groupBox_emergencyParam->setGeometry(QRect(280, 180, 240, 62));
        groupBox_emergencyParam->setFont(font);
        verticalLayout = new QVBoxLayout(groupBox_emergencyParam);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        OldLampcheckBox = new QCheckBox(groupBox_emergencyParam);
        OldLampcheckBox->setObjectName(QString::fromUtf8("OldLampcheckBox"));
        OldLampcheckBox->setFont(font);

        verticalLayout->addWidget(OldLampcheckBox);

        pushButton_testMQTT = new QPushButton(dlgadminParamPage);
        pushButton_testMQTT->setObjectName(QString::fromUtf8("pushButton_testMQTT"));
        pushButton_testMQTT->setGeometry(QRect(40, 290, 130, 28));
        pushButton_testMQTT->setMinimumSize(QSize(0, 28));
        pushButton_testMQTT->setMaximumSize(QSize(16777215, 28));
        pushButton_testMQTT->setFont(font);

        retranslateUi(dlgadminParamPage);

        QMetaObject::connectSlotsByName(dlgadminParamPage);
    } // setupUi

    void retranslateUi(QDialog *dlgadminParamPage)
    {
        dlgadminParamPage->setWindowTitle(QApplication::translate("dlgadminParamPage", "\351\253\230\347\272\247\345\217\202\346\225\260", nullptr));
        MYcheckBox->setTitle(QApplication::translate("dlgadminParamPage", "\346\234\210\346\243\200\345\271\264\346\243\200\345\274\200\345\205\263", nullptr));
        MonthCheckBox->setText(QApplication::translate("dlgadminParamPage", "\347\246\201\346\255\242\346\234\210\346\243\200", nullptr));
        YearCheckBox->setText(QApplication::translate("dlgadminParamPage", "\347\246\201\346\255\242\345\271\264\346\243\200", nullptr));
        MYcheckTimeBox->setTitle(QApplication::translate("dlgadminParamPage", "\346\234\210\346\243\200\345\271\264\346\243\200\346\214\201\347\273\255\346\227\266\351\227\264", nullptr));
        label_1->setText(QApplication::translate("dlgadminParamPage", "\346\234\210\346\243\200\346\214\201\347\273\255:", nullptr));
        label_9->setText(QApplication::translate("dlgadminParamPage", "\347\247\222", nullptr));
        pushButton_month->setText(QApplication::translate("dlgadminParamPage", "\350\256\276\347\275\256", nullptr));
        label_2->setText(QApplication::translate("dlgadminParamPage", "\345\271\264\346\243\200\346\214\201\347\273\255:", nullptr));
        label_10->setText(QApplication::translate("dlgadminParamPage", "\345\210\206", nullptr));
        pushButton_year->setText(QApplication::translate("dlgadminParamPage", "\350\256\276\347\275\256", nullptr));
        SoundBox->setTitle(QApplication::translate("dlgadminParamPage", "\345\243\260\351\237\263\346\216\247\345\210\266", nullptr));
        SoundFCheckBox->setText(QApplication::translate("dlgadminParamPage", "\347\246\201\346\255\242\346\225\205\351\232\234\345\243\260", nullptr));
        SoundECheckBox->setText(QApplication::translate("dlgadminParamPage", "\347\246\201\346\255\242\345\272\224\346\200\245\345\243\260", nullptr));
        label->setText(QApplication::translate("dlgadminParamPage", "\351\253\230\347\272\247\345\217\202\346\225\260\346\230\276\347\244\272\346\210\252\346\255\242\346\227\266\351\227\264\357\274\232", nullptr));
        FirePointBox->setTitle(QApplication::translate("dlgadminParamPage", "\347\201\253\350\255\246\347\202\271", nullptr));
        HideLinkLineCheckBox->setText(QApplication::translate("dlgadminParamPage", "\351\232\220\350\227\217\345\205\263\350\201\224\347\272\277\346\230\276\347\244\272", nullptr));
        HideFirePointCheckBox->setText(QApplication::translate("dlgadminParamPage", "\351\232\220\350\227\217\347\201\253\350\255\246\347\202\271\346\230\276\347\244\272", nullptr));
        ShieldUnknownFirePointCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\346\234\252\347\237\245\347\201\253\350\255\246\347\202\271", nullptr));
        LightFaultBox->setTitle(QApplication::translate("dlgadminParamPage", "\345\205\211\346\272\220\346\225\205\351\232\234", nullptr));
        ShieldArrowLampLightFaultCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\346\240\207\345\277\227\347\201\257", nullptr));
        ShieldLightLampLightFaultCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\347\205\247\346\230\216\347\201\257", nullptr));
        ShieldUndergroundLampLightFaultCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\345\234\260\345\237\213\347\201\257", nullptr));
        ComFaultBox->setTitle(QApplication::translate("dlgadminParamPage", "\351\200\232\350\256\257\346\225\205\351\232\234", nullptr));
        ShieldLampComFaultCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\347\201\257\345\205\267\351\200\232\350\256\257\346\225\205\351\232\234", nullptr));
        ShieldCanDeviceComFaultCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\350\256\276\345\244\207\351\200\232\350\256\257\346\225\205\351\232\234", nullptr));
        ShieldLoginComFaultCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\261\217\350\224\275\346\263\250\345\206\214\345\257\274\350\207\264\347\232\204\351\200\232\350\256\257\346\225\205\351\232\234", nullptr));
        PowerFaultBox->setTitle(QApplication::translate("dlgadminParamPage", "\344\270\273\345\244\207\347\224\265\346\225\205\351\232\234", nullptr));
        ShieldMainPowerFaultEmergencyCheckBox->setText(QApplication::translate("dlgadminParamPage", "\345\201\234\346\255\242\344\270\273\347\224\265\346\225\205\351\232\234\345\272\224\346\200\245", nullptr));
        HideBatPowerFaultShowCheckBox->setText(QApplication::translate("dlgadminParamPage", "\351\232\220\350\227\217\345\244\207\347\224\265\346\225\205\351\232\234\346\230\276\347\244\272", nullptr));
        groupBox_emergencyParam->setTitle(QApplication::translate("dlgadminParamPage", "\345\272\224\346\200\245\345\217\202\346\225\260", nullptr));
        OldLampcheckBox->setText(QApplication::translate("dlgadminParamPage", "\346\227\247\347\201\257\345\205\267\346\226\271\345\220\221\346\216\247\345\210\266/\351\227\252\347\203\201\350\247\204\345\210\231", nullptr));
        pushButton_testMQTT->setText(QApplication::translate("dlgadminParamPage", "MQTT\346\265\213\350\257\225\347\225\214\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgadminParamPage: public Ui_dlgadminParamPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGADMINPARAMPAGE_H
