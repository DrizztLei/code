#ifndef MONTHBILLWIDGET_H
#define MONTHBILLWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QStandardItemModel>
namespace Ui {
class MonthBillWidget;
}

class MonthBillWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonthBillWidget(QWidget *parent = 0);
    ~MonthBillWidget();

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::MonthBillWidget *ui;
};

#endif // MONTHBILLWIDGET_H
