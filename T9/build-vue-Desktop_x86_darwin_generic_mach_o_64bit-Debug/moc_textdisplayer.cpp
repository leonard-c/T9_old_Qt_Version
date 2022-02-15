/****************************************************************************
** Meta object code from reading C++ file 'textdisplayer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../vue/textdisplayer.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textdisplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextDisplayer_t {
    const uint offsetsAndSize[30];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_TextDisplayer_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_TextDisplayer_t qt_meta_stringdata_TextDisplayer = {
    {
QT_MOC_LITERAL(0, 13), // "TextDisplayer"
QT_MOC_LITERAL(14, 16), // "newDigitSequence"
QT_MOC_LITERAL(31, 0), // ""
QT_MOC_LITERAL(32, 5), // "Word*"
QT_MOC_LITERAL(38, 18), // "disablePunctuation"
QT_MOC_LITERAL(57, 17), // "enablePunctuation"
QT_MOC_LITERAL(75, 8), // "addDigit"
QT_MOC_LITERAL(84, 5), // "digit"
QT_MOC_LITERAL(90, 7), // "rmDigit"
QT_MOC_LITERAL(98, 7), // "addWord"
QT_MOC_LITERAL(106, 12), // "selectedWord"
QT_MOC_LITERAL(119, 14), // "addPunctuation"
QT_MOC_LITERAL(134, 11), // "punctuation"
QT_MOC_LITERAL(146, 8), // "moveLeft"
QT_MOC_LITERAL(155, 9) // "moveRight"

    },
    "TextDisplayer\0newDigitSequence\0\0Word*\0"
    "disablePunctuation\0enablePunctuation\0"
    "addDigit\0digit\0rmDigit\0addWord\0"
    "selectedWord\0addPunctuation\0punctuation\0"
    "moveLeft\0moveRight"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextDisplayer[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,
       4,    0,   71,    2, 0x06,    3 /* Public */,
       5,    0,   72,    2, 0x06,    4 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   73,    2, 0x0a,    5 /* Public */,
       8,    0,   76,    2, 0x0a,    7 /* Public */,
       9,    1,   77,    2, 0x0a,    8 /* Public */,
      11,    1,   80,    2, 0x0a,   10 /* Public */,
      13,    0,   83,    2, 0x0a,   12 /* Public */,
      14,    0,   84,    2, 0x0a,   13 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TextDisplayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TextDisplayer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newDigitSequence((*reinterpret_cast< Word*(*)>(_a[1]))); break;
        case 1: _t->disablePunctuation(); break;
        case 2: _t->enablePunctuation(); break;
        case 3: _t->addDigit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->rmDigit(); break;
        case 5: _t->addWord((*reinterpret_cast< Word*(*)>(_a[1]))); break;
        case 6: _t->addPunctuation((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->moveLeft(); break;
        case 8: _t->moveRight(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextDisplayer::*)(Word * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextDisplayer::newDigitSequence)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TextDisplayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextDisplayer::disablePunctuation)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TextDisplayer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextDisplayer::enablePunctuation)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject TextDisplayer::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_TextDisplayer.offsetsAndSize,
    qt_meta_data_TextDisplayer,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_TextDisplayer_t
, QtPrivate::TypeAndForceComplete<TextDisplayer, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Word *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Word *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *TextDisplayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextDisplayer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextDisplayer.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int TextDisplayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void TextDisplayer::newDigitSequence(Word * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TextDisplayer::disablePunctuation()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TextDisplayer::enablePunctuation()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
