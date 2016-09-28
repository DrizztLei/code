#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "http.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(QWidget *parent,QString id);

    static HTTP& getHTTP();

    /*
    {
        return MainWindow::http;
    }
    */

    ~MainWindow();

private slots:
    //RECORD_METER
    void importMeterDataSlot();
    void inputMeterDataSlot();
    //CHARGE_FEE
    void userPaySlot();
    void allUserBillSlot();
    void monthShouldPayNotPaySlot();
    //REPORT_FORMS
    void monthBillSlot();
    void seasonBillSlot();
    void yearBillSlot();
    //ADD_DEL_PROPRIETOR
    void addProprietorSlot();
    void delProprietorSlot();
    void showAllProprietorSlot();
    void showAllRoomSlot();
    //ADD_DEL_CHARGER
    void addChargerSlot();
    void delChargerSlot();
    //SET_STANDARD
    void setStandardSlot();
    //help
    void contactSlot();
    void aboutSlot();
private:
    void setActions(QList<QString> list);
    void setCentralContent(QWidget* w);
    Ui::MainWindow *ui;
    QString loginId;
    //RECORD_METER
    QMenu* meterMenu;
    QAction *importMeterData;
    QAction *inputMeterData;
    //CHARGE_FEE
    QMenu* chargingMenu;
    QAction *userPay;
    QAction *allUserBill;
    QAction *shouldPayNotPay;
    //REPORT_FORMS
    QMenu* reportMenu;
    QAction* monthBillAction;
    QAction* seasonBillAction;
    QAction* yearBillAction;
    //ADD_DEL_PROPRIETOR
    QMenu* proprietorMenu;
    QAction *addProprietor;
    QAction *delProprietor;
    QAction *showAllProprietor;
    QAction *showAllRoom;
    //ADD_DEL_CHARGER
    QMenu* chargerMenu;
    QAction *addCharger;
    QAction *delCharger;
    //SET_STANDARD
    QMenu* standardMenu;
    QAction *setStandard;

    //ADD_DEL_BUILDING
    //ADD_DEL_ROOM
    QMenu* help;
    QAction *about;
    QAction *contact;
    static HTTP http;
};

#endif // MAINWINDOW_H

