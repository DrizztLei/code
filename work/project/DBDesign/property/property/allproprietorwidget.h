#ifndef ALLPROPRIETORWIDGET_H
#define ALLPROPRIETORWIDGET_H

#include "http.h"

#include <QWidget>

namespace Ui
{
class AllProprietorWidget;
}

class AllProprietorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AllProprietorWidget(QWidget *parent = 0);
    ~AllProprietorWidget();
    static HTTP& getHTTP();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::AllProprietorWidget *ui;
    static HTTP http;
};

#endif // ALLPROPRIETORWIDGET_H
