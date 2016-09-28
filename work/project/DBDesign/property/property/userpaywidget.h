#ifndef USERPAYWIDGET_H
#define USERPAYWIDGET_H

#include "http.h"

#include <QSqlQuery>
#include <QStandardItemModel>
#include <QWidget>
#include <QDebug>

namespace Ui
{
class UserPayWidget;
}

class UserPayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserPayWidget(QWidget *parent = 0);
    ~UserPayWidget();
    static HTTP& getHTTP();
private slots:
    void on_buildingComboBox_currentIndexChanged(int index);

    void on_roomComboBox_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_SelectPushButton_clicked();

    void on_pushButton_clicked();

private:
    void printTable();
    Ui::UserPayWidget *ui;
    static HTTP http;
};

#endif // USERPAYWIDGET_H
