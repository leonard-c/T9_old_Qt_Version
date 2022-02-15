/****************************************************************************
** Meta object code from reading C++ file 'selector.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../vue/selector.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'selector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Selector_t {
    const uint offsetsAndSize[10];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Selector_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Selector_t qt_meta_stringdata_Selector = {
    {
QT_MOC_LITERAL(0, 8), // "Selector"
QT_MOC_LITERAL(9, 9), // "pressedUp"
QT_MOC_LITERAL(19, 0), // ""
QT_MOC_LITERAL(20, 11), // "pressedDown"
QT_MOC_LITERAL(32, 13) // "pressedSelect"

    },
    "Selector\0pressedUp\0\0pressedDown\0"
    "pressedSelect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Selector[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x06,    1 /* Public */,
       3,    0,   33,    2, 0x06,    2 /* Public */,
       4,    0,   34,    2, 0x06,    3 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Selector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Selector *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pressedUp(); break;
        case 1: _t->pressedDown(); break;
        case 2: _t->pressedSelect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Selector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Selector::pressedUp)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Selector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Selector::pressedDown)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Selector::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Selector::pressedSelect)) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject Selector::staticMetaObject = { {
    QMetaObject::SuperData::link<QGroupBox::staticMetaObject>(),
    qt_meta_stringdata_Selector.offsetsAndSize,
    qt_meta_data_Selector,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Selector_t
, QtPrivate::TypeAndForceComplete<Selector, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>



>,
    nullptr
} };


const QMetaObject *Selector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Selector::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Selector.stringdata0))
        return static_cast<void*>(this);
    return QGroupBox::qt_metacast(_clname);
}

int Selector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Selector::pressedUp()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Selector::pressedDown()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Selector::pressedSelect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
