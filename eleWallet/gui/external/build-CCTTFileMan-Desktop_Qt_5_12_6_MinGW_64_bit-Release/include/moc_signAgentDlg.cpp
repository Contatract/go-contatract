/****************************************************************************
** Meta object code from reading C++ file 'signAgentDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CCTTFileMan/include/signAgentDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'signAgentDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SignAgentDlg_t {
    QByteArrayData data[7];
    char stringdata0[113];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SignAgentDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SignAgentDlg_t qt_meta_stringdata_SignAgentDlg = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SignAgentDlg"
QT_MOC_LITERAL(1, 13, 20), // "on_cancelBtn_clicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 23), // "on_timeRadioBtn_toggled"
QT_MOC_LITERAL(4, 59, 7), // "checked"
QT_MOC_LITERAL(5, 67, 23), // "on_flowRadioBtn_toggled"
QT_MOC_LITERAL(6, 91, 21) // "on_confirmBtn_clicked"

    },
    "SignAgentDlg\0on_cancelBtn_clicked\0\0"
    "on_timeRadioBtn_toggled\0checked\0"
    "on_flowRadioBtn_toggled\0on_confirmBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SignAgentDlg[] = {

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
       3,    1,   35,    2, 0x08 /* Private */,
       5,    1,   38,    2, 0x08 /* Private */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,

       0        // eod
};

void SignAgentDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SignAgentDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_cancelBtn_clicked(); break;
        case 1: _t->on_timeRadioBtn_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_flowRadioBtn_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_confirmBtn_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SignAgentDlg::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_SignAgentDlg.data,
    qt_meta_data_SignAgentDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SignAgentDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SignAgentDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SignAgentDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int SignAgentDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE