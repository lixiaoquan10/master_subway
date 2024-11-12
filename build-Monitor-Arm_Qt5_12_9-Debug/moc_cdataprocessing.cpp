/****************************************************************************
** Meta object code from reading C++ file 'cdataprocessing.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/business/cdataprocessing.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cdataprocessing.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CDataProcessing_t {
    QByteArrayData data[23];
    char stringdata0[314];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDataProcessing_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDataProcessing_t qt_meta_stringdata_CDataProcessing = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CDataProcessing"
QT_MOC_LITERAL(1, 16, 21), // "slotNotifyInformation"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 4), // "type"
QT_MOC_LITERAL(4, 44, 4), // "data"
QT_MOC_LITERAL(5, 49, 17), // "slotCommandResult"
QT_MOC_LITERAL(6, 67, 11), // "commandType"
QT_MOC_LITERAL(7, 79, 15), // "CMsgStructBase*"
QT_MOC_LITERAL(8, 95, 7), // "msgData"
QT_MOC_LITERAL(9, 103, 15), // "slotVerifyAdmin"
QT_MOC_LITERAL(10, 119, 20), // "slotStateInformation"
QT_MOC_LITERAL(11, 140, 10), // "StatusInfo"
QT_MOC_LITERAL(12, 151, 10), // "statusInfo"
QT_MOC_LITERAL(13, 162, 3), // "opr"
QT_MOC_LITERAL(14, 166, 15), // "slotChangeColor"
QT_MOC_LITERAL(15, 182, 18), // "slotcheckLoginInfo"
QT_MOC_LITERAL(16, 201, 17), // "slot_usetimeCheck"
QT_MOC_LITERAL(17, 219, 14), // "slot_usetime1h"
QT_MOC_LITERAL(18, 234, 19), // "slot_threadFinished"
QT_MOC_LITERAL(19, 254, 17), // "slot_updateStatus"
QT_MOC_LITERAL(20, 272, 8), // "CObject*"
QT_MOC_LITERAL(21, 281, 25), // "slot_setDeviceOnlineTotal"
QT_MOC_LITERAL(22, 307, 6) // "CLoop*"

    },
    "CDataProcessing\0slotNotifyInformation\0"
    "\0type\0data\0slotCommandResult\0commandType\0"
    "CMsgStructBase*\0msgData\0slotVerifyAdmin\0"
    "slotStateInformation\0StatusInfo\0"
    "statusInfo\0opr\0slotChangeColor\0"
    "slotcheckLoginInfo\0slot_usetimeCheck\0"
    "slot_usetime1h\0slot_threadFinished\0"
    "slot_updateStatus\0CObject*\0"
    "slot_setDeviceOnlineTotal\0CLoop*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDataProcessing[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x0a /* Public */,
       5,    2,   74,    2, 0x0a /* Public */,
       9,    2,   79,    2, 0x0a /* Public */,
      10,    3,   84,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,
      15,    0,   92,    2, 0x0a /* Public */,
      16,    0,   93,    2, 0x0a /* Public */,
      17,    0,   94,    2, 0x0a /* Public */,
      18,    0,   95,    2, 0x0a /* Public */,
      19,    3,   96,    2, 0x0a /* Public */,
      21,    2,  103,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QVariantList,    3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 11, QMetaType::Int, QMetaType::Int,   12,    3,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20, QMetaType::Short, QMetaType::UChar,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 22, QMetaType::Int,    2,    2,

       0        // eod
};

void CDataProcessing::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CDataProcessing *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotNotifyInformation((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QList<QVariant>(*)>(_a[2]))); break;
        case 1: _t->slotCommandResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CMsgStructBase*(*)>(_a[2]))); break;
        case 2: _t->slotVerifyAdmin((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CMsgStructBase*(*)>(_a[2]))); break;
        case 3: _t->slotStateInformation((*reinterpret_cast< const StatusInfo(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->slotChangeColor(); break;
        case 5: _t->slotcheckLoginInfo(); break;
        case 6: _t->slot_usetimeCheck(); break;
        case 7: _t->slot_usetime1h(); break;
        case 8: _t->slot_threadFinished(); break;
        case 9: _t->slot_updateStatus((*reinterpret_cast< CObject*(*)>(_a[1])),(*reinterpret_cast< short(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3]))); break;
        case 10: _t->slot_setDeviceOnlineTotal((*reinterpret_cast< CLoop*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CMsgStructBase* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CMsgStructBase* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CDataProcessing::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CDataProcessing.data,
    qt_meta_data_CDataProcessing,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CDataProcessing::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDataProcessing::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CDataProcessing.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CDataProcessing::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
struct qt_meta_stringdata_checkThread_t {
    QByteArrayData data[7];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_checkThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_checkThread_t qt_meta_stringdata_checkThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "checkThread"
QT_MOC_LITERAL(1, 12, 14), // "threadFinished"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "updateStatus"
QT_MOC_LITERAL(4, 41, 8), // "CObject*"
QT_MOC_LITERAL(5, 50, 20), // "setDeviceOnlineTotal"
QT_MOC_LITERAL(6, 71, 6) // "CLoop*"

    },
    "checkThread\0threadFinished\0\0updateStatus\0"
    "CObject*\0setDeviceOnlineTotal\0CLoop*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_checkThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    3,   30,    2, 0x06 /* Public */,
       5,    2,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Short, QMetaType::UChar,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int,    2,    2,

       0        // eod
};

void checkThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<checkThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->threadFinished(); break;
        case 1: _t->updateStatus((*reinterpret_cast< CObject*(*)>(_a[1])),(*reinterpret_cast< short(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3]))); break;
        case 2: _t->setDeviceOnlineTotal((*reinterpret_cast< CLoop*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (checkThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&checkThread::threadFinished)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (checkThread::*)(CObject * , short , unsigned char );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&checkThread::updateStatus)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (checkThread::*)(CLoop * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&checkThread::setDeviceOnlineTotal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject checkThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_checkThread.data,
    qt_meta_data_checkThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *checkThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *checkThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_checkThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int checkThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void checkThread::threadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void checkThread::updateStatus(CObject * _t1, short _t2, unsigned char _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void checkThread::setDeviceOnlineTotal(CLoop * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
