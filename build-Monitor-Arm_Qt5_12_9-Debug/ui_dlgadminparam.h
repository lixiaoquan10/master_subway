/********************************************************************************
** Form generated from reading UI file 'dlgadminparam.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGADMINPARAM_H
#define UI_DLGADMINPARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgadminParam
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_message;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *m_LocalNumber;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *m_rPowerCode;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *m_btnCancel;
    QPushButton *m_btnOk;

    void setupUi(QDialog *dlgadminParam)
    {
        if (dlgadminParam->objectName().isEmpty())
            dlgadminParam->setObjectName(QString::fromUtf8("dlgadminParam"));
        dlgadminParam->resize(300, 180);
        dlgadminParam->setMaximumSize(QSize(300, 180));
        QFont font;
        font.setPointSize(15);
        dlgadminParam->setFont(font);
        dlgadminParam->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 255, 255);"));
        verticalLayout = new QVBoxLayout(dlgadminParam);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_message = new QLabel(dlgadminParam);
        label_message->setObjectName(QString::fromUtf8("label_message"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        label_message->setFont(font1);

        horizontalLayout_4->addWidget(label_message);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(dlgadminParam);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(65, 30));
        label_2->setMaximumSize(QSize(65, 30));

        horizontalLayout->addWidget(label_2);

        m_LocalNumber = new QLineEdit(dlgadminParam);
        m_LocalNumber->setObjectName(QString::fromUtf8("m_LocalNumber"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(m_LocalNumber->sizePolicy().hasHeightForWidth());
        m_LocalNumber->setSizePolicy(sizePolicy);
        m_LocalNumber->setMinimumSize(QSize(190, 30));
        m_LocalNumber->setMaximumSize(QSize(190, 30));
        m_LocalNumber->setEchoMode(QLineEdit::Normal);
        m_LocalNumber->setReadOnly(true);

        horizontalLayout->addWidget(m_LocalNumber);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(dlgadminParam);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(65, 30));
        label->setMaximumSize(QSize(65, 30));

        horizontalLayout_2->addWidget(label);

        m_rPowerCode = new QLineEdit(dlgadminParam);
        m_rPowerCode->setObjectName(QString::fromUtf8("m_rPowerCode"));
        sizePolicy.setHeightForWidth(m_rPowerCode->sizePolicy().hasHeightForWidth());
        m_rPowerCode->setSizePolicy(sizePolicy);
        m_rPowerCode->setMinimumSize(QSize(190, 30));
        m_rPowerCode->setMaximumSize(QSize(190, 30));
        m_rPowerCode->setEchoMode(QLineEdit::Normal);

        horizontalLayout_2->addWidget(m_rPowerCode);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        m_btnCancel = new QPushButton(dlgadminParam);
        m_btnCancel->setObjectName(QString::fromUtf8("m_btnCancel"));
        m_btnCancel->setMinimumSize(QSize(125, 30));
        m_btnCancel->setMaximumSize(QSize(125, 30));

        horizontalLayout_3->addWidget(m_btnCancel);

        m_btnOk = new QPushButton(dlgadminParam);
        m_btnOk->setObjectName(QString::fromUtf8("m_btnOk"));
        m_btnOk->setMinimumSize(QSize(125, 30));
        m_btnOk->setMaximumSize(QSize(125, 30));

        horizontalLayout_3->addWidget(m_btnOk);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(dlgadminParam);

        QMetaObject::connectSlotsByName(dlgadminParam);
    } // setupUi

    void retranslateUi(QDialog *dlgadminParam)
    {
        dlgadminParam->setWindowTitle(QApplication::translate("dlgadminParam", "\347\224\250\346\210\267\347\231\273\345\275\225", nullptr));
        label_message->setText(QApplication::translate("dlgadminParam", "\351\253\230\347\272\247\345\217\202\346\225\260", nullptr));
        label_2->setText(QApplication::translate("dlgadminParam", "\346\234\254\346\234\272\344\273\243\347\240\201:", nullptr));
        m_LocalNumber->setPlaceholderText(QString());
        label->setText(QApplication::translate("dlgadminParam", "\346\235\203\351\231\220\344\273\243\347\240\201:", nullptr));
        m_rPowerCode->setPlaceholderText(QString());
        m_btnCancel->setText(QApplication::translate("dlgadminParam", "\345\217\226\346\266\210", nullptr));
        m_btnOk->setText(QApplication::translate("dlgadminParam", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgadminParam: public Ui_dlgadminParam {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGADMINPARAM_H
