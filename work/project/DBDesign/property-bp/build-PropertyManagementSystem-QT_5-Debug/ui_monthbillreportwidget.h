/********************************************************************************
** Form generated from reading UI file 'monthbillreportwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONTHBILLREPORTWIDGET_H
#define UI_MONTHBILLREPORTWIDGET_H

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

class Ui_MonthBillReportWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *yearomboBox;
    QLabel *label;
    QComboBox *monthComboBox;
    QSpacerItem *horizontalSpacer;
    QComboBox *feeTypeComboBox;
    QPushButton *selectPushButton;
    QTableView *tableView;

    void setupUi(QWidget *MonthBillReportWidget)
    {
        if (MonthBillReportWidget->objectName().isEmpty())
            MonthBillReportWidget->setObjectName(QStringLiteral("MonthBillReportWidget"));
        MonthBillReportWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MonthBillReportWidget->sizePolicy().hasHeightForWidth());
        MonthBillReportWidget->setSizePolicy(sizePolicy);
        MonthBillReportWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(MonthBillReportWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(MonthBillReportWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(MonthBillReportWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        yearomboBox = new QComboBox(MonthBillReportWidget);
        yearomboBox->setObjectName(QStringLiteral("yearomboBox"));

        horizontalLayout->addWidget(yearomboBox);

        label = new QLabel(MonthBillReportWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        monthComboBox = new QComboBox(MonthBillReportWidget);
        monthComboBox->setObjectName(QStringLiteral("monthComboBox"));

        horizontalLayout->addWidget(monthComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        feeTypeComboBox = new QComboBox(MonthBillReportWidget);
        feeTypeComboBox->setObjectName(QStringLiteral("feeTypeComboBox"));

        horizontalLayout->addWidget(feeTypeComboBox);

        selectPushButton = new QPushButton(MonthBillReportWidget);
        selectPushButton->setObjectName(QStringLiteral("selectPushButton"));

        horizontalLayout->addWidget(selectPushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(MonthBillReportWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(MonthBillReportWidget);

        QMetaObject::connectSlotsByName(MonthBillReportWidget);
    } // setupUi

    void retranslateUi(QWidget *MonthBillReportWidget)
    {
        MonthBillReportWidget->setWindowTitle(QApplication::translate("MonthBillReportWidget", "Form", 0));
        label_3->setText(QApplication::translate("MonthBillReportWidget", "\346\234\210\345\272\246\346\212\245\350\241\250", 0));
        label_2->setText(QApplication::translate("MonthBillReportWidget", "\345\271\264\344\273\275\357\274\232", 0));
        label->setText(QApplication::translate("MonthBillReportWidget", "\346\234\210\344\273\275\357\274\232", 0));
        selectPushButton->setText(QApplication::translate("MonthBillReportWidget", "\346\237\245\350\257\242\346\212\245\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class MonthBillReportWidget: public Ui_MonthBillReportWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONTHBILLREPORTWIDGET_H
