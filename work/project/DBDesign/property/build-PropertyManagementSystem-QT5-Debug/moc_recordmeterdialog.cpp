/****************************************************************************
** Meta object code from reading C++ file 'recordmeterdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../property/recordmeterdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recordmeterdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RecordMeterDialog_t {
    QByteArrayData data[6];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordMeterDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordMeterDialog_t qt_meta_stringdata_RecordMeterDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "RecordMeterDialog"
QT_MOC_LITERAL(1, 18, 38), // "on_buildingomboBox_currentInd..."
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 5), // "index"
QT_MOC_LITERAL(4, 64, 33), // "on_insertRecordPushButton_cli..."
QT_MOC_LITERAL(5, 98, 28) // "on_confirmPushButton_clicked"

    },
    "RecordMeterDialog\0"
    "on_buildingomboBox_currentIndexChanged\0"
    "\0index\0on_insertRecordPushButton_clicked\0"
    "on_confirmPushButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordMeterDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x08 /* Private */,
       4,    0,   32,    2, 0x08 /* Private */,
       5,    0,   33,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RecordMeterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RecordMeterDialog *_t = static_cast<RecordMeterDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_buildingomboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_insertRecordPushButton_clicked(); break;
        case 2: _t->on_confirmPushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject RecordMeterDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_RecordMeterDialog.data,
      qt_meta_data_RecordMeterDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RecordMeterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordMeterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RecordMeterDialog.stringdata0))
        return static_cast<void*>(const_cast< RecordMeterDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int RecordMeterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
