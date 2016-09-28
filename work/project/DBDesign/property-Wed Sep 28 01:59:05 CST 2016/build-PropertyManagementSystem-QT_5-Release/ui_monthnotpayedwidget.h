/********************************************************************************
** Form generated from reading UI file 'monthnotpayedwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONTHNOTPAYEDWIDGET_H
#define UI_MONTHNOTPAYEDWIDGET_H

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

class Ui_MonthNotPayedWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *yearLabel;
    QLabel *label_3;
    QComboBox *MonthComboBox;
    QLabel *label_4;
    QComboBox *BuildingComboBox;
    QSpacerItem *horizontalSpacer;
    QPushButton *selectPushButton;
    QTableView *tableView;

    void setupUi(QWidget *MonthNotPayedWidget)
    {
        if (MonthNotPayedWidget->objectName().isEmpty())
            MonthNotPayedWidget->setObjectName(QStringLiteral("MonthNotPayedWidget"));
        MonthNotPayedWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MonthNotPayedWidget->sizePolicy().hasHeightForWidth());
        MonthNotPayedWidget->setSizePolicy(sizePolicy);
        MonthNotPayedWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(MonthNotPayedWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(MonthNotPayedWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(MonthNotPayedWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        yearLabel = new QLabel(MonthNotPayedWidget);
        yearLabel->setObjectName(QStringLiteral("yearLabel"));

        horizontalLayout->addWidget(yearLabel);

        label_3 = new QLabel(MonthNotPayedWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        MonthComboBox = new QComboBox(MonthNotPayedWidget);
        MonthComboBox->setObjectName(QStringLiteral("MonthComboBox"));

        horizontalLayout->addWidget(MonthComboBox);

        label_4 = new QLabel(MonthNotPayedWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        BuildingComboBox = new QComboBox(MonthNotPayedWidget);
        BuildingComboBox->setObjectName(QStringLiteral("BuildingComboBox"));

        horizontalLayout->addWidget(BuildingComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        selectPushButton = new QPushButton(MonthNotPayedWidget);
        selectPushButton->setObjectName(QStringLiteral("selectPushButton"));

        horizontalLayout->addWidget(selectPushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(MonthNotPayedWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(MonthNotPayedWidget);

        QMetaObject::connectSlotsByName(MonthNotPayedWidget);
    } // setupUi

    void retranslateUi(QWidget *MonthNotPayedWidget)
    {
        MonthNotPayedWidget->setWindowTitle(QApplication::translate("MonthNotPayedWidget", "Form", 0));
        label->setText(QApplication::translate("MonthNotPayedWidget", "\346\234\210\345\272\224\347\274\264\346\234\252\347\274\264", 0));
        label_2->setText(QApplication::translate("MonthNotPayedWidget", "\345\271\264\344\273\275\357\274\232", 0));
        yearLabel->setText(QString());
        label_3->setText(QApplication::translate("MonthNotPayedWidget", "\346\234\210\344\273\275\357\274\232", 0));
        label_4->setText(QApplication::translate("MonthNotPayedWidget", "\346\245\274\346\240\213\345\217\267\357\274\232", 0));
        selectPushButton->setText(QApplication::translate("MonthNotPayedWidget", "\346\237\245\350\257\242", 0));
    } // retranslateUi

};

namespace Ui {
    class MonthNotPayedWidget: public Ui_MonthNotPayedWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONTHNOTPAYEDWIDGET_H
