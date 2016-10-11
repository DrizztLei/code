/********************************************************************************
** Form generated from reading UI file 'recordmeterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDMETERDIALOG_H
#define UI_RECORDMETERDIALOG_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RecordMeterDialog
{
public:
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
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

    void setupUi(QDialog *RecordMeterDialog)
    {
        if (RecordMeterDialog->objectName().isEmpty())
            RecordMeterDialog->setObjectName(QStringLiteral("RecordMeterDialog"));
        RecordMeterDialog->resize(872, 620);
        formLayout = new QFormLayout(RecordMeterDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        tableView = new QTableView(RecordMeterDialog);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setMinimumSize(QSize(700, 600));

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(10, -1, -1, -1);
        label = new QLabel(RecordMeterDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        dateEdit = new QDateEdit(RecordMeterDialog);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setDateTime(QDateTime(QDate(2016, 7, 1), QTime(0, 0, 0)));
        dateEdit->setDate(QDate(2016, 7, 1));

        verticalLayout->addWidget(dateEdit);

        label_2 = new QLabel(RecordMeterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        buildingomboBox = new QComboBox(RecordMeterDialog);
        buildingomboBox->setObjectName(QStringLiteral("buildingomboBox"));

        verticalLayout->addWidget(buildingomboBox);

        label_3 = new QLabel(RecordMeterDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        roomComboBox = new QComboBox(RecordMeterDialog);
        roomComboBox->setObjectName(QStringLiteral("roomComboBox"));

        verticalLayout->addWidget(roomComboBox);

        waterLabel = new QLabel(RecordMeterDialog);
        waterLabel->setObjectName(QStringLiteral("waterLabel"));

        verticalLayout->addWidget(waterLabel);

        waterDoubleSpinBox = new QDoubleSpinBox(RecordMeterDialog);
        waterDoubleSpinBox->setObjectName(QStringLiteral("waterDoubleSpinBox"));
        waterDoubleSpinBox->setMaximum(100000);

        verticalLayout->addWidget(waterDoubleSpinBox);

        wattLabel = new QLabel(RecordMeterDialog);
        wattLabel->setObjectName(QStringLiteral("wattLabel"));

        verticalLayout->addWidget(wattLabel);

        wattDoubleSpinBox = new QDoubleSpinBox(RecordMeterDialog);
        wattDoubleSpinBox->setObjectName(QStringLiteral("wattDoubleSpinBox"));
        wattDoubleSpinBox->setMaximum(100000);

        verticalLayout->addWidget(wattDoubleSpinBox);

        gasLabel = new QLabel(RecordMeterDialog);
        gasLabel->setObjectName(QStringLiteral("gasLabel"));

        verticalLayout->addWidget(gasLabel);

        gasDoubleSpinBox = new QDoubleSpinBox(RecordMeterDialog);
        gasDoubleSpinBox->setObjectName(QStringLiteral("gasDoubleSpinBox"));
        gasDoubleSpinBox->setMaximum(100000);

        verticalLayout->addWidget(gasDoubleSpinBox);

        insertRecordPushButton = new QPushButton(RecordMeterDialog);
        insertRecordPushButton->setObjectName(QStringLiteral("insertRecordPushButton"));

        verticalLayout->addWidget(insertRecordPushButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        confirmPushButton = new QPushButton(RecordMeterDialog);
        confirmPushButton->setObjectName(QStringLiteral("confirmPushButton"));

        verticalLayout->addWidget(confirmPushButton);


        horizontalLayout->addLayout(verticalLayout);


        formLayout->setLayout(0, QFormLayout::LabelRole, horizontalLayout);


        retranslateUi(RecordMeterDialog);

        QMetaObject::connectSlotsByName(RecordMeterDialog);
    } // setupUi

    void retranslateUi(QDialog *RecordMeterDialog)
    {
        RecordMeterDialog->setWindowTitle(QApplication::translate("RecordMeterDialog", "MeterRecord", 0));
        label->setText(QApplication::translate("RecordMeterDialog", "Date", 0));
        dateEdit->setDisplayFormat(QApplication::translate("RecordMeterDialog", "yyyy-MM-dd", 0));
        label_2->setText(QApplication::translate("RecordMeterDialog", "BuildingID", 0));
        label_3->setText(QApplication::translate("RecordMeterDialog", "RoomID", 0));
        waterLabel->setText(QApplication::translate("RecordMeterDialog", "Water", 0));
        wattLabel->setText(QApplication::translate("RecordMeterDialog", "Watt", 0));
        gasLabel->setText(QApplication::translate("RecordMeterDialog", "Gas", 0));
        insertRecordPushButton->setText(QApplication::translate("RecordMeterDialog", "Add", 0));
        confirmPushButton->setText(QApplication::translate("RecordMeterDialog", "Submit", 0));
    } // retranslateUi

};

namespace Ui {
    class RecordMeterDialog: public Ui_RecordMeterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDMETERDIALOG_H
