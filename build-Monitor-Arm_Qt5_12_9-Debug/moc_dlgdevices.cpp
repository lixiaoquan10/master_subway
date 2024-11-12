/****************************************************************************
** Meta object code from reading C++ file 'dlgdevices.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/dialog/dlgdevices.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlgdevices.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_dlgDevices_t {
    QByteArrayData data[19];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_dlgDevices_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_dlgDevices_t qt_meta_stringdata_dlgDevices = {
    {
QT_MOC_LITERAL(0, 0, 10), // "dlgDevices"
QT_MOC_LITERAL(1, 11, 14), // "slot_StartTest"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 13), // "slot_StopTest"
QT_MOC_LITERAL(4, 41, 19), // "slot_StartEmergency"
QT_MOC_LITERAL(5, 61, 18), // "slot_StopEmergency"
QT_MOC_LITERAL(6, 80, 20), // "slot_CloseBatteryOut"
QT_MOC_LITERAL(7, 101, 19), // "slot_BatteryOutKeep"
QT_MOC_LITERAL(8, 121, 14), // "slot_deviceUse"
QT_MOC_LITERAL(9, 136, 17), // "slot_deviceForbid"
QT_MOC_LITERAL(10, 154, 23), // "slot_DeviceProductionId"
QT_MOC_LITERAL(11, 178, 20), // "on_tableView_clicked"
QT_MOC_LITERAL(12, 199, 11), // "QModelIndex"
QT_MOC_LITERAL(13, 211, 5), // "index"
QT_MOC_LITERAL(14, 217, 35), // "on_ReadBatteryStatus_Button_c..."
QT_MOC_LITERAL(15, 253, 29), // "on_pageScrollBar_valueChanged"
QT_MOC_LITERAL(16, 283, 5), // "value"
QT_MOC_LITERAL(17, 289, 26), // "on_nextPage_Button_clicked"
QT_MOC_LITERAL(18, 316, 30) // "on_previousPage_Button_clicked"

    },
    "dlgDevices\0slot_StartTest\0\0slot_StopTest\0"
    "slot_StartEmergency\0slot_StopEmergency\0"
    "slot_CloseBatteryOut\0slot_BatteryOutKeep\0"
    "slot_deviceUse\0slot_deviceForbid\0"
    "slot_DeviceProductionId\0on_tableView_clicked\0"
    "QModelIndex\0index\0on_ReadBatteryStatus_Button_clicked\0"
    "on_pageScrollBar_valueChanged\0value\0"
    "on_nextPage_Button_clicked\0"
    "on_previousPage_Button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_dlgDevices[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    0,   88,    2, 0x08 /* Private */,
       7,    0,   89,    2, 0x08 /* Private */,
       8,    0,   90,    2, 0x08 /* Private */,
       9,    0,   91,    2, 0x08 /* Private */,
      10,    0,   92,    2, 0x08 /* Private */,
      11,    1,   93,    2, 0x08 /* Private */,
      14,    0,   96,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    0,  101,    2, 0x08 /* Private */,

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
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void dlgDevices::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<dlgDevices *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_StartTest(); break;
        case 1: _t->slot_StopTest(); break;
        case 2: _t->slot_StartEmergency(); break;
        case 3: _t->slot_StopEmergency(); break;
        case 4: _t->slot_CloseBatteryOut(); break;
        case 5: _t->slot_BatteryOutKeep(); break;
        case 6: _t->slot_deviceUse(); break;
        case 7: _t->slot_deviceForbid(); break;
        case 8: _t->slot_DeviceProductionId(); break;
        case 9: _t->on_tableView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 10: _t->on_ReadBatteryStatus_Button_clicked(); break;
        case 11: _t->on_pageScrollBar_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_nextPage_Button_clicked(); break;
        case 13: _t->on_previousPage_Button_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject dlgDevices::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_dlgDevices.data,
    qt_meta_data_dlgDevices,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *dlgDevices::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *dlgDevices::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_dlgDevices.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int dlgDevices::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
