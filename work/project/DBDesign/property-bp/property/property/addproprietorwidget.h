#ifndef ADDPROPRIETORWIDGET_H
#define ADDPROPRIETORWIDGET_H

#include "http.h"

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QStandardItemModel>

namespace Ui
{
class AddProprietorWidget;
}

class AddProprietorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddProprietorWidget(QWidget *parent = 0);
    ~AddProprietorWidget();
    static HTTP& getHTTP();

private slots:
    void on_buildingComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::AddProprietorWidget *ui;
    QStandardItemModel* old;
    static HTTP http;
};

#endif // ADDPROPRIETORWIDGET_H
