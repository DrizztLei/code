#ifndef SETSTANDARDWIDGET_H
#define SETSTANDARDWIDGET_H

#include "http.h"

// #include <QSqlQuery>
// #include <QSqlTableModel>
#include <QStandardItem>
#include <QWidget>
#include <vector>

namespace Ui
{
class setStandardWidget;
}

class setStandardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit setStandardWidget(QWidget *parent = 0);
    ~setStandardWidget();
    // static HTTP& getHTTP();
private slots:
    void on_submitPushButton_clicked();

private:
    Ui::setStandardWidget *ui;
    QStandardItemModel *model;
    const int size = 1;
    std::vector<HTTP> list;
    // static HTTP http;
};

#endif // SETSTANDARDWIDGET_H
