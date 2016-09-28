/********************************************************************************
** Form generated from reading UI file 'delchargerwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELCHARGERWIDGET_H
#define UI_DELCHARGERWIDGET_H

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

class Ui_DelChargerWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;

    void setupUi(QWidget *DelChargerWidget)
    {
        if (DelChargerWidget->objectName().isEmpty())
            DelChargerWidget->setObjectName(QStringLiteral("DelChargerWidget"));
        DelChargerWidget->resize(600, 500);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DelChargerWidget->sizePolicy().hasHeightForWidth());
        DelChargerWidget->setSizePolicy(sizePolicy);
        DelChargerWidget->setMinimumSize(QSize(600, 500));
        gridLayout = new QGridLayout(DelChargerWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(DelChargerWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(DelChargerWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(DelChargerWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        pushButton = new QPushButton(DelChargerWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(DelChargerWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setMinimumSize(QSize(600, 500));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(DelChargerWidget);

        QMetaObject::connectSlotsByName(DelChargerWidget);
    } // setupUi

    void retranslateUi(QWidget *DelChargerWidget)
    {
        DelChargerWidget->setWindowTitle(QApplication::translate("DelChargerWidget", "Form", 0));
        label_2->setText(QApplication::translate("DelChargerWidget", "\345\210\240\351\231\244\346\224\266\350\264\271\344\272\272\345\221\230", 0));
        label->setText(QApplication::translate("DelChargerWidget", "\347\231\273\351\231\206ID\357\274\232", 0));
        pushButton->setText(QApplication::translate("DelChargerWidget", "\345\210\240\351\231\244", 0));
    } // retranslateUi

};

namespace Ui {
    class DelChargerWidget: public Ui_DelChargerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELCHARGERWIDGET_H
