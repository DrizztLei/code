/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 19), // "importMeterDataSlot"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 18), // "inputMeterDataSlot"
QT_MOC_LITERAL(4, 51, 11), // "userPaySlot"
QT_MOC_LITERAL(5, 63, 15), // "allUserBillSlot"
QT_MOC_LITERAL(6, 79, 24), // "monthShouldPayNotPaySlot"
QT_MOC_LITERAL(7, 104, 17), // "shouldChargedSlot"
QT_MOC_LITERAL(8, 122, 18), // "acturalChargedSlot"
QT_MOC_LITERAL(9, 141, 14), // "notChargedSlot"
QT_MOC_LITERAL(10, 156, 17), // "addProprietorSlot"
QT_MOC_LITERAL(11, 174, 17), // "delProprietorSlot"
QT_MOC_LITERAL(12, 192, 14), // "addChargerSlot"
QT_MOC_LITERAL(13, 207, 14), // "delChargerSlot"
QT_MOC_LITERAL(14, 222, 15), // "setStandardSlot"
QT_MOC_LITERAL(15, 238, 11), // "contactSlot"
QT_MOC_LITERAL(16, 250, 9) // "aboutSlot"

    },
    "MainWindow\0importMeterDataSlot\0\0"
    "inputMeterDataSlot\0userPaySlot\0"
    "allUserBillSlot\0monthShouldPayNotPaySlot\0"
    "shouldChargedSlot\0acturalChargedSlot\0"
    "notChargedSlot\0addProprietorSlot\0"
    "delProprietorSlot\0addChargerSlot\0"
    "delChargerSlot\0setStandardSlot\0"
    "contactSlot\0aboutSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->importMeterDataSlot(); break;
        case 1: _t->inputMeterDataSlot(); break;
        case 2: _t->userPaySlot(); break;
        case 3: _t->allUserBillSlot(); break;
        case 4: _t->monthShouldPayNotPaySlot(); break;
        case 5: _t->shouldChargedSlot(); break;
        case 6: _t->acturalChargedSlot(); break;
        case 7: _t->notChargedSlot(); break;
        case 8: _t->addProprietorSlot(); break;
        case 9: _t->delProprietorSlot(); break;
        case 10: _t->addChargerSlot(); break;
        case 11: _t->delChargerSlot(); break;
        case 12: _t->setStandardSlot(); break;
        case 13: _t->contactSlot(); break;
        case 14: _t->aboutSlot(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
