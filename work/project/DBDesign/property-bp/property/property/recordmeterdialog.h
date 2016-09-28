#ifndef RECORDMETERDIALOG_H
#define RECORDMETERDIALOG_H

#include "http.h"

#include <QDialog>
#include <QSqlQuery>
#include <QStandardItemModel>

namespace Ui
{
class RecordMeterDialog;
}

class RecordMeterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecordMeterDialog(QWidget *parent = 0);
    ~RecordMeterDialog();
    static HTTP& getHTTP();
private slots:
    void on_buildingomboBox_currentIndexChanged(int index);

    void on_insertRecordPushButton_clicked();


    void on_confirmPushButton_clicked();

private:
    Ui::RecordMeterDialog *ui;
    QStandardItemModel  *model;
    static HTTP http;
};

#endif // RECORDMETERDIALOG_H
