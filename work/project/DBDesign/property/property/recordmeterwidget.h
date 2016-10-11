#ifndef RECORDMETERWIDGET_H
#define RECORDMETERWIDGET_H
#include "http.h"

#include <QStandardItemModel>
#include <QWidget>
#include <vector>

namespace Ui
{
class RecordMeterWidget;
}

class RecordMeterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RecordMeterWidget(QWidget *parent = 0);
    ~RecordMeterWidget();
    // static HTTP& getHTTP();
private slots:
    void on_buildingomboBox_currentIndexChanged(int index);

    void on_insertRecordPushButton_clicked();

    void on_confirmPushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::RecordMeterWidget *ui;
    QStandardItemModel  *model;
    const int size = 8;
    std::vector<HTTP> list;
    // static HTTP http;
};

#endif // RECORDMETERWIDGET_H
