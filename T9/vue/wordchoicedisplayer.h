#ifndef WORDCHOICEDISPLAYER_H
#define WORDCHOICEDISPLAYER_H

#include <QLabel>
#include "../model/word.hpp"

class WordChoiceDisplayer : public QLabel
{
    Q_OBJECT
public:
    WordChoiceDisplayer();

    void displayChoices();

public slots:
    void getNewWord(Word* newWord);
    void moveUp();
    void moveDown();
    void select();
    void displayPunctuation();

signals:
    void newWordSelected(Word* newWord);
    void newPunctuationSelected(QString punctuation);

private:
    Word *TypedWord;
    QVector<QString> *punctuationChoices;
    int punctuationSelected;
    bool punctuationIsDisplayed;
};

#endif // WORDCHOICEDISPLAYER_H
