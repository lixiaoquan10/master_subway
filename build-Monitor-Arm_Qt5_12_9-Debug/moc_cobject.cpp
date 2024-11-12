/****************************************************************************
** Meta object code from reading C++ file 'cobject.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/dm/cobject.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cobject.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CObject_t {
    QByteArrayData data[25];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CObject_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CObject_t qt_meta_stringdata_CObject = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CObject"
QT_MOC_LITERAL(1, 8, 17), // "editStatusChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 19), // "CObject::EditStatus"
QT_MOC_LITERAL(4, 47, 6), // "status"
QT_MOC_LITERAL(5, 54, 19), // "objectStatusChanged"
QT_MOC_LITERAL(6, 74, 8), // "oldValue"
QT_MOC_LITERAL(7, 83, 8), // "newValue"
QT_MOC_LITERAL(8, 92, 4), // "time"
QT_MOC_LITERAL(9, 97, 12), // "valueChanged"
QT_MOC_LITERAL(10, 110, 8), // "QString&"
QT_MOC_LITERAL(11, 119, 4), // "name"
QT_MOC_LITERAL(12, 124, 9), // "QVariant&"
QT_MOC_LITERAL(13, 134, 13), // "objectChanged"
QT_MOC_LITERAL(14, 148, 19), // "CObject::ObjectType"
QT_MOC_LITERAL(15, 168, 4), // "type"
QT_MOC_LITERAL(16, 173, 8), // "CObject*"
QT_MOC_LITERAL(17, 182, 6), // "object"
QT_MOC_LITERAL(18, 189, 8), // "destrory"
QT_MOC_LITERAL(19, 198, 10), // "EditStatus"
QT_MOC_LITERAL(20, 209, 9), // "EditState"
QT_MOC_LITERAL(21, 219, 7), // "ES_None"
QT_MOC_LITERAL(22, 227, 6), // "ES_New"
QT_MOC_LITERAL(23, 234, 9), // "ES_Modify"
QT_MOC_LITERAL(24, 244, 10) // "ES_Deleted"

    },
    "CObject\0editStatusChanged\0\0"
    "CObject::EditStatus\0status\0"
    "objectStatusChanged\0oldValue\0newValue\0"
    "time\0valueChanged\0QString&\0name\0"
    "QVariant&\0objectChanged\0CObject::ObjectType\0"
    "type\0CObject*\0object\0destrory\0EditStatus\0"
    "EditState\0ES_None\0ES_New\0ES_Modify\0"
    "ES_Deleted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CObject[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       1,   66, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    4,   42,    2, 0x06 /* Public */,
       9,    3,   51,    2, 0x06 /* Public */,
      13,    2,   58,    2, 0x06 /* Public */,
      18,    1,   63,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Short, QMetaType::UChar, QMetaType::UChar, QMetaType::UInt,    4,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 12, 0x80000000 | 12,   11,    6,    7,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 16,   17,

 // enums: name, alias, flags, count, data
      19,   20, 0x1,    4,   71,

 // enum data: key, value
      21, uint(CObject::ES_None),
      22, uint(CObject::ES_New),
      23, uint(CObject::ES_Modify),
      24, uint(CObject::ES_Deleted),

       0        // eod
};

void CObject::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CObject *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editStatusChanged((*reinterpret_cast< CObject::EditStatus(*)>(_a[1]))); break;
        case 1: _t->objectStatusChanged((*reinterpret_cast< short(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 2: _t->valueChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 3: _t->objectChanged((*reinterpret_cast< CObject::ObjectType(*)>(_a[1])),(*reinterpret_cast< CObject*(*)>(_a[2]))); break;
        case 4: _t->destrory((*reinterpret_cast< CObject*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CObject* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CObject* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CObject::*)(CObject::EditStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CObject::editStatusChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CObject::*)(short , unsigned char , unsigned char , unsigned int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CObject::objectStatusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CObject::*)(QString & , QVariant & , QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CObject::valueChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CObject::*)(CObject::ObjectType , CObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CObject::objectChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CObject::*)(CObject * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CObject::destrory)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CObject::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CObject.data,
    qt_meta_data_CObject,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CObject::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CObject::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CObject.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CObject::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CObject::editStatusChanged(CObject::EditStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CObject::objectStatusChanged(short _t1, unsigned char _t2, unsigned char _t3, unsigned int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CObject::valueChanged(QString & _t1, QVariant & _t2, QVariant & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CObject::objectChanged(CObject::ObjectType _t1, CObject * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CObject::destrory(CObject * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
