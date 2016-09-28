#ifndef YEARBILLREPORTWIDGET_H
#define YEARBILLREPORTWIDGET_H

#include "http.h"

#include <QWidget>

namespace Ui
{
class YearBillReportWidget;
}

class YearBillReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit YearBillReportWidget(QWidget *parent = 0);
    ~YearBillReportWidget();
    // static HTTP& getHTTP();

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::YearBillReportWidget *ui;
    // static HTTP http;
};

#endif // YEARBILLREPORTWIDGET_H
