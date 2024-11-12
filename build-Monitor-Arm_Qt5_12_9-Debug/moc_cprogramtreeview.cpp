/****************************************************************************
** Meta object code from reading C++ file 'cprogramtreeview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/widget/cprogramtreeview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprogramtreeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CProgramTreeView_t {
    QByteArrayData data[18];
    char stringdata0[297];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CProgramTreeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CProgramTreeView_t qt_meta_stringdata_CProgramTreeView = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CProgramTreeView"
QT_MOC_LITERAL(1, 17, 23), // "signalRightSelectedLoop"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 6), // "CLoop*"
QT_MOC_LITERAL(4, 49, 4), // "loop"
QT_MOC_LITERAL(5, 54, 17), // "slotNewController"
QT_MOC_LITERAL(6, 72, 18), // "slotOpenController"
QT_MOC_LITERAL(7, 91, 19), // "slotCloseController"
QT_MOC_LITERAL(8, 111, 18), // "slotSaveController"
QT_MOC_LITERAL(9, 130, 20), // "slotExportController"
QT_MOC_LITERAL(10, 151, 20), // "slot_TreeViewClicked"
QT_MOC_LITERAL(11, 172, 11), // "QModelIndex"
QT_MOC_LITERAL(12, 184, 5), // "index"
QT_MOC_LITERAL(13, 190, 19), // "slot_emergencyStart"
QT_MOC_LITERAL(14, 210, 18), // "slot_emergencyStop"
QT_MOC_LITERAL(15, 229, 20), // "slot_ReadLampVersion"
QT_MOC_LITERAL(16, 250, 25), // "slot_DelayReadLampVersion"
QT_MOC_LITERAL(17, 276, 20) // "slot_removeLampLogin"

    },
    "CProgramTreeView\0signalRightSelectedLoop\0"
    "\0CLoop*\0loop\0slotNewController\0"
    "slotOpenController\0slotCloseController\0"
    "slotSaveController\0slotExportController\0"
    "slot_TreeViewClicked\0QModelIndex\0index\0"
    "slot_emergencyStart\0slot_emergencyStop\0"
    "slot_ReadLampVersion\0slot_DelayReadLampVersion\0"
    "slot_removeLampLogin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CProgramTreeView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    0,   87,    2, 0x0a /* Public */,
      16,    0,   88,    2, 0x0a /* Public */,
      17,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CProgramTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CProgramTreeView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalRightSelectedLoop((*reinterpret_cast< CLoop*(*)>(_a[1]))); break;
        case 1: _t->slotNewController(); break;
        case 2: _t->slotOpenController(); break;
        case 3: _t->slotCloseController(); break;
        case 4: _t->slotSaveController(); break;
        case 5: _t->slotExportController(); break;
        case 6: _t->slot_TreeViewClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 7: _t->slot_emergencyStart(); break;
        case 8: _t->slot_emergencyStop(); break;
        case 9: _t->slot_ReadLampVersion(); break;
        case 10: _t->slot_DelayReadLampVersion(); break;
        case 11: _t->slot_removeLampLogin(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CProgramTreeView::*)(CLoop * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CProgramTreeView::signalRightSelectedLoop)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CProgramTreeView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CProgramTreeView.data,
    qt_meta_data_CProgramTreeView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CProgramTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CProgramTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CProgramTreeView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CProgramTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CProgramTreeView::signalRightSelectedLoop(CLoop * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
