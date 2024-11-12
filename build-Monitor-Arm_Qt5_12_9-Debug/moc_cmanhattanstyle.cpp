/****************************************************************************
** Meta object code from reading C++ file 'cmanhattanstyle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/style/cmanhattanstyle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cmanhattanstyle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CManhattanStyle_t {
    QByteArrayData data[9];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CManhattanStyle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CManhattanStyle_t qt_meta_stringdata_CManhattanStyle = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CManhattanStyle"
QT_MOC_LITERAL(1, 16, 26), // "standardIconImplementation"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 14), // "StandardPixmap"
QT_MOC_LITERAL(4, 59, 12), // "standardIcon"
QT_MOC_LITERAL(5, 72, 19), // "const QStyleOption*"
QT_MOC_LITERAL(6, 92, 6), // "option"
QT_MOC_LITERAL(7, 99, 14), // "const QWidget*"
QT_MOC_LITERAL(8, 114, 6) // "widget"

    },
    "CManhattanStyle\0standardIconImplementation\0"
    "\0StandardPixmap\0standardIcon\0"
    "const QStyleOption*\0option\0const QWidget*\0"
    "widget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CManhattanStyle[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::QIcon, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,

       0        // eod
};

void CManhattanStyle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CManhattanStyle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QIcon _r = _t->standardIconImplementation((*reinterpret_cast< StandardPixmap(*)>(_a[1])),(*reinterpret_cast< const QStyleOption*(*)>(_a[2])),(*reinterpret_cast< const QWidget*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< QIcon*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CManhattanStyle::staticMetaObject = { {
    &QProxyStyle::staticMetaObject,
    qt_meta_stringdata_CManhattanStyle.data,
    qt_meta_data_CManhattanStyle,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CManhattanStyle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CManhattanStyle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CManhattanStyle.stringdata0))
        return static_cast<void*>(this);
    return QProxyStyle::qt_metacast(_clname);
}

int CManhattanStyle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProxyStyle::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
