#ifndef SELECTOR_H
#define SELECTOR_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QPushButton>
#include <QShortcut>

class Selector : public QGroupBox
{
    Q_OBJECT
public:
    Selector();

signals :
    void pressedUp();
    void pressedDown();
    void pressedSelect();

private:
    QGridLayout *selectorLayout;
    QPushButton *upArrow;
    QPushButton *downArrow;
    QPushButton *select;
};

#endif // SELECTOR_H
