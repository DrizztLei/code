#ifndef ADDCHARGERWIDGET_H
#define ADDCHARGERWIDGET_H

#include "http.h"

#include <QWidget>
#include <QStandardItemModel>
#include <vector>

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
    // static HTTP& getHTTP();

private slots:
    void on_addNewpushButton_clicked();
private:
    Ui::AddChargerWidget *ui;
    std::vector<HTTP> list;
    const int size = 1;
    // static HTTP http;
};

#endif // ADDCHARGERWIDGET_H
