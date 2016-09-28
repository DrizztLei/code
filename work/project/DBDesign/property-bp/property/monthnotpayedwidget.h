#ifndef MONTHNOTPAYEDWIDGET_H
#define MONTHNOTPAYEDWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QStandardItemModel>
namespace Ui
{
class MonthNotPayedWidget;
}

class MonthNotPayedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonthNotPayedWidget(QWidget *parent = 0);
    ~MonthNotPayedWidget();

private:
    Ui::MonthNotPayedWidget *ui;
};

#endif // MONTHNOTPAYEDWIDGET_H
