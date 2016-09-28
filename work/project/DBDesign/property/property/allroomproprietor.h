#ifndef ALLROOMPROPRIETOR_H
#define ALLROOMPROPRIETOR_H

#include "http.h"

#include <QWidget>

namespace Ui
{
class AllRoomProprietor;
}

class AllRoomWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AllRoomWidget(QWidget *parent = 0);
    ~AllRoomWidget();
    static HTTP& getHTTP();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::AllRoomProprietor *ui;
    static HTTP http;
};

#endif // ALLROOMPROPRIETOR_H
