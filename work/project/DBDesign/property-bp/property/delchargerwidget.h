#ifndef DELCHARGERWIDGET_H
#define DELCHARGERWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QStandardItemModel>

namespace Ui {
class DelChargerWidget;
}

class DelChargerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelChargerWidget(QWidget *parent = 0);
    ~DelChargerWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DelChargerWidget *ui;
     QStandardItemModel  *model;
};

#endif // DELCHARGERWIDGET_H
