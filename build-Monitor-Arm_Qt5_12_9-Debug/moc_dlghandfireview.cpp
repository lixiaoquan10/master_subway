/****************************************************************************
** Meta object code from reading C++ file 'dlghandfireview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/dialog/dlghandfireview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlghandfireview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dlgHandFireView_t {
    QByteArrayData data[8];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dlgHandFireView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dlgHandFireView_t qt_meta_stringdata_dlgHandFireView = {
    {
QT_MOC_LITERAL(0, 0, 15), // "dlgHandFireView"
QT_MOC_LITERAL(1, 16, 27), // "on_pushButton_close_clicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 26), // "on_pushButton_fire_clicked"
QT_MOC_LITERAL(4, 72, 19), // "slot_threadFinished"
QT_MOC_LITERAL(5, 92, 15), // "slot_dataLoaded"
QT_MOC_LITERAL(6, 108, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(7, 125, 8) // "rootItem"

    },
    "dlgHandFireView\0on_pushButton_close_clicked\0"
    "\0on_pushButton_fire_clicked\0"
    "slot_threadFinished\0slot_dataLoaded\0"
    "QTreeWidgetItem*\0rootItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dlgHandFireView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    1,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void dlgHandFireView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dlgHandFireView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButton_close_clicked(); break;
        case 1: _t->on_pushButton_fire_clicked(); break;
        case 2: _t->slot_threadFinished(); break;
        case 3: _t->slot_dataLoaded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject dlgHandFireView::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_dlgHandFireView.data,
    qt_meta_data_dlgHandFireView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *dlgHandFireView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dlgHandFireView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dlgHandFireView.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int dlgHandFireView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_LoadNodeDataThread_t {
    QByteArrayData data[6];
    char stringdata0[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoadNodeDataThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoadNodeDataThread_t qt_meta_stringdata_LoadNodeDataThread = {
    {
QT_MOC_LITERAL(0, 0, 18), // "LoadNodeDataThread"
QT_MOC_LITERAL(1, 19, 10), // "dataLoaded"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(4, 48, 8), // "rootItem"
QT_MOC_LITERAL(5, 57, 14) // "threadFinished"

    },
    "LoadNodeDataThread\0dataLoaded\0\0"
    "QTreeWidgetItem*\0rootItem\0threadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoadNodeDataThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void LoadNodeDataThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoadNodeDataThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dataLoaded((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->threadFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoadNodeDataThread::*)(QTreeWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoadNodeDataThread::dataLoaded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoadNodeDataThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoadNodeDataThread::threadFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LoadNodeDataThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_LoadNodeDataThread.data,
    qt_meta_data_LoadNodeDataThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LoadNodeDataThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoadNodeDataThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoadNodeDataThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int LoadNodeDataThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LoadNodeDataThread::dataLoaded(QTreeWidgetItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LoadNodeDataThread::threadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
