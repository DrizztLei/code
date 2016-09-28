/********************************************************************************
** Form generated from reading UI file 'addproprietorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPROPRIETORWIDGET_H
#define UI_ADDPROPRIETORWIDGET_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
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
    QTableView *proprietorTableView;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *proprietorLineEdit;
    QLabel *label_3;
    QLineEdit *nameLineEdit;
    QLabel *label_4;
    QLineEdit *organizationLineEdit;
    QLabel *label_5;
    QLineEdit *phone1LineEdit;
    QLineEdit *phone2Line;
    QLabel *label_6;
    QComboBox *buildingComboBox;
    QLabel *label_7;
    QComboBox *roomComboBox;
    QLabel *label_8;
    QDateTimeEdit *ownDateDateTimeEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *AddProprietorWidget)
    {
        if (AddProprietorWidget->objectName().isEmpty())
            AddProprietorWidget->setObjectName(QStringLiteral("AddProprietorWidget"));
        AddProprietorWidget->resize(1030, 600);
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
        proprietorTableView = new QTableView(AddProprietorWidget);
        proprietorTableView->setObjectName(QStringLiteral("proprietorTableView"));

        horizontalLayout->addWidget(proprietorTableView);

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

        proprietorLineEdit = new QLineEdit(AddProprietorWidget);
        proprietorLineEdit->setObjectName(QStringLiteral("proprietorLineEdit"));
        proprietorLineEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(proprietorLineEdit);

        label_3 = new QLabel(AddProprietorWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        nameLineEdit = new QLineEdit(AddProprietorWidget);
        nameLineEdit->setObjectName(QStringLiteral("nameLineEdit"));
        nameLineEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(nameLineEdit);

        label_4 = new QLabel(AddProprietorWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        organizationLineEdit = new QLineEdit(AddProprietorWidget);
        organizationLineEdit->setObjectName(QStringLiteral("organizationLineEdit"));
        organizationLineEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(organizationLineEdit);

        label_5 = new QLabel(AddProprietorWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        phone1LineEdit = new QLineEdit(AddProprietorWidget);
        phone1LineEdit->setObjectName(QStringLiteral("phone1LineEdit"));
        phone1LineEdit->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(phone1LineEdit);

        phone2Line = new QLineEdit(AddProprietorWidget);
        phone2Line->setObjectName(QStringLiteral("phone2Line"));
        phone2Line->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(phone2Line);

        label_6 = new QLabel(AddProprietorWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        buildingComboBox = new QComboBox(AddProprietorWidget);
        buildingComboBox->setObjectName(QStringLiteral("buildingComboBox"));
        buildingComboBox->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(buildingComboBox);

        label_7 = new QLabel(AddProprietorWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        roomComboBox = new QComboBox(AddProprietorWidget);
        roomComboBox->setObjectName(QStringLiteral("roomComboBox"));
        roomComboBox->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(roomComboBox);

        label_8 = new QLabel(AddProprietorWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        ownDateDateTimeEdit = new QDateTimeEdit(AddProprietorWidget);
        ownDateDateTimeEdit->setObjectName(QStringLiteral("ownDateDateTimeEdit"));
        ownDateDateTimeEdit->setMaximumSize(QSize(120, 16777215));
        ownDateDateTimeEdit->setDateTime(QDateTime(QDate(2016, 7, 1), QTime(0, 0, 0)));
        ownDateDateTimeEdit->setDate(QDate(2016, 7, 1));
        ownDateDateTimeEdit->setMaximumDate(QDate(7999, 12, 30));
        ownDateDateTimeEdit->setCalendarPopup(false);

        verticalLayout->addWidget(ownDateDateTimeEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(AddProprietorWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMaximumSize(QSize(120, 16777215));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


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
        ownDateDateTimeEdit->setDisplayFormat(QApplication::translate("AddProprietorWidget", "yyyy-MM-dd", 0));
        pushButton->setText(QApplication::translate("AddProprietorWidget", "\347\241\256\350\256\244\346\267\273\345\212\240", 0));
    } // retranslateUi

};

namespace Ui {
    class AddProprietorWidget: public Ui_AddProprietorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPROPRIETORWIDGET_H
