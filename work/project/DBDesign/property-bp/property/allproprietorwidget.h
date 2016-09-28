#ifndef ALLPROPRIETORWIDGET_H
#define ALLPROPRIETORWIDGET_H

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

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::AllProprietorWidget *ui;
};

#endif // ALLPROPRIETORWIDGET_H
