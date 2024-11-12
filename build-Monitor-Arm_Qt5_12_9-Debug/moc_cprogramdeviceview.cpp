/****************************************************************************
** Meta object code from reading C++ file 'cprogramdeviceview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/widget/cprogramdeviceview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprogramdeviceview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CProgramDeviceView_t {
    QByteArrayData data[21];
    char stringdata0[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CProgramDeviceView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CProgramDeviceView_t qt_meta_stringdata_CProgramDeviceView = {
    {
QT_MOC_LITERAL(0, 0, 18), // "CProgramDeviceView"
QT_MOC_LITERAL(1, 19, 14), // "slot_ChangeAdd"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 21), // "slot_ChangeDeviceType"
QT_MOC_LITERAL(4, 57, 12), // "slot_Lighten"
QT_MOC_LITERAL(5, 70, 15), // "slot_CloseLight"
QT_MOC_LITERAL(6, 86, 13), // "slot_AllClose"
QT_MOC_LITERAL(7, 100, 9), // "slot_Left"
QT_MOC_LITERAL(8, 110, 10), // "slot_Right"
QT_MOC_LITERAL(9, 121, 14), // "slot_StartTest"
QT_MOC_LITERAL(10, 136, 13), // "slot_StopTest"
QT_MOC_LITERAL(11, 150, 19), // "slot_StartEmergency"
QT_MOC_LITERAL(12, 170, 18), // "slot_StopEmergency"
QT_MOC_LITERAL(13, 189, 20), // "slot_ReadLampVersion"
QT_MOC_LITERAL(14, 210, 20), // "slot_CloseBatteryOut"
QT_MOC_LITERAL(15, 231, 19), // "slot_BatteryOutKeep"
QT_MOC_LITERAL(16, 251, 18), // "slot_uploadOldLamp"
QT_MOC_LITERAL(17, 270, 30), // "slot_nologinSendToDistribution"
QT_MOC_LITERAL(18, 301, 20), // "on_tableView_clicked"
QT_MOC_LITERAL(19, 322, 11), // "QModelIndex"
QT_MOC_LITERAL(20, 334, 5) // "index"

    },
    "CProgramDeviceView\0slot_ChangeAdd\0\0"
    "slot_ChangeDeviceType\0slot_Lighten\0"
    "slot_CloseLight\0slot_AllClose\0slot_Left\0"
    "slot_Right\0slot_StartTest\0slot_StopTest\0"
    "slot_StartEmergency\0slot_StopEmergency\0"
    "slot_ReadLampVersion\0slot_CloseBatteryOut\0"
    "slot_BatteryOutKeep\0slot_uploadOldLamp\0"
    "slot_nologinSendToDistribution\0"
    "on_tableView_clicked\0QModelIndex\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CProgramDeviceView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    1,  115,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,   20,

       0        // eod
};

void CProgramDeviceView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CProgramDeviceView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_ChangeAdd(); break;
        case 1: _t->slot_ChangeDeviceType(); break;
        case 2: _t->slot_Lighten(); break;
        case 3: _t->slot_CloseLight(); break;
        case 4: _t->slot_AllClose(); break;
        case 5: _t->slot_Left(); break;
        case 6: _t->slot_Right(); break;
        case 7: _t->slot_StartTest(); break;
        case 8: _t->slot_StopTest(); break;
        case 9: _t->slot_StartEmergency(); break;
        case 10: _t->slot_StopEmergency(); break;
        case 11: _t->slot_ReadLampVersion(); break;
        case 12: _t->slot_CloseBatteryOut(); break;
        case 13: _t->slot_BatteryOutKeep(); break;
        case 14: _t->slot_uploadOldLamp(); break;
        case 15: _t->slot_nologinSendToDistribution(); break;
        case 16: _t->on_tableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CProgramDeviceView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CProgramDeviceView.data,
    qt_meta_data_CProgramDeviceView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CProgramDeviceView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CProgramDeviceView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CProgramDeviceView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CProgramDeviceView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
