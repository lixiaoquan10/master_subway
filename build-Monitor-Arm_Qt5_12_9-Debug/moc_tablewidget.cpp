/****************************************************************************
** Meta object code from reading C++ file 'tablewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/dialog/tablewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tablewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TableWidget_t {
    QByteArrayData data[15];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TableWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TableWidget_t qt_meta_stringdata_TableWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TableWidget"
QT_MOC_LITERAL(1, 12, 15), // "InsertSingleRow"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "row"
QT_MOC_LITERAL(4, 33, 7), // "content"
QT_MOC_LITERAL(5, 41, 5), // "brush"
QT_MOC_LITERAL(6, 47, 15), // "AppendSingleRow"
QT_MOC_LITERAL(7, 63, 15), // "RemoveSingleRow"
QT_MOC_LITERAL(8, 79, 19), // "RemoveLastSingleRow"
QT_MOC_LITERAL(9, 99, 11), // "SetItemText"
QT_MOC_LITERAL(10, 111, 4), // "nrow"
QT_MOC_LITERAL(11, 116, 7), // "ncolumn"
QT_MOC_LITERAL(12, 124, 7), // "strtext"
QT_MOC_LITERAL(13, 132, 11), // "SetRowColor"
QT_MOC_LITERAL(14, 144, 5) // "color"

    },
    "TableWidget\0InsertSingleRow\0\0row\0"
    "content\0brush\0AppendSingleRow\0"
    "RemoveSingleRow\0RemoveLastSingleRow\0"
    "SetItemText\0nrow\0ncolumn\0strtext\0"
    "SetRowColor\0color"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TableWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x0a /* Public */,
       1,    2,   61,    2, 0x2a /* Public | MethodCloned */,
       6,    2,   66,    2, 0x0a /* Public */,
       6,    1,   71,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   74,    2, 0x0a /* Public */,
       8,    0,   77,    2, 0x0a /* Public */,
       9,    3,   78,    2, 0x0a /* Public */,
      13,    2,   85,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool, QMetaType::Int, QMetaType::QStringList, QMetaType::QBrush,    3,    4,    5,
    QMetaType::Bool, QMetaType::Int, QMetaType::QStringList,    3,    4,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QBrush,    4,    5,
    QMetaType::Void, QMetaType::QStringList,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   10,   11,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QColor,   10,   14,

       0        // eod
};

void TableWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TableWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { bool _r = _t->InsertSingleRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QBrush(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->InsertSingleRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->AppendSingleRow((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QBrush(*)>(_a[2]))); break;
        case 3: _t->AppendSingleRow((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 4: _t->RemoveSingleRow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->RemoveLastSingleRow(); break;
        case 6: _t->SetItemText((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 7: _t->SetRowColor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QColor(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TableWidget::staticMetaObject = { {
    &QTableWidget::staticMetaObject,
    qt_meta_stringdata_TableWidget.data,
    qt_meta_data_TableWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TableWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TableWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TableWidget.stringdata0))
        return static_cast<void*>(this);
    return QTableWidget::qt_metacast(_clname);
}

int TableWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
