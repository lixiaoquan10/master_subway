/********************************************************************************
** Form generated from reading UI file 'dlgdeviceForbidFault.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDEVICEFORBIDFAULT_H
#define UI_DLGDEVICEFORBIDFAULT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgdeviceForbidFault
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_close;

    void setupUi(QDialog *dlgdeviceForbidFault)
    {
        if (dlgdeviceForbidFault->objectName().isEmpty())
            dlgdeviceForbidFault->setObjectName(QString::fromUtf8("dlgdeviceForbidFault"));
        dlgdeviceForbidFault->resize(670, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dlgdeviceForbidFault->sizePolicy().hasHeightForWidth());
        dlgdeviceForbidFault->setSizePolicy(sizePolicy);
        dlgdeviceForbidFault->setMinimumSize(QSize(0, 0));
        dlgdeviceForbidFault->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(12);
        dlgdeviceForbidFault->setFont(font);
        dlgdeviceForbidFault->setStyleSheet(QString::fromUtf8("border: 1px solid black; "));
        dlgdeviceForbidFault->setInputMethodHints(Qt::ImhNone);
        verticalLayout = new QVBoxLayout(dlgdeviceForbidFault);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label = new QLabel(dlgdeviceForbidFault);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("border: 0px solid black; "));

        horizontalLayout_2->addWidget(label);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_2);

        tableView = new QTableView(dlgdeviceForbidFault);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setFont(font);
        tableView->setStyleSheet(QString::fromUtf8("border: 0px solid black; "));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_close = new QPushButton(dlgdeviceForbidFault);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        pushButton_close->setMinimumSize(QSize(60, 35));

        horizontalLayout->addWidget(pushButton_close);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(dlgdeviceForbidFault);

        QMetaObject::connectSlotsByName(dlgdeviceForbidFault);
    } // setupUi

    void retranslateUi(QDialog *dlgdeviceForbidFault)
    {
        dlgdeviceForbidFault->setWindowTitle(QApplication::translate("dlgdeviceForbidFault", "Dialog", nullptr));
        label->setText(QApplication::translate("dlgdeviceForbidFault", "\347\246\201\347\224\250\347\201\257\345\205\267\345\210\227\350\241\250", nullptr));
        pushButton_close->setText(QApplication::translate("dlgdeviceForbidFault", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgdeviceForbidFault: public Ui_dlgdeviceForbidFault {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGDEVICEFORBIDFAULT_H
