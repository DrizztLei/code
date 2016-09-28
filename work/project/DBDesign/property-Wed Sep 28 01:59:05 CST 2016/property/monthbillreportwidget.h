#ifndef MONTHBILLREPORTWIDGET_H
#define MONTHBILLREPORTWIDGET_H

#include "http.h"

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
    // static HTTP& getHTTP();
private slots:
    void on_selectPushButton_clicked();

private:
    Ui::MonthBillReportWidget *ui;
    // static HTTP http;
};

#endif // MONTHBILLREPORTWIDGET_H
