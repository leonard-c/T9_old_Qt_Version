#ifndef CURSORARROWS_H
#define CURSORARROWS_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>

class CursorArrows : public QGroupBox
{
    Q_OBJECT
public:
    CursorArrows();

signals:
    void pressedLeft();
    void pressedRight();

private:
    QGridLayout *arrowsLayout;
    QPushButton* leftArrow;
    QPushButton* rightArrow;
};

#endif // CURSORARROWS_H
