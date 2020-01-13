/****************************************************************************
** Meta object code from reading C++ file 'eleWalletBackRPC.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CCTTFileMan/include/eleWalletBackRPC.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'eleWalletBackRPC.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EleWalletBackRPCCli_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EleWalletBackRPCCli_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EleWalletBackRPCCli_t qt_meta_stringdata_EleWalletBackRPCCli = {
    {
QT_MOC_LITERAL(0, 0, 19), // "EleWalletBackRPCCli"
QT_MOC_LITERAL(1, 20, 8), // "readData"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 10), // "connectSuc"
QT_MOC_LITERAL(4, 41, 10), // "connectErr"
QT_MOC_LITERAL(5, 52, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(6, 81, 10) // "connectDis"

    },
    "EleWalletBackRPCCli\0readData\0\0connectSuc\0"
    "connectErr\0QAbstractSocket::SocketError\0"
    "connectDis"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EleWalletBackRPCCli[] = {

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
       4,    1,   36,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,

       0        // eod
};

void EleWalletBackRPCCli::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EleWalletBackRPCCli *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readData(); break;
        case 1: _t->connectSuc(); break;
        case 2: _t->connectErr((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 3: _t->connectDis(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EleWalletBackRPCCli::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_EleWalletBackRPCCli.data,
    qt_meta_data_EleWalletBackRPCCli,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EleWalletBackRPCCli::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EleWalletBackRPCCli::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EleWalletBackRPCCli.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EleWalletBackRPCCli::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
