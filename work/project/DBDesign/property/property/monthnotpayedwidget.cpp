#include "monthnotpayedwidget.h"
#include "ui_monthnotpayedwidget.h"

MonthNotPayedWidget::MonthNotPayedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonthNotPayedWidget)
{
    ui->setupUi(this);
}

MonthNotPayedWidget::~MonthNotPayedWidget()
{
    delete ui;
}
