#ifndef SEASONBILLREPORTWIDGET_H
#define SEASONBILLREPORTWIDGET_H

#include <QWidget>

namespace Ui
{
class SeasonBillReportWidget;
}

class SeasonBillReportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SeasonBillReportWidget(QWidget *parent = 0);
    ~SeasonBillReportWidget();

private slots:
    void on_selectPushButton_clicked();

private:
    Ui::SeasonBillReportWidget *ui;
};

#endif // SEASONBILLREPORTWIDGET_H
