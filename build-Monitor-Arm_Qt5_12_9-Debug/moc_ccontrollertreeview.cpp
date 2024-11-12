/****************************************************************************
** Meta object code from reading C++ file 'ccontrollertreeview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/view/ccontrollertreeview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccontrollertreeview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CControllerTreeView_t {
    QByteArrayData data[18];
    char stringdata0[275];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CControllerTreeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CControllerTreeView_t qt_meta_stringdata_CControllerTreeView = {
    {
QT_MOC_LITERAL(0, 0, 19), // "CControllerTreeView"
QT_MOC_LITERAL(1, 20, 19), // "sigSelectionChanged"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "QItemSelection"
QT_MOC_LITERAL(4, 56, 8), // "selected"
QT_MOC_LITERAL(5, 65, 10), // "deselected"
QT_MOC_LITERAL(6, 76, 15), // "signalStartDrag"
QT_MOC_LITERAL(7, 92, 15), // "Qt::DropActions"
QT_MOC_LITERAL(8, 108, 16), // "supportedActions"
QT_MOC_LITERAL(9, 125, 20), // "signalDragEnterEvent"
QT_MOC_LITERAL(10, 146, 16), // "QDragEnterEvent*"
QT_MOC_LITERAL(11, 163, 5), // "event"
QT_MOC_LITERAL(12, 169, 19), // "signalDragMoveEvent"
QT_MOC_LITERAL(13, 189, 15), // "QDragMoveEvent*"
QT_MOC_LITERAL(14, 205, 15), // "signalDropEvent"
QT_MOC_LITERAL(15, 221, 11), // "QDropEvent*"
QT_MOC_LITERAL(16, 233, 22), // "signalContextMenuEvent"
QT_MOC_LITERAL(17, 256, 18) // "QContextMenuEvent*"

    },
    "CControllerTreeView\0sigSelectionChanged\0"
    "\0QItemSelection\0selected\0deselected\0"
    "signalStartDrag\0Qt::DropActions\0"
    "supportedActions\0signalDragEnterEvent\0"
    "QDragEnterEvent*\0event\0signalDragMoveEvent\0"
    "QDragMoveEvent*\0signalDropEvent\0"
    "QDropEvent*\0signalContextMenuEvent\0"
    "QContextMenuEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CControllerTreeView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    1,   49,    2, 0x06 /* Public */,
       9,    1,   52,    2, 0x06 /* Public */,
      12,    1,   55,    2, 0x06 /* Public */,
      14,    1,   58,    2, 0x06 /* Public */,
      16,    1,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   11,
    QMetaType::Void, 0x80000000 | 15,   11,
    QMetaType::Void, 0x80000000 | 17,   11,

       0        // eod
};

void CControllerTreeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CControllerTreeView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigSelectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 1: _t->signalStartDrag((*reinterpret_cast< Qt::DropActions(*)>(_a[1]))); break;
        case 2: _t->signalDragEnterEvent((*reinterpret_cast< QDragEnterEvent*(*)>(_a[1]))); break;
        case 3: _t->signalDragMoveEvent((*reinterpret_cast< QDragMoveEvent*(*)>(_a[1]))); break;
        case 4: _t->signalDropEvent((*reinterpret_cast< QDropEvent*(*)>(_a[1]))); break;
        case 5: _t->signalContextMenuEvent((*reinterpret_cast< QContextMenuEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            using _t = void (CControllerTreeView::*)(const QItemSelection & , const QItemSelection & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CControllerTreeView::sigSelectionChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CControllerTreeView::*)(Qt::DropActions );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CControllerTreeView::signalStartDrag)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CControllerTreeView::*)(QDragEnterEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CControllerTreeView::signalDragEnterEvent)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CControllerTreeView::*)(QDragMoveEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CControllerTreeView::signalDragMoveEvent)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CControllerTreeView::*)(QDropEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CControllerTreeView::signalDropEvent)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CControllerTreeView::*)(QContextMenuEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CControllerTreeView::signalContextMenuEvent)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CControllerTreeView::staticMetaObject = { {
    &QTreeView::staticMetaObject,
    qt_meta_stringdata_CControllerTreeView.data,
    qt_meta_data_CControllerTreeView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CControllerTreeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CControllerTreeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CControllerTreeView.stringdata0))
        return static_cast<void*>(this);
    return QTreeView::qt_metacast(_clname);
}

int CControllerTreeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CControllerTreeView::sigSelectionChanged(const QItemSelection & _t1, const QItemSelection & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CControllerTreeView::signalStartDrag(Qt::DropActions _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CControllerTreeView::signalDragEnterEvent(QDragEnterEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CControllerTreeView::signalDragMoveEvent(QDragMoveEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CControllerTreeView::signalDropEvent(QDropEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CControllerTreeView::signalContextMenuEvent(QContextMenuEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
