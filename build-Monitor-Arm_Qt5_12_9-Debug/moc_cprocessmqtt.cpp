/****************************************************************************
** Meta object code from reading C++ file 'cprocessmqtt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/business/cprocessmqtt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprocessmqtt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CprocessMqtt_t {
    QByteArrayData data[26];
    char stringdata0[430];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CprocessMqtt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CprocessMqtt_t qt_meta_stringdata_CprocessMqtt = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CprocessMqtt"
QT_MOC_LITERAL(1, 13, 13), // "connectStatus"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "status"
QT_MOC_LITERAL(4, 35, 14), // "hostControlMsg"
QT_MOC_LITERAL(5, 50, 4), // "type"
QT_MOC_LITERAL(6, 55, 14), // "publishMessage"
QT_MOC_LITERAL(7, 70, 5), // "topic"
QT_MOC_LITERAL(8, 76, 7), // "message"
QT_MOC_LITERAL(9, 84, 25), // "slot_updateLogStateChange"
QT_MOC_LITERAL(10, 110, 23), // "slot_brokerDisconnected"
QT_MOC_LITERAL(11, 134, 26), // "slot_handleMessageReceived"
QT_MOC_LITERAL(12, 161, 14), // "QMqttTopicName"
QT_MOC_LITERAL(13, 176, 17), // "slot_pingResponse"
QT_MOC_LITERAL(14, 194, 16), // "slot_requestPing"
QT_MOC_LITERAL(15, 211, 22), // "slot_reconnectToBroker"
QT_MOC_LITERAL(16, 234, 25), // "slot_messageStatusChanged"
QT_MOC_LITERAL(17, 260, 8), // "packetId"
QT_MOC_LITERAL(18, 269, 20), // "QMqtt::MessageStatus"
QT_MOC_LITERAL(19, 290, 23), // "slot_ResendTimerTimeout"
QT_MOC_LITERAL(20, 314, 24), // "slot_sendDeviceStatusMsg"
QT_MOC_LITERAL(21, 339, 8), // "CObject*"
QT_MOC_LITERAL(22, 348, 6), // "object"
QT_MOC_LITERAL(23, 355, 30), // "isDistributionEmergencyOrFault"
QT_MOC_LITERAL(24, 386, 26), // "slot_uploadAllDeviceStatus"
QT_MOC_LITERAL(25, 413, 16) // "slot_testMessage"

    },
    "CprocessMqtt\0connectStatus\0\0status\0"
    "hostControlMsg\0type\0publishMessage\0"
    "topic\0message\0slot_updateLogStateChange\0"
    "slot_brokerDisconnected\0"
    "slot_handleMessageReceived\0QMqttTopicName\0"
    "slot_pingResponse\0slot_requestPing\0"
    "slot_reconnectToBroker\0slot_messageStatusChanged\0"
    "packetId\0QMqtt::MessageStatus\0"
    "slot_ResendTimerTimeout\0"
    "slot_sendDeviceStatusMsg\0CObject*\0"
    "object\0isDistributionEmergencyOrFault\0"
    "slot_uploadAllDeviceStatus\0slot_testMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CprocessMqtt[] = {

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
       6,    2,   95,    2, 0x0a /* Public */,
       9,    0,  100,    2, 0x0a /* Public */,
      10,    0,  101,    2, 0x0a /* Public */,
      11,    2,  102,    2, 0x0a /* Public */,
      13,    0,  107,    2, 0x0a /* Public */,
      14,    0,  108,    2, 0x0a /* Public */,
      15,    0,  109,    2, 0x0a /* Public */,
      16,    2,  110,    2, 0x0a /* Public */,
      19,    0,  115,    2, 0x0a /* Public */,
      20,    2,  116,    2, 0x0a /* Public */,
      20,    1,  121,    2, 0x2a /* Public | MethodCloned */,
      24,    0,  124,    2, 0x0a /* Public */,
      25,    0,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::QByteArray,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 12,    8,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, 0x80000000 | 18,   17,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21, QMetaType::Bool,   22,   23,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CprocessMqtt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CprocessMqtt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->hostControlMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: { bool _r = _t->publishMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->slot_updateLogStateChange(); break;
        case 4: _t->slot_brokerDisconnected(); break;
        case 5: _t->slot_handleMessageReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QMqttTopicName(*)>(_a[2]))); break;
        case 6: _t->slot_pingResponse(); break;
        case 7: _t->slot_requestPing(); break;
        case 8: _t->slot_reconnectToBroker(); break;
        case 9: _t->slot_messageStatusChanged((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< QMqtt::MessageStatus(*)>(_a[2]))); break;
        case 10: _t->slot_ResendTimerTimeout(); break;
        case 11: _t->slot_sendDeviceStatusMsg((*reinterpret_cast< CObject*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->slot_sendDeviceStatusMsg((*reinterpret_cast< CObject*(*)>(_a[1]))); break;
        case 13: _t->slot_uploadAllDeviceStatus(); break;
        case 14: _t->slot_testMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttTopicName >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CprocessMqtt::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CprocessMqtt::connectStatus)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CprocessMqtt::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CprocessMqtt::hostControlMsg)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CprocessMqtt::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CprocessMqtt.data,
    qt_meta_data_CprocessMqtt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CprocessMqtt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CprocessMqtt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CprocessMqtt.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CprocessMqtt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void CprocessMqtt::connectStatus(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CprocessMqtt::hostControlMsg(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
