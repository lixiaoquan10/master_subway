/****************************************************************************
** Meta object code from reading C++ file 'ccommunicationmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BService/process/ccommunicationmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccommunicationmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CCommunicationManager_t {
    QByteArrayData data[19];
    char stringdata0[296];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CCommunicationManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CCommunicationManager_t qt_meta_stringdata_CCommunicationManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CCommunicationManager"
QT_MOC_LITERAL(1, 22, 18), // "sig_ReceivedPacket"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 13), // "nSerialNumber"
QT_MOC_LITERAL(4, 56, 14), // "sig_ReciveData"
QT_MOC_LITERAL(5, 71, 8), // "lineName"
QT_MOC_LITERAL(6, 80, 8), // "infoType"
QT_MOC_LITERAL(7, 89, 13), // "controlDomain"
QT_MOC_LITERAL(8, 103, 4), // "data"
QT_MOC_LITERAL(9, 108, 12), // "doReciveData"
QT_MOC_LITERAL(10, 121, 4), // "name"
QT_MOC_LITERAL(11, 126, 21), // "slot_LinkageFlagReset"
QT_MOC_LITERAL(12, 148, 15), // "slot_ARTUDIsend"
QT_MOC_LITERAL(13, 164, 19), // "handleLedReciveData"
QT_MOC_LITERAL(14, 184, 23), // "handleLinkageReciveData"
QT_MOC_LITERAL(15, 208, 20), // "handleTestReciveData"
QT_MOC_LITERAL(16, 229, 20), // "handleCan1ReciveData"
QT_MOC_LITERAL(17, 250, 20), // "handleCan2ReciveData"
QT_MOC_LITERAL(18, 271, 24) // "updataRecentSerialNumber"

    },
    "CCommunicationManager\0sig_ReceivedPacket\0"
    "\0nSerialNumber\0sig_ReciveData\0lineName\0"
    "infoType\0controlDomain\0data\0doReciveData\0"
    "name\0slot_LinkageFlagReset\0slot_ARTUDIsend\0"
    "handleLedReciveData\0handleLinkageReciveData\0"
    "handleTestReciveData\0handleCan1ReciveData\0"
    "handleCan2ReciveData\0updataRecentSerialNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CCommunicationManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    4,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    2,   81,    2, 0x0a /* Public */,
      11,    0,   86,    2, 0x0a /* Public */,
      12,    0,   87,    2, 0x0a /* Public */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,
      15,    0,   90,    2, 0x08 /* Private */,
      16,    0,   91,    2, 0x08 /* Private */,
      17,    0,   92,    2, 0x08 /* Private */,
      18,    2,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::QVariantHash, QMetaType::QByteArray,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   10,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,    3,

       0        // eod
};

void CCommunicationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CCommunicationManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_ReceivedPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_ReciveData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 2: _t->doReciveData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 3: _t->slot_LinkageFlagReset(); break;
        case 4: _t->slot_ARTUDIsend(); break;
        case 5: _t->handleLedReciveData(); break;
        case 6: _t->handleLinkageReciveData(); break;
        case 7: _t->handleTestReciveData(); break;
        case 8: _t->handleCan1ReciveData(); break;
        case 9: _t->handleCan2ReciveData(); break;
        case 10: _t->updataRecentSerialNumber((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CCommunicationManager::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CCommunicationManager::sig_ReceivedPacket)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CCommunicationManager::*)(const QString & , const int & , const QHash<QString,QVariant> & , const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CCommunicationManager::sig_ReciveData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CCommunicationManager::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CCommunicationManager.data,
    qt_meta_data_CCommunicationManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CCommunicationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CCommunicationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CCommunicationManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CCommunicationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void CCommunicationManager::sig_ReceivedPacket(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CCommunicationManager::sig_ReciveData(const QString & _t1, const int & _t2, const QHash<QString,QVariant> & _t3, const QByteArray & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
