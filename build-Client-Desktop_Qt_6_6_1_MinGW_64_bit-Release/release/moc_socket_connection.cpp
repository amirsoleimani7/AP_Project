/****************************************************************************
** Meta object code from reading C++ file 'socket_connection.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client/socket_connection.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socket_connection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSsocket_connectionENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSsocket_connectionENDCLASS = QtMocHelpers::stringData(
    "socket_connection",
    "delay",
    "",
    "readSocket",
    "witing_instructions",
    "QString&",
    "instruction",
    "discardSocket",
    "Doing_senging_file",
    "sendFile",
    "QTcpSocket*",
    "socket",
    "fileName"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSsocket_connectionENDCLASS_t {
    uint offsetsAndSizes[26];
    char stringdata0[18];
    char stringdata1[6];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[20];
    char stringdata5[9];
    char stringdata6[12];
    char stringdata7[14];
    char stringdata8[19];
    char stringdata9[9];
    char stringdata10[12];
    char stringdata11[7];
    char stringdata12[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSsocket_connectionENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSsocket_connectionENDCLASS_t qt_meta_stringdata_CLASSsocket_connectionENDCLASS = {
    {
        QT_MOC_LITERAL(0, 17),  // "socket_connection"
        QT_MOC_LITERAL(18, 5),  // "delay"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 10),  // "readSocket"
        QT_MOC_LITERAL(36, 19),  // "witing_instructions"
        QT_MOC_LITERAL(56, 8),  // "QString&"
        QT_MOC_LITERAL(65, 11),  // "instruction"
        QT_MOC_LITERAL(77, 13),  // "discardSocket"
        QT_MOC_LITERAL(91, 18),  // "Doing_senging_file"
        QT_MOC_LITERAL(110, 8),  // "sendFile"
        QT_MOC_LITERAL(119, 11),  // "QTcpSocket*"
        QT_MOC_LITERAL(131, 6),  // "socket"
        QT_MOC_LITERAL(138, 8)   // "fileName"
    },
    "socket_connection",
    "delay",
    "",
    "readSocket",
    "witing_instructions",
    "QString&",
    "instruction",
    "discardSocket",
    "Doing_senging_file",
    "sendFile",
    "QTcpSocket*",
    "socket",
    "fileName"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSsocket_connectionENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    1,   52,    2, 0x0a,    3 /* Public */,
       7,    0,   55,    2, 0x0a,    5 /* Public */,
       8,    0,   56,    2, 0x0a,    6 /* Public */,
       9,    2,   57,    2, 0x0a,    7 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString,   11,   12,

       0        // eod
};

Q_CONSTINIT const QMetaObject socket_connection::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSsocket_connectionENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSsocket_connectionENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSsocket_connectionENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<socket_connection, std::true_type>,
        // method 'delay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'readSocket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'witing_instructions'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        // method 'discardSocket'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'Doing_senging_file'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'sendFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>
    >,
    nullptr
} };

void socket_connection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<socket_connection *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->delay(); break;
        case 1: _t->readSocket(); break;
        case 2: _t->witing_instructions((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1]))); break;
        case 3: _t->discardSocket(); break;
        case 4: _t->Doing_senging_file(); break;
        case 5: _t->sendFile((*reinterpret_cast< std::add_pointer_t<QTcpSocket*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    }
}

const QMetaObject *socket_connection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *socket_connection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSsocket_connectionENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int socket_connection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
