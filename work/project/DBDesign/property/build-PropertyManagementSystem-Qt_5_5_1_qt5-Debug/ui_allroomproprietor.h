/********************************************************************************
** Form generated from reading UI file 'allroomproprietor.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALLROOMPROPRIETOR_H
#define UI_ALLROOMPROPRIETOR_H

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

class Ui_AllRoomProprietor
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QTableView *buildingTableView;
    QTableView *roomTableView;

    void setupUi(QWidget *AllRoomProprietor)
    {
        if (AllRoomProprietor->objectName().isEmpty())
            AllRoomProprietor->setObjectName(QStringLiteral("AllRoomProprietor"));
        AllRoomProprietor->resize(800, 600);
        AllRoomProprietor->setMinimumSize(QSize(800, 600));
        gridLayout = new QGridLayout(AllRoomProprietor);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(AllRoomProprietor);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label->setFont(font);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(AllRoomProprietor);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox = new QComboBox(AllRoomProprietor);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buildingTableView = new QTableView(AllRoomProprietor);
        buildingTableView->setObjectName(QStringLiteral("buildingTableView"));

        horizontalLayout->addWidget(buildingTableView);

        roomTableView = new QTableView(AllRoomProprietor);
        roomTableView->setObjectName(QStringLiteral("roomTableView"));

        horizontalLayout->addWidget(roomTableView);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 7);

        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(AllRoomProprietor);

        QMetaObject::connectSlotsByName(AllRoomProprietor);
    } // setupUi

    void retranslateUi(QWidget *AllRoomProprietor)
    {
        AllRoomProprietor->setWindowTitle(QApplication::translate("AllRoomProprietor", "Form", 0));
        label->setText(QApplication::translate("AllRoomProprietor", "\346\210\277\345\261\213\344\277\241\346\201\257", 0));
        label_2->setText(QApplication::translate("AllRoomProprietor", "\346\245\274\346\240\213", 0));
    } // retranslateUi

};

namespace Ui {
    class AllRoomProprietor: public Ui_AllRoomProprietor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALLROOMPROPRIETOR_H
