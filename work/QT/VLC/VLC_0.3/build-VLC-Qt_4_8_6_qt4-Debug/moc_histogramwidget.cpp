/****************************************************************************
** Meta object code from reading C++ file 'histogramwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VLC/histogramwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histogramwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrameProcess[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      67,   54,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FrameProcess[] = {
    "FrameProcess\0\0histogram\0"
    "histogramRead(QVector<qreal>)\0"
    "frame,levels\0processFrame(QVideo,int)\0"
};

void FrameProcess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        FrameProcess *_t = static_cast<FrameProcess *>(_o);
        switch (_id) {
        case 0: _t->histogramRead((*reinterpret_cast< QVector<qreal>(*)>(_a[1]))); break;
        case 1: _t->processFrame((*reinterpret_cast< QVideo(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData FrameProcess::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject FrameProcess::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FrameProcess,
      qt_meta_data_FrameProcess, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrameProcess::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrameProcess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrameProcess::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrameProcess))
        return static_cast<void*>(const_cast< FrameProcess*>(this));
    return QObject::qt_metacast(_clname);
}

int FrameProcess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FrameProcess::histogramRead(QVector<qreal> _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_HistogramWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x0a,
      59,   49,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_HistogramWidget[] = {
    "HistogramWidget\0\0frame\0processFrame(QVideoFrame)\0"
    "histogram\0setHistogram(QVector<qureal>)\0"
};

void HistogramWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HistogramWidget *_t = static_cast<HistogramWidget *>(_o);
        switch (_id) {
        case 0: _t->processFrame((*reinterpret_cast< QVideoFrame(*)>(_a[1]))); break;
        case 1: _t->setHistogram((*reinterpret_cast< QVector<qureal>(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HistogramWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HistogramWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HistogramWidget,
      qt_meta_data_HistogramWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HistogramWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HistogramWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HistogramWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HistogramWidget))
        return static_cast<void*>(const_cast< HistogramWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int HistogramWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
