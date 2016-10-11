/********************************************************************************
** Form generated from reading UI file 'contactdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTDIALOG_H
#define UI_CONTACTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_ContactDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *ContactDialog)
    {
        if (ContactDialog->objectName().isEmpty())
            ContactDialog->setObjectName(QStringLiteral("ContactDialog"));
        ContactDialog->resize(400, 300);
        label = new QLabel(ContactDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 40, 81, 31));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label_2 = new QLabel(ContactDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 110, 221, 31));
        QFont font1;
        font1.setFamily(QStringLiteral("Calibri"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_3 = new QLabel(ContactDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 160, 271, 31));
        label_3->setFont(font1);

        retranslateUi(ContactDialog);

        QMetaObject::connectSlotsByName(ContactDialog);
    } // setupUi

    void retranslateUi(QDialog *ContactDialog)
    {
        ContactDialog->setWindowTitle(QApplication::translate("ContactDialog", "Dialog", 0));
        label->setText(QApplication::translate("ContactDialog", "\350\201\224\347\263\273\346\210\221...", 0));
        label_2->setText(QApplication::translate("ContactDialog", "\345\274\200\345\217\221\350\200\205\357\274\232 \350\256\270\345\264\207\346\235\250", 0));
        label_3->setText(QApplication::translate("ContactDialog", "E-mail: xuchongyang@mail.sdu.edu.cn", 0));
    } // retranslateUi

};

namespace Ui {
    class ContactDialog: public Ui_ContactDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTDIALOG_H
