#ifndef DELPROPRIETORWIDGET_H
#define DELPROPRIETORWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QStandardItemModel>
namespace Ui {
class DelProprietorWidget;
}

class DelProprietorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DelProprietorWidget(QWidget *parent = 0);
    ~DelProprietorWidget();

private slots:
    void on_buildComboBox_currentIndexChanged(int index);

    void on_roomComboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::DelProprietorWidget *ui;
};

#endif // DELPROPRIETORWIDGET_H
