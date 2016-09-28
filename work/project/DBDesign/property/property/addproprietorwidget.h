#ifndef ADDPROPRIETORWIDGET_H
#define ADDPROPRIETORWIDGET_H

#include "http.h"

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QSemaphore>
#include <vector>

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

private slots:
    void on_buildingComboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();

private:
    Ui::AddProprietorWidget *ui;
    QStandardItemModel* old;
    HTTP BUILDING , ID , ROOM  , AREA;
    std::vector<HTTP> list;
    QSemaphore sem;
    // INFO info = INFO::DEFAULT;
};

#endif // ADDPROPRIETORWIDGET_H
