/********************************************************************************
** Form generated from reading UI file 'yearbillreportwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_YEARBILLREPORTWIDGET_H
#define UI_YEARBILLREPORTWIDGET_H

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

class Ui_YearBillReportWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *yearomboBox;
    QSpacerItem *horizontalSpacer;
    QComboBox *feeTypeComboBox;
    QPushButton *selectPushButton;
    QTableView *tableView;

    void setupUi(QWidget *YearBillReportWidget)
    {
        if (YearBillReportWidget->objectName().isEmpty())
            YearBillReportWidget->setObjectName(QStringLiteral("YearBillReportWidget"));
        YearBillReportWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(YearBillReportWidget->sizePolicy().hasHeightForWidth());
        YearBillReportWidget->setSizePolicy(sizePolicy);
        YearBillReportWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(YearBillReportWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(YearBillReportWidget);
        label->setObjectName(QStringLiteral("label"));
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
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(YearBillReportWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        yearomboBox = new QComboBox(YearBillReportWidget);
        yearomboBox->setObjectName(QStringLiteral("yearomboBox"));

        horizontalLayout->addWidget(yearomboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        feeTypeComboBox = new QComboBox(YearBillReportWidget);
        feeTypeComboBox->setObjectName(QStringLiteral("feeTypeComboBox"));

        horizontalLayout->addWidget(feeTypeComboBox);

        selectPushButton = new QPushButton(YearBillReportWidget);
        selectPushButton->setObjectName(QStringLiteral("selectPushButton"));

        horizontalLayout->addWidget(selectPushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(YearBillReportWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(YearBillReportWidget);

        QMetaObject::connectSlotsByName(YearBillReportWidget);
    } // setupUi

    void retranslateUi(QWidget *YearBillReportWidget)
    {
        YearBillReportWidget->setWindowTitle(QApplication::translate("YearBillReportWidget", "Form", 0));
        label->setText(QApplication::translate("YearBillReportWidget", "\345\271\264\345\272\246\346\212\245\350\241\250", 0));
        label_2->setText(QApplication::translate("YearBillReportWidget", "\345\271\264\344\273\275\357\274\232", 0));
        selectPushButton->setText(QApplication::translate("YearBillReportWidget", "\346\237\245\350\257\242\346\212\245\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class YearBillReportWidget: public Ui_YearBillReportWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_YEARBILLREPORTWIDGET_H
