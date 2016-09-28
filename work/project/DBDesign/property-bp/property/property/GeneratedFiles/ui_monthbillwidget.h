/********************************************************************************
** Form generated from reading UI file 'monthbillwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONTHBILLWIDGET_H
#define UI_MONTHBILLWIDGET_H

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

class Ui_MonthBillWidget
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

    void setupUi(QWidget *MonthBillWidget)
    {
        if (MonthBillWidget->objectName().isEmpty())
            MonthBillWidget->setObjectName(QStringLiteral("MonthBillWidget"));
        MonthBillWidget->resize(800, 600);
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
        label_2 = new QLabel(MonthBillWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        yearLabel = new QLabel(MonthBillWidget);
        yearLabel->setObjectName(QStringLiteral("yearLabel"));

        horizontalLayout->addWidget(yearLabel);

        label_3 = new QLabel(MonthBillWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        MonthComboBox = new QComboBox(MonthBillWidget);
        MonthComboBox->setObjectName(QStringLiteral("MonthComboBox"));

        horizontalLayout->addWidget(MonthComboBox);

        label_4 = new QLabel(MonthBillWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        BuildingComboBox = new QComboBox(MonthBillWidget);
        BuildingComboBox->setObjectName(QStringLiteral("BuildingComboBox"));

        horizontalLayout->addWidget(BuildingComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

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
        label_2->setText(QApplication::translate("MonthBillWidget", "\345\271\264\344\273\275\357\274\232", 0));
        yearLabel->setText(QApplication::translate("MonthBillWidget", "TextLabel", 0));
        label_3->setText(QApplication::translate("MonthBillWidget", "\346\234\210\344\273\275\357\274\232", 0));
        label_4->setText(QApplication::translate("MonthBillWidget", "\346\245\274\346\240\213\345\217\267\357\274\232", 0));
        selectPushButton->setText(QApplication::translate("MonthBillWidget", "\346\237\245\350\257\242", 0));
    } // retranslateUi

};

namespace Ui {
    class MonthBillWidget: public Ui_MonthBillWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONTHBILLWIDGET_H
