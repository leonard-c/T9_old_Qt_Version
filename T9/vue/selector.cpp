#include "selector.h"

Selector::Selector() : QGroupBox()
{
    selectorLayout = new QGridLayout;
    upArrow = new QPushButton("▲\nUp");
    selectorLayout->addWidget(upArrow, 0, 0);
    downArrow = new QPushButton("▼\nDown");
    selectorLayout->addWidget(downArrow, 1, 0);
    select = new QPushButton("\n↵\nOK\n\n");
    selectorLayout->addWidget(select, 0, 1, 2, 1);
    setLayout(selectorLayout);

    // Linking the buttons with the keyboard
    upArrow->setShortcut(Qt::Key_Up);
    downArrow->setShortcut(Qt::Key_Down);
    // 2 ways of selecting the word
    select->setShortcut(Qt::Key_Return);
    QShortcut *space = new QShortcut(Qt::Key_Space, this);
    QObject::connect(space, SIGNAL(QShortcut::activated), select, SLOT(QPushButton::click));

    QObject::connect(upArrow, SIGNAL(QPushButton::pressed), this, SLOT([this]{ emit pressedUp(); }));
    QObject::connect(downArrow, SIGNAL(QPushButton::pressed), this, SLOT([this]{ emit pressedDown(); }));
    QObject::connect(select, SIGNAL(QPushButton::pressed), this, SLOT([this]{ emit pressedSelect(); }));
}
