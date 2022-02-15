#ifndef TEXTDISPLAYER_H
#define TEXTDISPLAYER_H

#include <QApplication>
#include <QObject>
#include <QLabel>
#include <qmessagebox.h>
#include <string>
#include <QString>
#include <stdlib.h>
#include <iostream>

#include "../model/dictionary.hpp"
#include "../model/sentence.hpp"
#include "../model/word.hpp"

class TextDisplayer : public QLabel
{
    Q_OBJECT

public:
    TextDisplayer();
    TextDisplayer(std::string filename);

    void refreshfullSentence();
    void displayCursor();
    void updateWord(int position, int relativePosition, int originalWordSize, QString updated);

public slots:
    void addDigit(int digit);
    void rmDigit();
    void addWord(Word* selectedWord);
    void addPunctuation(QString punctuation);
    void moveLeft();
    void moveRight();

signals:
    void newDigitSequence(Word*);
    void disablePunctuation();
    void enablePunctuation();

private :
    Dictionary *usedDic;
    Sentence *phrase;
    QString displayedText;
    std::string currentWordDigits;
    struct CursorPosition{
        int position;
        int wordIndex;
        int relativePosition;
        int wordSize;
        int numberOfWords;
        bool isEditing;
        bool wordHasPunctuation;
    };
    CursorPosition cursor;
};

#endif // TEXTDISPLAYER_H
