#include "cursorarrows.h"


CursorArrows::CursorArrows() : QGroupBox()
{
    arrowsLayout = new QGridLayout;
    leftArrow = new QPushButton("<");
    rightArrow = new QPushButton(">");
    arrowsLayout->addWidget(leftArrow, 0, 0);
    arrowsLayout->addWidget(rightArrow, 0, 1);
    setLayout(arrowsLayout);

    setFocusPolicy(Qt::TabFocus); // to avoid any highlight on the buttons

    // Linking the buttons with the keyboard
    leftArrow->setShortcut(Qt::Key_Left);
    rightArrow->setShortcut(Qt::Key_Right);

    QObject::connect(leftArrow, SIGNAL(QPushButton::pressed), this, SLOT([this]{ emit pressedLeft(); }));
    QObject::connect(rightArrow, SIGNAL(QPushButton::pressed), this, SLOT([this]{ emit pressedRight(); }));
}
