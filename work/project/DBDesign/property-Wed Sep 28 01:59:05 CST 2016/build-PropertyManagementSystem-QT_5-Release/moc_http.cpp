/****************************************************************************
** Meta object code from reading C++ file 'http.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../property/http.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'http.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HTTP_t {
    QByteArrayData data[17];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HTTP_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HTTP_t qt_meta_stringdata_HTTP = {
    {
QT_MOC_LITERAL(0, 0, 4), // "HTTP"
QT_MOC_LITERAL(1, 5, 14), // "cancelDownload"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 20), // "enableDownloadButton"
QT_MOC_LITERAL(4, 42, 26), // "slotAuthenticationRequired"
QT_MOC_LITERAL(5, 69, 14), // "QNetworkReply*"
QT_MOC_LITERAL(6, 84, 15), // "QAuthenticator*"
QT_MOC_LITERAL(7, 100, 24), // "slotNetworkReplyProgress"
QT_MOC_LITERAL(8, 125, 9), // "receivers"
QT_MOC_LITERAL(9, 135, 5), // "total"
QT_MOC_LITERAL(10, 141, 14), // "slotDownFinish"
QT_MOC_LITERAL(11, 156, 12), // "httpFinished"
QT_MOC_LITERAL(12, 169, 8), // "download"
QT_MOC_LITERAL(13, 178, 13), // "httpReadyRead"
QT_MOC_LITERAL(14, 192, 9), // "sslErrors"
QT_MOC_LITERAL(15, 202, 16), // "QList<QSslError>"
QT_MOC_LITERAL(16, 219, 6) // "errors"

    },
    "HTTP\0cancelDownload\0\0enableDownloadButton\0"
    "slotAuthenticationRequired\0QNetworkReply*\0"
    "QAuthenticator*\0slotNetworkReplyProgress\0"
    "receivers\0total\0slotDownFinish\0"
    "httpFinished\0download\0httpReadyRead\0"
    "sslErrors\0QList<QSslError>\0errors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HTTP[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    2,   61,    2, 0x08 /* Private */,
       7,    2,   66,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,
      11,    0,   72,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,
      13,    0,   74,    2, 0x08 /* Private */,
      14,    2,   75,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 15,    2,   16,

       0        // eod
};

void HTTP::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HTTP *_t = static_cast<HTTP *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cancelDownload(); break;
        case 1: _t->enableDownloadButton(); break;
        case 2: _t->slotAuthenticationRequired((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 3: _t->slotNetworkReplyProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->slotDownFinish(); break;
        case 5: _t->httpFinished(); break;
        case 6: _t->download(); break;
        case 7: _t->httpReadyRead(); break;
        case 8: _t->sslErrors((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< const QList<QSslError>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

const QMetaObject HTTP::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HTTP.data,
      qt_meta_data_HTTP,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HTTP::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HTTP::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HTTP.stringdata0))
        return static_cast<void*>(const_cast< HTTP*>(this));
    return QObject::qt_metacast(_clname);
}

int HTTP::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
