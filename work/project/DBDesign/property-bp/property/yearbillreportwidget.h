#ifndef YEARBILLREPORTWIDGET_H
#define YEARBILLREPORTWIDGET_H

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

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::YearBillReportWidget *ui;
};

#endif // YEARBILLREPORTWIDGET_H
