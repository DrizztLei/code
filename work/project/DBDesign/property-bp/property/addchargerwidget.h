#ifndef ADDCHARGERWIDGET_H
#define ADDCHARGERWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QStandardItemModel>
namespace Ui
{
class AddChargerWidget;
}

class AddChargerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AddChargerWidget(QWidget *parent = 0);
    ~AddChargerWidget();

private slots:
    void on_addNewpushButton_clicked();

private:
    Ui::AddChargerWidget *ui;
};

#endif // ADDCHARGERWIDGET_H
