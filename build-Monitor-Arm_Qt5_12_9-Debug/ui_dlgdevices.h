/********************************************************************************
** Form generated from reading UI file 'dlgdevices.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGDEVICES_H
#define UI_DLGDEVICES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <view/ctableview.h>

QT_BEGIN_NAMESPACE

class Ui_dlgDevices
{
public:
    QVBoxLayout *verticalLayout;
    CTableView *tableView;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLineEdit *m_page;
    QPushButton *previousPage_Button;
    QPushButton *nextPage_Button;
    QScrollBar *pageScrollBar;
    QLabel *label;
    QLineEdit *m_deviceNumber;
    QPushButton *ReadBatteryStatus_Button;

    void setupUi(QDialog *dlgDevices)
    {
        if (dlgDevices->objectName().isEmpty())
            dlgDevices->setObjectName(QString::fromUtf8("dlgDevices"));
        dlgDevices->resize(1060, 484);
        QFont font;
        font.setPointSize(12);
        dlgDevices->setFont(font);
        verticalLayout = new QVBoxLayout(dlgDevices);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tableView = new CTableView(dlgDevices);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setMaximumSize(QSize(1366, 768));
        tableView->setFont(font);
        tableView->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(tableView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(dlgDevices);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 30));
        label_2->setMaximumSize(QSize(70, 30));
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        m_page = new QLineEdit(dlgDevices);
        m_page->setObjectName(QString::fromUtf8("m_page"));
        m_page->setMinimumSize(QSize(50, 30));
        m_page->setMaximumSize(QSize(50, 30));
        m_page->setFont(font);
        m_page->setReadOnly(true);

        horizontalLayout->addWidget(m_page);

        previousPage_Button = new QPushButton(dlgDevices);
        previousPage_Button->setObjectName(QString::fromUtf8("previousPage_Button"));
        previousPage_Button->setMinimumSize(QSize(0, 30));
        previousPage_Button->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        previousPage_Button->setFont(font1);
        previousPage_Button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(previousPage_Button);

        nextPage_Button = new QPushButton(dlgDevices);
        nextPage_Button->setObjectName(QString::fromUtf8("nextPage_Button"));
        nextPage_Button->setMinimumSize(QSize(0, 30));
        nextPage_Button->setMaximumSize(QSize(16777215, 30));
        nextPage_Button->setFont(font1);
        nextPage_Button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(nextPage_Button);

        pageScrollBar = new QScrollBar(dlgDevices);
        pageScrollBar->setObjectName(QString::fromUtf8("pageScrollBar"));
        pageScrollBar->setMinimumSize(QSize(200, 20));
        pageScrollBar->setFont(font);
        pageScrollBar->setMinimum(1);
        pageScrollBar->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(pageScrollBar);

        label = new QLabel(dlgDevices);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(0, 30));
        label->setMaximumSize(QSize(70, 30));
        label->setFont(font);

        horizontalLayout->addWidget(label);

        m_deviceNumber = new QLineEdit(dlgDevices);
        m_deviceNumber->setObjectName(QString::fromUtf8("m_deviceNumber"));
        m_deviceNumber->setMinimumSize(QSize(50, 30));
        m_deviceNumber->setMaximumSize(QSize(50, 30));
        m_deviceNumber->setFont(font);
        m_deviceNumber->setReadOnly(true);

        horizontalLayout->addWidget(m_deviceNumber);

        ReadBatteryStatus_Button = new QPushButton(dlgDevices);
        ReadBatteryStatus_Button->setObjectName(QString::fromUtf8("ReadBatteryStatus_Button"));
        ReadBatteryStatus_Button->setMinimumSize(QSize(0, 30));
        ReadBatteryStatus_Button->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        ReadBatteryStatus_Button->setFont(font2);
        ReadBatteryStatus_Button->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(ReadBatteryStatus_Button);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(dlgDevices);

        QMetaObject::connectSlotsByName(dlgDevices);
    } // setupUi

    void retranslateUi(QDialog *dlgDevices)
    {
        dlgDevices->setWindowTitle(QApplication::translate("dlgDevices", "Dialog", nullptr));
        label_2->setText(QApplication::translate("dlgDevices", "\351\241\265\347\240\201:", nullptr));
        previousPage_Button->setText(QApplication::translate("dlgDevices", "\344\270\212\344\270\200\351\241\265", nullptr));
        nextPage_Button->setText(QApplication::translate("dlgDevices", "\344\270\213\344\270\200\351\241\265", nullptr));
        label->setText(QApplication::translate("dlgDevices", "\347\201\257\345\205\267\346\225\260\351\207\217:", nullptr));
        ReadBatteryStatus_Button->setText(QApplication::translate("dlgDevices", "\350\257\273\345\217\226\347\224\265\346\261\240\347\224\265\351\207\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlgDevices: public Ui_dlgDevices {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGDEVICES_H
