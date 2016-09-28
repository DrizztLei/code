#ifndef SETSTANDARDWIDGET_H
#define SETSTANDARDWIDGET_H
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QWidget>

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

private slots:
    void on_submitPushButton_clicked();

private:
    Ui::setStandardWidget *ui;
    QSqlTableModel *model;
};

#endif // SETSTANDARDWIDGET_H
