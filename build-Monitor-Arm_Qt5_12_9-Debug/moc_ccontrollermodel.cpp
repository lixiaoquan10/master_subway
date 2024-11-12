/****************************************************************************
** Meta object code from reading C++ file 'ccontrollermodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/model/ccontrollermodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccontrollermodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CControllerModel_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CControllerModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CControllerModel_t qt_meta_stringdata_CControllerModel = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CControllerModel"
QT_MOC_LITERAL(1, 17, 13), // "objectChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "CObject::ObjectType"
QT_MOC_LITERAL(4, 52, 4), // "type"
QT_MOC_LITERAL(5, 57, 8), // "CObject*"
QT_MOC_LITERAL(6, 66, 6), // "object"
QT_MOC_LITERAL(7, 73, 13) // "objectDestroy"

    },
    "CControllerModel\0objectChanged\0\0"
    "CObject::ObjectType\0type\0CObject*\0"
    "object\0objectDestroy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CControllerModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x09 /* Protected */,
       7,    1,   29,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void CControllerModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CControllerModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->objectChanged((*reinterpret_cast< CObject::ObjectType(*)>(_a[1])),(*reinterpret_cast< CObject*(*)>(_a[2]))); break;
        case 1: _t->objectDestroy((*reinterpret_cast< CObject*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CObject* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CObject* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CControllerModel::staticMetaObject = { {
    &CModel::staticMetaObject,
    qt_meta_stringdata_CControllerModel.data,
    qt_meta_data_CControllerModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CControllerModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CControllerModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CControllerModel.stringdata0))
        return static_cast<void*>(this);
    return CModel::qt_metacast(_clname);
}

int CControllerModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
