#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>

#include "textdisplayer.h"
#include "wordchoicedisplayer.h"
#include "selector.h"
#include "cursorarrows.h"


class TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor();

private:
    QGridLayout *globalLayout;
    QGroupBox *textBox;
    QGridLayout *textBoxLayout;
    TextDisplayer *text;
    CursorArrows *textArrows;

    QGroupBox *keyBoardBox;
    QGridLayout *keyBoardBoxLayout;
    QPushButton *keyBoard[12];

    QGroupBox *selectorBox;
    QGridLayout *selectorBoxLayout;
    QGroupBox *wordChoicesBox;
    QGridLayout *wordChoicesBoxLayout;
    WordChoiceDisplayer *wordChoices;
    Selector *arrows;
};

#endif // TEXTEDITOR_H
