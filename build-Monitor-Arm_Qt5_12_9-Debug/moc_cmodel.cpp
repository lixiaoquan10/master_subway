/****************************************************************************
** Meta object code from reading C++ file 'cmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/model/cmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CModel_t {
    QByteArrayData data[19];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CModel_t qt_meta_stringdata_CModel = {
    {
QT_MOC_LITERAL(0, 0, 6), // "CModel"
QT_MOC_LITERAL(1, 7, 12), // "valueChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "QString&"
QT_MOC_LITERAL(4, 30, 4), // "name"
QT_MOC_LITERAL(5, 35, 9), // "QVariant&"
QT_MOC_LITERAL(6, 45, 8), // "oldValue"
QT_MOC_LITERAL(7, 54, 8), // "newValue"
QT_MOC_LITERAL(8, 63, 13), // "objectChanged"
QT_MOC_LITERAL(9, 77, 19), // "CObject::ObjectType"
QT_MOC_LITERAL(10, 97, 4), // "type"
QT_MOC_LITERAL(11, 102, 8), // "CObject*"
QT_MOC_LITERAL(12, 111, 6), // "object"
QT_MOC_LITERAL(13, 118, 19), // "objectStatusChanged"
QT_MOC_LITERAL(14, 138, 6), // "status"
QT_MOC_LITERAL(15, 145, 4), // "time"
QT_MOC_LITERAL(16, 150, 17), // "editStatusChanged"
QT_MOC_LITERAL(17, 168, 19), // "CObject::EditStatus"
QT_MOC_LITERAL(18, 188, 13) // "objectDestroy"

    },
    "CModel\0valueChanged\0\0QString&\0name\0"
    "QVariant&\0oldValue\0newValue\0objectChanged\0"
    "CObject::ObjectType\0type\0CObject*\0"
    "object\0objectStatusChanged\0status\0"
    "time\0editStatusChanged\0CObject::EditStatus\0"
    "objectDestroy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   39,    2, 0x09 /* Protected */,
       8,    2,   46,    2, 0x09 /* Protected */,
      13,    4,   51,    2, 0x09 /* Protected */,
      16,    1,   60,    2, 0x09 /* Protected */,
      18,    1,   63,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 5,    4,    6,    7,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 11,   10,   12,
    QMetaType::Void, QMetaType::Short, QMetaType::UChar, QMetaType::UChar, QMetaType::UInt,   14,    6,    7,   15,
    QMetaType::Void, 0x80000000 | 17,   14,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void CModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2])),(*reinterpret_cast< QVariant(*)>(_a[3]))); break;
        case 1: _t->objectChanged((*reinterpret_cast< CObject::ObjectType(*)>(_a[1])),(*reinterpret_cast< CObject*(*)>(_a[2]))); break;
        case 2: _t->objectStatusChanged((*reinterpret_cast< short(*)>(_a[1])),(*reinterpret_cast< unsigned char(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3])),(*reinterpret_cast< uint(*)>(_a[4]))); break;
        case 3: _t->editStatusChanged((*reinterpret_cast< CObject::EditStatus(*)>(_a[1]))); break;
        case 4: _t->objectDestroy((*reinterpret_cast< CObject*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
    }
}

QT_INIT_METAOBJECT const QMetaObject CModel::staticMetaObject = { {
    &QAbstractItemModel::staticMetaObject,
    qt_meta_stringdata_CModel.data,
    qt_meta_data_CModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractItemModel::qt_metacast(_clname);
}

int CModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractItemModel::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
