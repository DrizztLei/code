#ifndef ADDPROPRIETORWIDGET_H
#define ADDPROPRIETORWIDGET_H

#include "http.h"

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QSemaphore>

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
    // // static HTTP& getHTTP();
    enum class INFO{BUILDING , ID , ROOM , AREA , BOX , DEFAULT};

private slots:
    void on_buildingComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::AddProprietorWidget *ui;
    QStandardItemModel* old;
    QSemaphore sem;
    INFO info = INFO::DEFAULT;
    // // static HTTP http;
};

#endif // ADDPROPRIETORWIDGET_H
