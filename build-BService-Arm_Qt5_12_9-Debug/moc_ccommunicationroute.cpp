/****************************************************************************
** Meta object code from reading C++ file 'ccommunicationroute.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BService/process/ccommunicationroute.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccommunicationroute.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCommunicationRoute_t {
    QByteArrayData data[15];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCommunicationRoute_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCommunicationRoute_t qt_meta_stringdata_CCommunicationRoute = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CCommunicationRoute"
QT_MOC_LITERAL(1, 20, 22), // "communicationSendEvent"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 4), // "name"
QT_MOC_LITERAL(4, 49, 11), // "commandName"
QT_MOC_LITERAL(5, 61, 7), // "control"
QT_MOC_LITERAL(6, 69, 4), // "data"
QT_MOC_LITERAL(7, 74, 16), // "processRecvEvent"
QT_MOC_LITERAL(8, 91, 11), // "processname"
QT_MOC_LITERAL(9, 103, 8), // "infotype"
QT_MOC_LITERAL(10, 112, 26), // "procCommunicationRecvEvent"
QT_MOC_LITERAL(11, 139, 8), // "lineName"
QT_MOC_LITERAL(12, 148, 8), // "infoType"
QT_MOC_LITERAL(13, 157, 13), // "controlDomain"
QT_MOC_LITERAL(14, 171, 23) // "slot_stopTestLinkageCom"

    },
    "CCommunicationRoute\0communicationSendEvent\0"
    "\0name\0commandName\0control\0data\0"
    "processRecvEvent\0processname\0infotype\0"
    "procCommunicationRecvEvent\0lineName\0"
    "infoType\0controlDomain\0slot_stopTestLinkageCom"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCommunicationRoute[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   34,    2, 0x06 /* Public */,
       7,    4,   43,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    4,   52,    2, 0x0a /* Public */,
      14,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QVariantHash, QMetaType::QByteArray,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QVariantHash, QMetaType::QByteArray,    8,    9,    5,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QVariantHash, QMetaType::QByteArray,   11,   12,   13,    6,
    QMetaType::Void,

       0        // eod
};

void CCommunicationRoute::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CCommunicationRoute *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->communicationSendEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 1: _t->processRecvEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 2: _t->procCommunicationRecvEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 3: _t->slot_stopTestLinkageCom(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CCommunicationRoute::*)(const QString & , const QString & , const QHash<QString,QVariant> & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CCommunicationRoute::communicationSendEvent)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CCommunicationRoute::*)(const QString & , const int & , const QHash<QString,QVariant> & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CCommunicationRoute::processRecvEvent)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CCommunicationRoute::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CCommunicationRoute.data,
    qt_meta_data_CCommunicationRoute,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CCommunicationRoute::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCommunicationRoute::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CCommunicationRoute.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CCommunicationRoute::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void CCommunicationRoute::communicationSendEvent(const QString & _t1, const QString & _t2, const QHash<QString,QVariant> & _t3, const QByteArray & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CCommunicationRoute::processRecvEvent(const QString & _t1, const int & _t2, const QHash<QString,QVariant> & _t3, const QByteArray & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
