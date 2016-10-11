/********************************************************************************
** Form generated from reading UI file 'recordmeterwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDMETERWIDGET_H
#define UI_RECORDMETERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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

class Ui_RecordMeterWidget
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QLabel *label;
    QDateEdit *dateEdit;
    QLabel *label_2;
    QComboBox *buildingomboBox;
    QLabel *label_3;
    QComboBox *roomComboBox;
    QLabel *waterLabel;
    QDoubleSpinBox *waterDoubleSpinBox;
    QLabel *wattLabel;
    QDoubleSpinBox *wattDoubleSpinBox;
    QLabel *gasLabel;
    QDoubleSpinBox *gasDoubleSpinBox;
    QPushButton *insertRecordPushButton;
    QSpacerItem *verticalSpacer;
    QPushButton *confirmPushButton;

    void setupUi(QWidget *RecordMeterWidget)
    {
        if (RecordMeterWidget->objectName().isEmpty())
            RecordMeterWidget->setObjectName(QStringLiteral("RecordMeterWidget"));
        RecordMeterWidget->setWindowModality(Qt::NonModal);
        RecordMeterWidget->resize(831, 620);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RecordMeterWidget->sizePolicy().hasHeightForWidth());
        RecordMeterWidget->setSizePolicy(sizePolicy);
        RecordMeterWidget->setMinimumSize(QSize(831, 620));
        RecordMeterWidget->setAutoFillBackground(false);
        gridLayout = new QGridLayout(RecordMeterWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        tableView = new QTableView(RecordMeterWidget);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setMinimumSize(QSize(700, 600));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(10, -1, -1, -1);
        label_4 = new QLabel(RecordMeterWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(12);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        label = new QLabel(RecordMeterWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        dateEdit = new QDateEdit(RecordMeterWidget);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setDateTime(QDateTime(QDate(2015, 7, 1), QTime(0, 0, 0)));

        verticalLayout->addWidget(dateEdit);

        label_2 = new QLabel(RecordMeterWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        buildingomboBox = new QComboBox(RecordMeterWidget);
        buildingomboBox->setObjectName(QStringLiteral("buildingomboBox"));

        verticalLayout->addWidget(buildingomboBox);

        label_3 = new QLabel(RecordMeterWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        roomComboBox = new QComboBox(RecordMeterWidget);
        roomComboBox->setObjectName(QStringLiteral("roomComboBox"));

        verticalLayout->addWidget(roomComboBox);

        waterLabel = new QLabel(RecordMeterWidget);
        waterLabel->setObjectName(QStringLiteral("waterLabel"));

        verticalLayout->addWidget(waterLabel);

        waterDoubleSpinBox = new QDoubleSpinBox(RecordMeterWidget);
        waterDoubleSpinBox->setObjectName(QStringLiteral("waterDoubleSpinBox"));
        waterDoubleSpinBox->setMaximum(100000);

        verticalLayout->addWidget(waterDoubleSpinBox);

        wattLabel = new QLabel(RecordMeterWidget);
        wattLabel->setObjectName(QStringLiteral("wattLabel"));

        verticalLayout->addWidget(wattLabel);

        wattDoubleSpinBox = new QDoubleSpinBox(RecordMeterWidget);
        wattDoubleSpinBox->setObjectName(QStringLiteral("wattDoubleSpinBox"));
        wattDoubleSpinBox->setMaximum(100000);

        verticalLayout->addWidget(wattDoubleSpinBox);

        gasLabel = new QLabel(RecordMeterWidget);
        gasLabel->setObjectName(QStringLiteral("gasLabel"));

        verticalLayout->addWidget(gasLabel);

        gasDoubleSpinBox = new QDoubleSpinBox(RecordMeterWidget);
        gasDoubleSpinBox->setObjectName(QStringLiteral("gasDoubleSpinBox"));
        gasDoubleSpinBox->setMaximum(100000);

        verticalLayout->addWidget(gasDoubleSpinBox);

        insertRecordPushButton = new QPushButton(RecordMeterWidget);
        insertRecordPushButton->setObjectName(QStringLiteral("insertRecordPushButton"));

        verticalLayout->addWidget(insertRecordPushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        confirmPushButton = new QPushButton(RecordMeterWidget);
        confirmPushButton->setObjectName(QStringLiteral("confirmPushButton"));

        verticalLayout->addWidget(confirmPushButton);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(RecordMeterWidget);

        QMetaObject::connectSlotsByName(RecordMeterWidget);
    } // setupUi

    void retranslateUi(QWidget *RecordMeterWidget)
    {
        RecordMeterWidget->setWindowTitle(QApplication::translate("RecordMeterWidget", "Form", 0));
        label_4->setText(QApplication::translate("RecordMeterWidget", "\346\212\204\350\241\250\346\225\260\346\215\256\345\275\225\345\205\245", 0));
        label->setText(QApplication::translate("RecordMeterWidget", "\346\212\204\350\241\250\346\227\245\346\234\237\357\274\232", 0));
        dateEdit->setDisplayFormat(QApplication::translate("RecordMeterWidget", "yyyy-MM-dd", 0));
        label_2->setText(QApplication::translate("RecordMeterWidget", "\346\245\274\346\240\213\345\217\267\357\274\232", 0));
        label_3->setText(QApplication::translate("RecordMeterWidget", "\346\210\277\345\261\213\345\217\267\357\274\232", 0));
        waterLabel->setText(QApplication::translate("RecordMeterWidget", "\346\260\264\350\241\250\350\257\273\346\225\260\357\274\232", 0));
        wattLabel->setText(QApplication::translate("RecordMeterWidget", "\347\224\265\350\241\250\350\257\273\346\225\260\357\274\232", 0));
        gasLabel->setText(QApplication::translate("RecordMeterWidget", "\347\205\244\346\260\224\350\257\273\346\225\260\357\274\232", 0));
        insertRecordPushButton->setText(QApplication::translate("RecordMeterWidget", "\346\267\273\345\212\240", 0));
        confirmPushButton->setText(QApplication::translate("RecordMeterWidget", "\347\241\256\350\256\244\345\275\225\345\205\245", 0));
    } // retranslateUi

};

namespace Ui {
    class RecordMeterWidget: public Ui_RecordMeterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDMETERWIDGET_H
