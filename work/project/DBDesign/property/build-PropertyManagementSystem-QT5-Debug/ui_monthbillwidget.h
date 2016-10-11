/********************************************************************************
** Form generated from reading UI file 'monthbillwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONTHBILLWIDGET_H
#define UI_MONTHBILLWIDGET_H

#include <QtCore/QDate>
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MonthBillWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QDateEdit *startDateEdit;
    QLabel *label_5;
    QDateEdit *stopdateEdit;
    QLabel *label_4;
    QComboBox *BuildingComboBox;
    QSpacerItem *horizontalSpacer;
    QComboBox *feeTypecomboBox;
    QPushButton *selectPushButton;
    QTableView *tableView;

    void setupUi(QWidget *MonthBillWidget)
    {
        if (MonthBillWidget->objectName().isEmpty())
            MonthBillWidget->setObjectName(QStringLiteral("MonthBillWidget"));
        MonthBillWidget->resize(842, 600);
        MonthBillWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(MonthBillWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(MonthBillWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
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
        label_3 = new QLabel(MonthBillWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        startDateEdit = new QDateEdit(MonthBillWidget);
        startDateEdit->setObjectName(QStringLiteral("startDateEdit"));
        startDateEdit->setDateTime(QDateTime(QDate(2016, 1, 1), QTime(0, 0, 0)));
        startDateEdit->setDate(QDate(2016, 1, 1));

        horizontalLayout->addWidget(startDateEdit);

        label_5 = new QLabel(MonthBillWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);

        stopdateEdit = new QDateEdit(MonthBillWidget);
        stopdateEdit->setObjectName(QStringLiteral("stopdateEdit"));
        stopdateEdit->setDateTime(QDateTime(QDate(2017, 1, 1), QTime(0, 0, 0)));
        stopdateEdit->setDate(QDate(2017, 1, 1));

        horizontalLayout->addWidget(stopdateEdit);

        label_4 = new QLabel(MonthBillWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        BuildingComboBox = new QComboBox(MonthBillWidget);
        BuildingComboBox->setObjectName(QStringLiteral("BuildingComboBox"));

        horizontalLayout->addWidget(BuildingComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        feeTypecomboBox = new QComboBox(MonthBillWidget);
        feeTypecomboBox->setObjectName(QStringLiteral("feeTypecomboBox"));
        feeTypecomboBox->setMinimumSize(QSize(100, 0));

        horizontalLayout->addWidget(feeTypecomboBox);

        selectPushButton = new QPushButton(MonthBillWidget);
        selectPushButton->setObjectName(QStringLiteral("selectPushButton"));

        horizontalLayout->addWidget(selectPushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(MonthBillWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(MonthBillWidget);

        QMetaObject::connectSlotsByName(MonthBillWidget);
    } // setupUi

    void retranslateUi(QWidget *MonthBillWidget)
    {
        MonthBillWidget->setWindowTitle(QApplication::translate("MonthBillWidget", "Form", 0));
        label->setText(QApplication::translate("MonthBillWidget", "\346\234\210\350\264\246\345\215\225", 0));
        label_3->setText(QApplication::translate("MonthBillWidget", "\350\265\267\345\247\213\346\227\245\346\234\237\357\274\232", 0));
        startDateEdit->setDisplayFormat(QApplication::translate("MonthBillWidget", "yyyy-MM-dd", 0));
        label_5->setText(QApplication::translate("MonthBillWidget", "\347\273\223\346\235\237\346\227\245\346\234\237", 0));
        stopdateEdit->setDisplayFormat(QApplication::translate("MonthBillWidget", "yyyy-MM-dd", 0));
        label_4->setText(QApplication::translate("MonthBillWidget", "\346\245\274\346\240\213\345\217\267\357\274\232", 0));
        selectPushButton->setText(QApplication::translate("MonthBillWidget", "\346\237\245\350\257\242", 0));
    } // retranslateUi

};

namespace Ui {
    class MonthBillWidget: public Ui_MonthBillWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONTHBILLWIDGET_H
