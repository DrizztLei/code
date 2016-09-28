/********************************************************************************
** Form generated from reading UI file 'addproprietorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROPRIETORWIDGET_H
#define UI_ADDPROPRIETORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddProprietorWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QComboBox *comboBox;
    QLabel *label_7;
    QComboBox *comboBox_2;
    QLabel *label_8;
    QDateEdit *dateEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *AddProprietorWidget)
    {
        if (AddProprietorWidget->objectName().isEmpty())
            AddProprietorWidget->setObjectName(QStringLiteral("AddProprietorWidget"));
        AddProprietorWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddProprietorWidget->sizePolicy().hasHeightForWidth());
        AddProprietorWidget->setSizePolicy(sizePolicy);
        AddProprietorWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(AddProprietorWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(AddProprietorWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(30, -1, -1, -1);
        label = new QLabel(AddProprietorWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(AddProprietorWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(AddProprietorWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(AddProprietorWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(AddProprietorWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(lineEdit_2);

        label_4 = new QLabel(AddProprietorWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        lineEdit_3 = new QLineEdit(AddProprietorWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(lineEdit_3);

        label_5 = new QLabel(AddProprietorWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        lineEdit_4 = new QLineEdit(AddProprietorWidget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(AddProprietorWidget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(lineEdit_5);

        label_6 = new QLabel(AddProprietorWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        comboBox = new QComboBox(AddProprietorWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(comboBox);

        label_7 = new QLabel(AddProprietorWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        comboBox_2 = new QComboBox(AddProprietorWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(comboBox_2);

        label_8 = new QLabel(AddProprietorWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        dateEdit = new QDateEdit(AddProprietorWidget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setMaximumSize(QSize(120, 16777215));
        dateEdit->setDateTime(QDateTime(QDate(2015, 7, 1), QTime(0, 0, 0)));

        verticalLayout->addWidget(dateEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(AddProprietorWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 8);
        horizontalLayout->setStretch(1, 2);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(AddProprietorWidget);

        QMetaObject::connectSlotsByName(AddProprietorWidget);
    } // setupUi

    void retranslateUi(QWidget *AddProprietorWidget)
    {
        AddProprietorWidget->setWindowTitle(QApplication::translate("AddProprietorWidget", "Form", 0));
        label->setText(QApplication::translate("AddProprietorWidget", "\346\226\260\344\270\232\344\270\273\345\205\245\344\275\217", 0));
        label_2->setText(QApplication::translate("AddProprietorWidget", "\350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", 0));
        label_3->setText(QApplication::translate("AddProprietorWidget", "\345\247\223\345\220\215\357\274\232", 0));
        label_4->setText(QApplication::translate("AddProprietorWidget", "\345\267\245\344\275\234\345\215\225\344\275\215\357\274\232", 0));
        label_5->setText(QApplication::translate("AddProprietorWidget", "\346\211\213\346\234\272\345\217\267\357\274\232", 0));
        label_6->setText(QApplication::translate("AddProprietorWidget", "\346\245\274\346\240\213\345\217\267\357\274\232", 0));
        label_7->setText(QApplication::translate("AddProprietorWidget", "\346\210\277\345\261\213\345\217\267\357\274\232", 0));
        label_8->setText(QApplication::translate("AddProprietorWidget", "\345\205\245\344\275\217\346\227\245\346\234\237\357\274\232", 0));
        dateEdit->setDisplayFormat(QApplication::translate("AddProprietorWidget", "yyyy-MM-dd", 0));
        pushButton->setText(QApplication::translate("AddProprietorWidget", "\347\241\256\350\256\244\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class AddProprietorWidget: public Ui_AddProprietorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROPRIETORWIDGET_H
