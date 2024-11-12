/********************************************************************************
** Form generated from reading UI file 'mqttTest.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MQTTTEST_H
#define UI_MQTTTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_mqttTest
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEditHost;
    QLabel *label_2;
    QSpinBox *spinBoxPort;
    QPushButton *buttonConnect;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEditTopic;
    QLabel *label_4;
    QPushButton *buttonPublish;
    QPushButton *buttonSubscribe;
    QPushButton *buttonPing;
    QLineEdit *lineEditMessage;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *editLog;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *buttonClear;
    QPushButton *buttonQuit;

    void setupUi(QDialog *mqttTest)
    {
        if (mqttTest->objectName().isEmpty())
            mqttTest->setObjectName(QString::fromUtf8("mqttTest"));
        mqttTest->resize(800, 600);
        mqttTest->setMaximumSize(QSize(800, 600));
        mqttTest->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(mqttTest);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(mqttTest);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEditHost = new QLineEdit(mqttTest);
        lineEditHost->setObjectName(QString::fromUtf8("lineEditHost"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditHost);

        label_2 = new QLabel(mqttTest);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        spinBoxPort = new QSpinBox(mqttTest);
        spinBoxPort->setObjectName(QString::fromUtf8("spinBoxPort"));
        spinBoxPort->setMaximum(99999);
        spinBoxPort->setValue(1883);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxPort);


        horizontalLayout->addLayout(formLayout);

        buttonConnect = new QPushButton(mqttTest);
        buttonConnect->setObjectName(QString::fromUtf8("buttonConnect"));

        horizontalLayout->addWidget(buttonConnect);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(mqttTest);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEditTopic = new QLineEdit(mqttTest);
        lineEditTopic->setObjectName(QString::fromUtf8("lineEditTopic"));

        gridLayout->addWidget(lineEditTopic, 0, 1, 1, 1);

        label_4 = new QLabel(mqttTest);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        buttonPublish = new QPushButton(mqttTest);
        buttonPublish->setObjectName(QString::fromUtf8("buttonPublish"));

        gridLayout->addWidget(buttonPublish, 1, 2, 1, 1);

        buttonSubscribe = new QPushButton(mqttTest);
        buttonSubscribe->setObjectName(QString::fromUtf8("buttonSubscribe"));

        gridLayout->addWidget(buttonSubscribe, 0, 2, 1, 1);

        buttonPing = new QPushButton(mqttTest);
        buttonPing->setObjectName(QString::fromUtf8("buttonPing"));

        gridLayout->addWidget(buttonPing, 2, 2, 1, 1);

        lineEditMessage = new QLineEdit(mqttTest);
        lineEditMessage->setObjectName(QString::fromUtf8("lineEditMessage"));

        gridLayout->addWidget(lineEditMessage, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        groupBox = new QGroupBox(mqttTest);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        editLog = new QPlainTextEdit(groupBox);
        editLog->setObjectName(QString::fromUtf8("editLog"));

        horizontalLayout_2->addWidget(editLog);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonClear = new QPushButton(mqttTest);
        buttonClear->setObjectName(QString::fromUtf8("buttonClear"));

        horizontalLayout_3->addWidget(buttonClear);

        buttonQuit = new QPushButton(mqttTest);
        buttonQuit->setObjectName(QString::fromUtf8("buttonQuit"));
        buttonQuit->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(buttonQuit);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(mqttTest);

        QMetaObject::connectSlotsByName(mqttTest);
    } // setupUi

    void retranslateUi(QDialog *mqttTest)
    {
        mqttTest->setWindowTitle(QString());
        label->setText(QApplication::translate("mqttTest", "\346\234\215\345\212\241\345\231\250:", nullptr));
        lineEditHost->setText(QApplication::translate("mqttTest", "broker.hivemq.com", nullptr));
        label_2->setText(QApplication::translate("mqttTest", "\347\253\257\345\217\243:", nullptr));
        buttonConnect->setText(QApplication::translate("mqttTest", "\350\277\236\346\216\245", nullptr));
        label_3->setText(QApplication::translate("mqttTest", "\344\270\273\351\242\230:", nullptr));
        lineEditTopic->setText(QApplication::translate("mqttTest", "test_mqtt", nullptr));
        label_4->setText(QApplication::translate("mqttTest", "\346\225\260\346\215\256:", nullptr));
        buttonPublish->setText(QApplication::translate("mqttTest", "\345\217\221\351\200\201", nullptr));
        buttonSubscribe->setText(QApplication::translate("mqttTest", "\350\256\242\351\230\205", nullptr));
        buttonPing->setText(QApplication::translate("mqttTest", "Ping", nullptr));
        lineEditMessage->setText(QApplication::translate("mqttTest", "This is a test message", nullptr));
        groupBox->setTitle(QApplication::translate("mqttTest", "\347\212\266\346\200\201\344\277\241\346\201\257", nullptr));
        buttonClear->setText(QApplication::translate("mqttTest", "\346\270\205\347\251\272\347\212\266\346\200\201\344\277\241\346\201\257", nullptr));
        buttonQuit->setText(QApplication::translate("mqttTest", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mqttTest: public Ui_mqttTest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MQTTTEST_H
