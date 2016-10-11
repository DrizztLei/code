#ifndef DELCHARGERWIDGET_H
#define DELCHARGERWIDGET_H

#include "http.h"

#include <QWidget>
// #include <QSqlQuery>
#include <QStandardItemModel>

#include <vector>

namespace Ui
{
    class DelChargerWidget;
}

class DelChargerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelChargerWidget(QWidget *parent = 0);
    ~DelChargerWidget();
    // static HTTP& getHTTP();
private slots:
    void on_pushButton_clicked();

private:
    Ui::DelChargerWidget *ui;
    QStandardItemModel  *model;
    // static HTTP http;
    std::vector<HTTP> list;
    const int size = 3;
};

#endif // DELCHARGERWIDGET_H
