/****************************************************************************
** Meta object code from reading C++ file 'cdesigntreeview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/widget/cdesigntreeview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cdesigntreeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CDesignTreeView_t {
    QByteArrayData data[29];
    char stringdata0[400];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CDesignTreeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CDesignTreeView_t qt_meta_stringdata_CDesignTreeView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "CDesignTreeView"
QT_MOC_LITERAL(1, 16, 14), // "sigIsLayerView"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6), // "enable"
QT_MOC_LITERAL(4, 39, 12), // "layerChanged"
QT_MOC_LITERAL(5, 52, 7), // "CLayer*"
QT_MOC_LITERAL(6, 60, 5), // "layer"
QT_MOC_LITERAL(7, 66, 17), // "slotNewController"
QT_MOC_LITERAL(8, 84, 18), // "slotOpenController"
QT_MOC_LITERAL(9, 103, 19), // "slotCloseController"
QT_MOC_LITERAL(10, 123, 18), // "slotSaveController"
QT_MOC_LITERAL(11, 142, 20), // "slotExportController"
QT_MOC_LITERAL(12, 163, 20), // "slotSelectionChanged"
QT_MOC_LITERAL(13, 184, 14), // "QItemSelection"
QT_MOC_LITERAL(14, 199, 8), // "selected"
QT_MOC_LITERAL(15, 208, 10), // "deselected"
QT_MOC_LITERAL(16, 219, 13), // "slotStartDrag"
QT_MOC_LITERAL(17, 233, 15), // "Qt::DropActions"
QT_MOC_LITERAL(18, 249, 16), // "supportedActions"
QT_MOC_LITERAL(19, 266, 18), // "slotDragEnterEvent"
QT_MOC_LITERAL(20, 285, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(21, 302, 5), // "event"
QT_MOC_LITERAL(22, 308, 17), // "slotDragMoveEvent"
QT_MOC_LITERAL(23, 326, 15), // "QDragMoveEvent*"
QT_MOC_LITERAL(24, 342, 13), // "slotDropEvent"
QT_MOC_LITERAL(25, 356, 11), // "QDropEvent*"
QT_MOC_LITERAL(26, 368, 13), // "slot_autoPage"
QT_MOC_LITERAL(27, 382, 8), // "addLayer"
QT_MOC_LITERAL(28, 391, 8) // "delLayer"

    },
    "CDesignTreeView\0sigIsLayerView\0\0enable\0"
    "layerChanged\0CLayer*\0layer\0slotNewController\0"
    "slotOpenController\0slotCloseController\0"
    "slotSaveController\0slotExportController\0"
    "slotSelectionChanged\0QItemSelection\0"
    "selected\0deselected\0slotStartDrag\0"
    "Qt::DropActions\0supportedActions\0"
    "slotDragEnterEvent\0QDragEnterEvent*\0"
    "event\0slotDragMoveEvent\0QDragMoveEvent*\0"
    "slotDropEvent\0QDropEvent*\0slot_autoPage\0"
    "addLayer\0delLayer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CDesignTreeView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   95,    2, 0x0a /* Public */,
       8,    0,   96,    2, 0x0a /* Public */,
       9,    0,   97,    2, 0x0a /* Public */,
      10,    0,   98,    2, 0x0a /* Public */,
      11,    0,   99,    2, 0x0a /* Public */,
      12,    2,  100,    2, 0x0a /* Public */,
      16,    1,  105,    2, 0x0a /* Public */,
      19,    1,  108,    2, 0x0a /* Public */,
      22,    1,  111,    2, 0x0a /* Public */,
      24,    1,  114,    2, 0x0a /* Public */,
      26,    0,  117,    2, 0x0a /* Public */,
      27,    0,  118,    2, 0x08 /* Private */,
      28,    0,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 23,   21,
    QMetaType::Void, 0x80000000 | 25,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CDesignTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CDesignTreeView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigIsLayerView((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->layerChanged((*reinterpret_cast< CLayer*(*)>(_a[1]))); break;
        case 2: _t->slotNewController(); break;
        case 3: _t->slotOpenController(); break;
        case 4: _t->slotCloseController(); break;
        case 5: _t->slotSaveController(); break;
        case 6: _t->slotExportController(); break;
        case 7: _t->slotSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 8: _t->slotStartDrag((*reinterpret_cast< Qt::DropActions(*)>(_a[1]))); break;
        case 9: _t->slotDragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 10: _t->slotDragMoveEvent((*reinterpret_cast< QDragMoveEvent*(*)>(_a[1]))); break;
        case 11: _t->slotDropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 12: _t->slot_autoPage(); break;
        case 13: _t->addLayer(); break;
        case 14: _t->delLayer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CDesignTreeView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CDesignTreeView::sigIsLayerView)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CDesignTreeView::*)(CLayer * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CDesignTreeView::layerChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CDesignTreeView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CDesignTreeView.data,
    qt_meta_data_CDesignTreeView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CDesignTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CDesignTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CDesignTreeView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CDesignTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void CDesignTreeView::sigIsLayerView(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CDesignTreeView::layerChanged(CLayer * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
