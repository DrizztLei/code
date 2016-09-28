#ifndef MONTHBILLREPORTWIDGET_H
#define MONTHBILLREPORTWIDGET_H

#include <QWidget>

namespace Ui {
class MonthBillReportWidget;
}

class MonthBillReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MonthBillReportWidget(QWidget *parent = 0);
    ~MonthBillReportWidget();

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::MonthBillReportWidget *ui;
};

#endif // MONTHBILLREPORTWIDGET_H
