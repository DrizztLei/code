#ifndef MONTHBILLWIDGET_H
#define MONTHBILLWIDGET_H
#include "http.h"

#include <QWidget>
// #include <QSqlQuery>
#include <QStandardItemModel>

#include <vector>

namespace Ui
{
class MonthBillWidget;
}

class MonthBillWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonthBillWidget(QWidget *parent = 0);
    ~MonthBillWidget();
    // static HTTP& getHTTP();

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::MonthBillWidget *ui;
    const int size = 2;
    std::vector<HTTP> list;
    // static HTTP http;
};

#endif // MONTHBILLWIDGET_H
