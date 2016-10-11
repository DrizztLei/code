/****************************************************************************
** Meta object code from reading C++ file 'userpaywidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../property/userpaywidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userpaywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UserPayWidget_t {
    QByteArrayData data[8];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserPayWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserPayWidget_t qt_meta_stringdata_UserPayWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "UserPayWidget"
QT_MOC_LITERAL(1, 14, 39), // "on_buildingComboBox_currentIn..."
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 5), // "index"
QT_MOC_LITERAL(4, 61, 35), // "on_roomComboBox_currentIndexC..."
QT_MOC_LITERAL(5, 97, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(6, 121, 27), // "on_SelectPushButton_clicked"
QT_MOC_LITERAL(7, 149, 21) // "on_pushButton_clicked"

    },
    "UserPayWidget\0on_buildingComboBox_currentIndexChanged\0"
    "\0index\0on_roomComboBox_currentIndexChanged\0"
    "on_pushButton_2_clicked\0"
    "on_SelectPushButton_clicked\0"
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserPayWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       4,    1,   42,    2, 0x08 /* Private */,
       5,    0,   45,    2, 0x08 /* Private */,
       6,    0,   46,    2, 0x08 /* Private */,
       7,    0,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UserPayWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UserPayWidget *_t = static_cast<UserPayWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_buildingComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_roomComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_2_clicked(); break;
        case 3: _t->on_SelectPushButton_clicked(); break;
        case 4: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject UserPayWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UserPayWidget.data,
      qt_meta_data_UserPayWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UserPayWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserPayWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UserPayWidget.stringdata0))
        return static_cast<void*>(const_cast< UserPayWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int UserPayWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
