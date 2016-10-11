#ifndef SEASONBILLREPORTWIDGET_H
#define SEASONBILLREPORTWIDGET_H

#include "http.h"

#include <QWidget>
#include <vector>

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
    // static HTTP& getHTTP();
private slots:
    void on_selectPushButton_clicked();

private:
    Ui::SeasonBillReportWidget *ui;
    const int size = 2;
    std::vector<HTTP> list;
    // static HTTP http;
};

#endif // SEASONBILLREPORTWIDGET_H
