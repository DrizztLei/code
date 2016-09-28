/********************************************************************************
** Form generated from reading UI file 'setstandardwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETSTANDARDWIDGET_H
#define UI_SETSTANDARDWIDGET_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDoubleSpinBox>
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

class Ui_setStandardWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QDateEdit *startDateDateEdit;
    QLabel *label_3;
    QDoubleSpinBox *waterStandarddoubleSpinBox;
    QLabel *label_4;
    QDoubleSpinBox *wattStandarddoubleSpinBox;
    QLabel *label_5;
    QDoubleSpinBox *gasStandarddoubleSpinBox;
    QLabel *label_6;
    QDoubleSpinBox *tvStandarddoubleSpinBox;
    QLabel *label_7;
    QDoubleSpinBox *propStandarddoubleSpinBox;
    QLabel *label_8;
    QDoubleSpinBox *mortageStandarddoubleSpinBox;
    QSpacerItem *verticalSpacer;
    QPushButton *submitPushButton;

    void setupUi(QWidget *setStandardWidget)
    {
        if (setStandardWidget->objectName().isEmpty())
            setStandardWidget->setObjectName(QStringLiteral("setStandardWidget"));
        setStandardWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(setStandardWidget->sizePolicy().hasHeightForWidth());
        setStandardWidget->setSizePolicy(sizePolicy);
        setStandardWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(setStandardWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView = new QTableView(setStandardWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(setStandardWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(setStandardWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        startDateDateEdit = new QDateEdit(setStandardWidget);
        startDateDateEdit->setObjectName(QStringLiteral("startDateDateEdit"));
        startDateDateEdit->setDateTime(QDateTime(QDate(2016, 1, 1), QTime(0, 0, 0)));
        startDateDateEdit->setDate(QDate(2016, 1, 1));

        verticalLayout->addWidget(startDateDateEdit);

        label_3 = new QLabel(setStandardWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        waterStandarddoubleSpinBox = new QDoubleSpinBox(setStandardWidget);
        waterStandarddoubleSpinBox->setObjectName(QStringLiteral("waterStandarddoubleSpinBox"));

        verticalLayout->addWidget(waterStandarddoubleSpinBox);

        label_4 = new QLabel(setStandardWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        wattStandarddoubleSpinBox = new QDoubleSpinBox(setStandardWidget);
        wattStandarddoubleSpinBox->setObjectName(QStringLiteral("wattStandarddoubleSpinBox"));

        verticalLayout->addWidget(wattStandarddoubleSpinBox);

        label_5 = new QLabel(setStandardWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        gasStandarddoubleSpinBox = new QDoubleSpinBox(setStandardWidget);
        gasStandarddoubleSpinBox->setObjectName(QStringLiteral("gasStandarddoubleSpinBox"));

        verticalLayout->addWidget(gasStandarddoubleSpinBox);

        label_6 = new QLabel(setStandardWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        tvStandarddoubleSpinBox = new QDoubleSpinBox(setStandardWidget);
        tvStandarddoubleSpinBox->setObjectName(QStringLiteral("tvStandarddoubleSpinBox"));

        verticalLayout->addWidget(tvStandarddoubleSpinBox);

        label_7 = new QLabel(setStandardWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout->addWidget(label_7);

        propStandarddoubleSpinBox = new QDoubleSpinBox(setStandardWidget);
        propStandarddoubleSpinBox->setObjectName(QStringLiteral("propStandarddoubleSpinBox"));

        verticalLayout->addWidget(propStandarddoubleSpinBox);

        label_8 = new QLabel(setStandardWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout->addWidget(label_8);

        mortageStandarddoubleSpinBox = new QDoubleSpinBox(setStandardWidget);
        mortageStandarddoubleSpinBox->setObjectName(QStringLiteral("mortageStandarddoubleSpinBox"));
        mortageStandarddoubleSpinBox->setMaximum(1e+06);

        verticalLayout->addWidget(mortageStandarddoubleSpinBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        submitPushButton = new QPushButton(setStandardWidget);
        submitPushButton->setObjectName(QStringLiteral("submitPushButton"));

        verticalLayout->addWidget(submitPushButton);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(setStandardWidget);

        QMetaObject::connectSlotsByName(setStandardWidget);
    } // setupUi

    void retranslateUi(QWidget *setStandardWidget)
    {
        setStandardWidget->setWindowTitle(QApplication::translate("setStandardWidget", "Form", 0));
        label->setText(QApplication::translate("setStandardWidget", "\350\256\276\345\256\232\344\277\241\346\201\257\346\224\266\350\264\271\346\240\207\345\207\206", 0));
        label_2->setText(QApplication::translate("setStandardWidget", "\350\265\267\346\225\210\346\227\245\346\234\237", 0));
        startDateDateEdit->setDisplayFormat(QApplication::translate("setStandardWidget", "yyyy-MM-dd", 0));
        label_3->setText(QApplication::translate("setStandardWidget", "\346\260\264\350\264\271\345\215\225\344\273\267(\345\205\203/\347\253\213\346\226\271\347\261\263)", 0));
        label_4->setText(QApplication::translate("setStandardWidget", "\347\224\265\350\264\271\345\215\225\344\273\267\357\274\210\345\205\203/\345\272\246\357\274\211", 0));
        label_5->setText(QApplication::translate("setStandardWidget", "\347\205\244\346\260\224\345\215\225\344\273\267\357\274\210\345\205\203/\347\253\213\346\226\271\347\261\263\357\274\211", 0));
        label_6->setText(QApplication::translate("setStandardWidget", "\346\234\211\347\272\277\347\224\265\350\247\206\350\264\271\357\274\210\345\205\203/\346\234\210\357\274\211", 0));
        label_7->setText(QApplication::translate("setStandardWidget", "\347\211\251\344\270\232\350\264\271\347\224\250\345\215\225\344\273\267\357\274\210\345\205\203/\345\271\263\346\226\271\347\261\263\302\267\346\234\210\357\274\211", 0));
        label_8->setText(QApplication::translate("setStandardWidget", "\346\234\210\346\210\277\350\264\267\357\274\210\345\205\203/\346\234\210\357\274\211", 0));
        submitPushButton->setText(QApplication::translate("setStandardWidget", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class setStandardWidget: public Ui_setStandardWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETSTANDARDWIDGET_H
