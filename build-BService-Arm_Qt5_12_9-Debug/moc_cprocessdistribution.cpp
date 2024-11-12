/****************************************************************************
** Meta object code from reading C++ file 'cprocessdistribution.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BService/process/cprocessdistribution.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprocessdistribution.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CProcessDistribution_t {
    QByteArrayData data[18];
    char stringdata0[228];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CProcessDistribution_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CProcessDistribution_t qt_meta_stringdata_CProcessDistribution = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CProcessDistribution"
QT_MOC_LITERAL(1, 21, 7), // "timeOut"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "regeditOK"
QT_MOC_LITERAL(4, 40, 9), // "emergency"
QT_MOC_LITERAL(5, 50, 6), // "enable"
QT_MOC_LITERAL(6, 57, 19), // "distributionAddress"
QT_MOC_LITERAL(7, 77, 11), // "loopAddress"
QT_MOC_LITERAL(8, 89, 13), // "deviceAddress"
QT_MOC_LITERAL(9, 103, 10), // "canportAdd"
QT_MOC_LITERAL(10, 114, 10), // "Directions"
QT_MOC_LITERAL(11, 125, 9), // "Direction"
QT_MOC_LITERAL(12, 135, 13), // "NoneDirection"
QT_MOC_LITERAL(13, 149, 18), // "NoneFlashDirection"
QT_MOC_LITERAL(14, 168, 14), // "FlashDirection"
QT_MOC_LITERAL(15, 183, 13), // "LeftDirection"
QT_MOC_LITERAL(16, 197, 14), // "RightDirection"
QT_MOC_LITERAL(17, 212, 15) // "PeopleDirection"

    },
    "CProcessDistribution\0timeOut\0\0regeditOK\0"
    "emergency\0enable\0distributionAddress\0"
    "loopAddress\0deviceAddress\0canportAdd\0"
    "Directions\0Direction\0NoneDirection\0"
    "NoneFlashDirection\0FlashDirection\0"
    "LeftDirection\0RightDirection\0"
    "PeopleDirection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CProcessDistribution[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       1,   86, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    5,   51,    2, 0x0a /* Public */,
       4,    4,   62,    2, 0x2a /* Public | MethodCloned */,
       4,    3,   71,    2, 0x2a /* Public | MethodCloned */,
       4,    2,   78,    2, 0x2a /* Public | MethodCloned */,
       4,    1,   83,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,    8,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int, QMetaType::Int,    5,    6,    7,
    QMetaType::Void, QMetaType::Bool, QMetaType::Int,    5,    6,
    QMetaType::Void, QMetaType::Bool,    5,

 // enums: name, alias, flags, count, data
      10,   11, 0x1,    6,   91,

 // enum data: key, value
      12, uint(CProcessDistribution::NoneDirection),
      13, uint(CProcessDistribution::NoneFlashDirection),
      14, uint(CProcessDistribution::FlashDirection),
      15, uint(CProcessDistribution::LeftDirection),
      16, uint(CProcessDistribution::RightDirection),
      17, uint(CProcessDistribution::PeopleDirection),

       0        // eod
};

void CProcessDistribution::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CProcessDistribution *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeOut(); break;
        case 1: _t->regeditOK(); break;
        case 2: _t->emergency((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5]))); break;
        case 3: _t->emergency((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 4: _t->emergency((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->emergency((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->emergency((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CProcessDistribution::staticMetaObject = { {
    &CProcessBase::staticMetaObject,
    qt_meta_stringdata_CProcessDistribution.data,
    qt_meta_data_CProcessDistribution,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CProcessDistribution::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CProcessDistribution::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CProcessDistribution.stringdata0))
        return static_cast<void*>(this);
    return CProcessBase::qt_metacast(_clname);
}

int CProcessDistribution::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CProcessBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
