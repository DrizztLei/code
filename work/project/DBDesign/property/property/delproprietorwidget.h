#ifndef DELPROPRIETORWIDGET_H
#define DELPROPRIETORWIDGET_H

#include "http.h"

#include <QWidget>
// #include <QSqlQuery>
#include <QStandardItemModel>
#include <vector>

namespace Ui
{
class DelProprietorWidget;
}

class DelProprietorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelProprietorWidget(QWidget *parent = 0);
    ~DelProprietorWidget();
    // static HTTP& getHTTP();
private slots:
    void on_buildComboBox_currentIndexChanged(int index);
    void on_roomComboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();

private:
    Ui::DelProprietorWidget *ui;
    std::vector<HTTP> list;
    int const size = 14;
    // static HTTP http;
};

#endif // DELPROPRIETORWIDGET_H
