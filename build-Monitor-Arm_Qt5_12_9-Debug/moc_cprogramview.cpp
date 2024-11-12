/****************************************************************************
** Meta object code from reading C++ file 'cprogramview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/widget/cprogramview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprogramview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CProgramView_t {
    QByteArrayData data[15];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CProgramView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CProgramView_t qt_meta_stringdata_CProgramView = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CProgramView"
QT_MOC_LITERAL(1, 13, 13), // "sigRegAllInfo"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "sigRegLoopInfo"
QT_MOC_LITERAL(4, 43, 11), // "slot_regALL"
QT_MOC_LITERAL(5, 55, 12), // "slot_regLoop"
QT_MOC_LITERAL(6, 68, 12), // "slot_unLogin"
QT_MOC_LITERAL(7, 81, 16), // "slot_unLoginLoop"
QT_MOC_LITERAL(8, 98, 20), // "slot_recodeAllDevice"
QT_MOC_LITERAL(9, 119, 21), // "slot_recodeLoopDevice"
QT_MOC_LITERAL(10, 141, 18), // "slot_saveAllDevice"
QT_MOC_LITERAL(11, 160, 19), // "slot_saveLoopDevice"
QT_MOC_LITERAL(12, 180, 22), // "slot_removeLoginObject"
QT_MOC_LITERAL(13, 203, 24), // "slot_resetControllerView"
QT_MOC_LITERAL(14, 228, 19) // "slot_DelayReAddress"

    },
    "CProgramView\0sigRegAllInfo\0\0sigRegLoopInfo\0"
    "slot_regALL\0slot_regLoop\0slot_unLogin\0"
    "slot_unLoginLoop\0slot_recodeAllDevice\0"
    "slot_recodeLoopDevice\0slot_saveAllDevice\0"
    "slot_saveLoopDevice\0slot_removeLoginObject\0"
    "slot_resetControllerView\0slot_DelayReAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CProgramView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       6,    0,   83,    2, 0x0a /* Public */,
       7,    0,   84,    2, 0x0a /* Public */,
       8,    0,   85,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      10,    0,   87,    2, 0x0a /* Public */,
      11,    0,   88,    2, 0x0a /* Public */,
      12,    0,   89,    2, 0x0a /* Public */,
      13,    0,   90,    2, 0x0a /* Public */,
      14,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CProgramView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CProgramView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigRegAllInfo(); break;
        case 1: _t->sigRegLoopInfo(); break;
        case 2: _t->slot_regALL(); break;
        case 3: _t->slot_regLoop(); break;
        case 4: _t->slot_unLogin(); break;
        case 5: _t->slot_unLoginLoop(); break;
        case 6: _t->slot_recodeAllDevice(); break;
        case 7: _t->slot_recodeLoopDevice(); break;
        case 8: _t->slot_saveAllDevice(); break;
        case 9: _t->slot_saveLoopDevice(); break;
        case 10: _t->slot_removeLoginObject(); break;
        case 11: _t->slot_resetControllerView(); break;
        case 12: _t->slot_DelayReAddress(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CProgramView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CProgramView::sigRegAllInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CProgramView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CProgramView::sigRegLoopInfo)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CProgramView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CProgramView.data,
    qt_meta_data_CProgramView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CProgramView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CProgramView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CProgramView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CProgramView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void CProgramView::sigRegAllInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CProgramView::sigRegLoopInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
