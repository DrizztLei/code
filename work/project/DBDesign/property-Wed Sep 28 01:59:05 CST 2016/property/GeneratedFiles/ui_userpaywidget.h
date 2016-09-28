/********************************************************************************
** Form generated from reading UI file 'userpaywidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPAYWIDGET_H
#define UI_USERPAYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserPayWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *buildingComboBox;
    QLabel *label_2;
    QComboBox *roomComboBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer;
    QPushButton *SelectPushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QTableView *tableView;

    void setupUi(QWidget *UserPayWidget)
    {
        if (UserPayWidget->objectName().isEmpty())
            UserPayWidget->setObjectName(QStringLiteral("UserPayWidget"));
        UserPayWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UserPayWidget->sizePolicy().hasHeightForWidth());
        UserPayWidget->setSizePolicy(sizePolicy);
        UserPayWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(UserPayWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_7 = new QLabel(UserPayWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(UserPayWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        buildingComboBox = new QComboBox(UserPayWidget);
        buildingComboBox->setObjectName(QStringLiteral("buildingComboBox"));

        horizontalLayout->addWidget(buildingComboBox);

        label_2 = new QLabel(UserPayWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        roomComboBox = new QComboBox(UserPayWidget);
        roomComboBox->setObjectName(QStringLiteral("roomComboBox"));

        horizontalLayout->addWidget(roomComboBox);

        label_3 = new QLabel(UserPayWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        label_4 = new QLabel(UserPayWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        label_5 = new QLabel(UserPayWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        label_6 = new QLabel(UserPayWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        SelectPushButton = new QPushButton(UserPayWidget);
        SelectPushButton->setObjectName(QStringLiteral("SelectPushButton"));

        horizontalLayout->addWidget(SelectPushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(UserPayWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(UserPayWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(UserPayWidget);

        QMetaObject::connectSlotsByName(UserPayWidget);
    } // setupUi

    void retranslateUi(QWidget *UserPayWidget)
    {
        UserPayWidget->setWindowTitle(QApplication::translate("UserPayWidget", "Form", 0));
        label_7->setText(QApplication::translate("UserPayWidget", "\344\270\232\344\270\273\344\272\244\350\264\271", 0));
        label->setText(QApplication::translate("UserPayWidget", "\346\245\274\346\240\213\345\217\267\357\274\232", 0));
        label_2->setText(QApplication::translate("UserPayWidget", "\346\210\277\345\261\213\345\217\267\357\274\232", 0));
        label_3->setText(QApplication::translate("UserPayWidget", "\344\270\232\344\270\273\350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", 0));
        label_4->setText(QApplication::translate("UserPayWidget", "0", 0));
        label_5->setText(QApplication::translate("UserPayWidget", "\344\270\232\344\270\273\345\247\223\345\220\215\357\274\232", 0));
        label_6->setText(QApplication::translate("UserPayWidget", "TextLabel", 0));
        SelectPushButton->setText(QApplication::translate("UserPayWidget", "\346\237\245\350\257\242", 0));
        pushButton_2->setText(QApplication::translate("UserPayWidget", "\345\267\262\347\274\264\350\264\271", 0));
    } // retranslateUi

};

namespace Ui {
    class UserPayWidget: public Ui_UserPayWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPAYWIDGET_H
