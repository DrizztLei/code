#ifndef MONTHNOTPAYEDWIDGET_H
#define MONTHNOTPAYEDWIDGET_H

#include "http.h"

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
    static HTTP getHTTP();
private:
    Ui::MonthNotPayedWidget *ui;
    static HTTP http();
};

#endif // MONTHNOTPAYEDWIDGET_H
