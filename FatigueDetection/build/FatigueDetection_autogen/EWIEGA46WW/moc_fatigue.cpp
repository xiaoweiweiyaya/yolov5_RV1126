/****************************************************************************
** Meta object code from reading C++ file 'fatigue.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "fatigue.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fatigue.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Fatigue_t {
    QByteArrayData data[17];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Fatigue_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Fatigue_t qt_meta_stringdata_Fatigue = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Fatigue"
QT_MOC_LITERAL(1, 8, 9), // "attention"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 2), // "al"
QT_MOC_LITERAL(4, 22, 15), // "sendImageSignal"
QT_MOC_LITERAL(5, 38, 8), // "cv::Mat&"
QT_MOC_LITERAL(6, 47, 11), // "driverImage"
QT_MOC_LITERAL(7, 59, 5), // "Rect&"
QT_MOC_LITERAL(8, 65, 4), // "rect"
QT_MOC_LITERAL(9, 70, 10), // "video_show"
QT_MOC_LITERAL(10, 81, 13), // "timer_connect"
QT_MOC_LITERAL(11, 95, 12), // "stop_connect"
QT_MOC_LITERAL(12, 108, 13), // "start_connect"
QT_MOC_LITERAL(13, 122, 9), // "recv_data"
QT_MOC_LITERAL(14, 132, 15), // "FaceRecognition"
QT_MOC_LITERAL(15, 148, 9), // "sendImage"
QT_MOC_LITERAL(16, 158, 27) // "on_open_close_video_clicked"

    },
    "Fatigue\0attention\0\0al\0sendImageSignal\0"
    "cv::Mat&\0driverImage\0Rect&\0rect\0"
    "video_show\0timer_connect\0stop_connect\0"
    "start_connect\0recv_data\0FaceRecognition\0"
    "sendImage\0on_open_close_video_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Fatigue[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    2,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,
      13,    0,   76,    2, 0x0a /* Public */,
      14,    0,   77,    2, 0x0a /* Public */,
      15,    2,   78,    2, 0x0a /* Public */,
      16,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 7,    6,    8,
    QMetaType::Void,

       0        // eod
};

void Fatigue::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Fatigue *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attention((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->sendImageSignal((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< Rect(*)>(_a[2]))); break;
        case 2: _t->video_show(); break;
        case 3: _t->timer_connect(); break;
        case 4: _t->stop_connect(); break;
        case 5: _t->start_connect(); break;
        case 6: _t->recv_data(); break;
        case 7: _t->FaceRecognition(); break;
        case 8: _t->sendImage((*reinterpret_cast< cv::Mat(*)>(_a[1])),(*reinterpret_cast< Rect(*)>(_a[2]))); break;
        case 9: _t->on_open_close_video_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Fatigue::*)(unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Fatigue::attention)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Fatigue::*)(cv::Mat & , Rect & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Fatigue::sendImageSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Fatigue::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Fatigue.data,
    qt_meta_data_Fatigue,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Fatigue::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Fatigue::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Fatigue.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Fatigue::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Fatigue::attention(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Fatigue::sendImageSignal(cv::Mat & _t1, Rect & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
