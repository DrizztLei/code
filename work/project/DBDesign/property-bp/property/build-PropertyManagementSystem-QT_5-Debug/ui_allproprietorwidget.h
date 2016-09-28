/********************************************************************************
** Form generated from reading UI file 'allproprietorwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLPROPRIETORWIDGET_H
#define UI_ALLPROPRIETORWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AllProprietorWidget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    QTableView *tableView;

    void setupUi(QWidget *AllProprietorWidget)
    {
        if (AllProprietorWidget->objectName().isEmpty())
            AllProprietorWidget->setObjectName(QStringLiteral("AllProprietorWidget"));
        AllProprietorWidget->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AllProprietorWidget->sizePolicy().hasHeightForWidth());
        AllProprietorWidget->setSizePolicy(sizePolicy);
        AllProprietorWidget->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(AllProprietorWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(AllProprietorWidget);
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
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(AllProprietorWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox = new QComboBox(AllProprietorWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableView = new QTableView(AllProprietorWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AllProprietorWidget);

        QMetaObject::connectSlotsByName(AllProprietorWidget);
    } // setupUi

    void retranslateUi(QWidget *AllProprietorWidget)
    {
        AllProprietorWidget->setWindowTitle(QApplication::translate("AllProprietorWidget", "Form", 0));
        label->setText(QApplication::translate("AllProprietorWidget", "\344\270\232\344\270\273\344\277\241\346\201\257", 0));
        label_2->setText(QApplication::translate("AllProprietorWidget", "\346\245\274\345\217\267", 0));
    } // retranslateUi

};

namespace Ui {
    class AllProprietorWidget: public Ui_AllProprietorWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLPROPRIETORWIDGET_H
