/********************************************************************************
** Form generated from reading UI file 'shouldchargedwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOULDCHARGEDWIDGET_H
#define UI_SHOULDCHARGEDWIDGET_H

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

class Ui_ShouldChargedWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_3;
    QComboBox *comboBox_3;
    QLabel *label_4;
    QComboBox *comboBox_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QTableView *tableView;

    void setupUi(QWidget *ShouldChargedWidget)
    {
        if (ShouldChargedWidget->objectName().isEmpty())
            ShouldChargedWidget->setObjectName(QStringLiteral("ShouldChargedWidget"));
        ShouldChargedWidget->resize(800, 600);
        ShouldChargedWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(ShouldChargedWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_5 = new QLabel(ShouldChargedWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(ShouldChargedWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(ShouldChargedWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        label_2 = new QLabel(ShouldChargedWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(ShouldChargedWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout->addWidget(comboBox_2);

        label_3 = new QLabel(ShouldChargedWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        comboBox_3 = new QComboBox(ShouldChargedWidget);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        horizontalLayout->addWidget(comboBox_3);

        label_4 = new QLabel(ShouldChargedWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        comboBox_4 = new QComboBox(ShouldChargedWidget);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        horizontalLayout->addWidget(comboBox_4);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(ShouldChargedWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(ShouldChargedWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(ShouldChargedWidget);

        QMetaObject::connectSlotsByName(ShouldChargedWidget);
    } // setupUi

    void retranslateUi(QWidget *ShouldChargedWidget)
    {
        ShouldChargedWidget->setWindowTitle(QApplication::translate("ShouldChargedWidget", "Form", 0));
        label_5->setText(QApplication::translate("ShouldChargedWidget", "\345\272\224\346\224\266\350\264\271\347\224\250\346\212\245\350\241\250", 0));
        label->setText(QApplication::translate("ShouldChargedWidget", "\346\212\245\350\241\250\347\261\273\345\236\213\357\274\232", 0));
        label_2->setText(QApplication::translate("ShouldChargedWidget", "\345\271\264\344\273\275\357\274\232", 0));
        label_3->setText(QApplication::translate("ShouldChargedWidget", "\345\255\243\345\272\246\357\274\232", 0));
        label_4->setText(QApplication::translate("ShouldChargedWidget", "\346\234\210\344\273\275\357\274\232", 0));
        pushButton->setText(QApplication::translate("ShouldChargedWidget", "\346\237\245\347\234\213\346\212\245\350\241\250", 0));
    } // retranslateUi

};

namespace Ui {
    class ShouldChargedWidget: public Ui_ShouldChargedWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOULDCHARGEDWIDGET_H
