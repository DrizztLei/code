/********************************************************************************
** Form generated from reading UI file 'addchargerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCHARGERWIDGET_H
#define UI_ADDCHARGERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
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

class Ui_AddChargerWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *loginIdLineEdit;
    QLabel *label_2;
    QLineEdit *passWdLineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *addNewpushButton;
    QTableView *tableView;

    void setupUi(QWidget *AddChargerWidget)
    {
        if (AddChargerWidget->objectName().isEmpty())
            AddChargerWidget->setObjectName(QStringLiteral("AddChargerWidget"));
        AddChargerWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddChargerWidget->sizePolicy().hasHeightForWidth());
        AddChargerWidget->setSizePolicy(sizePolicy);
        AddChargerWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(AddChargerWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        label_4 = new QLabel(AddChargerWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(AddChargerWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        loginIdLineEdit = new QLineEdit(AddChargerWidget);
        loginIdLineEdit->setObjectName(QStringLiteral("loginIdLineEdit"));
        loginIdLineEdit->setMinimumSize(QSize(80, 0));
        loginIdLineEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(loginIdLineEdit);

        label_2 = new QLabel(AddChargerWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        passWdLineEdit = new QLineEdit(AddChargerWidget);
        passWdLineEdit->setObjectName(QStringLiteral("passWdLineEdit"));
        passWdLineEdit->setMinimumSize(QSize(80, 0));
        passWdLineEdit->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(passWdLineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        addNewpushButton = new QPushButton(AddChargerWidget);
        addNewpushButton->setObjectName(QStringLiteral("addNewpushButton"));

        horizontalLayout->addWidget(addNewpushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(AddChargerWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AddChargerWidget);

        QMetaObject::connectSlotsByName(AddChargerWidget);
    } // setupUi

    void retranslateUi(QWidget *AddChargerWidget)
    {
        AddChargerWidget->setWindowTitle(QApplication::translate("AddChargerWidget", "Form", 0));
        label_4->setText(QApplication::translate("AddChargerWidget", "\346\267\273\345\212\240\346\224\266\350\264\271\344\272\272\345\221\230", 0));
        label->setText(QApplication::translate("AddChargerWidget", "\347\231\273\351\231\206ID\357\274\232", 0));
        label_2->setText(QApplication::translate("AddChargerWidget", "\345\257\206\347\240\201\357\274\232", 0));
        addNewpushButton->setText(QApplication::translate("AddChargerWidget", "\346\267\273\345\212\240\347\224\250\346\210\267", 0));
    } // retranslateUi

};

namespace Ui {
    class AddChargerWidget: public Ui_AddChargerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCHARGERWIDGET_H
