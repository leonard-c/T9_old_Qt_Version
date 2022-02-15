#include "wordchoicedisplayer.h"

#include <QDebug>

WordChoiceDisplayer::WordChoiceDisplayer() : QLabel()
{
    TypedWord = NULL;
    punctuationChoices = new QVector<QString>({".", "!", "?"});
    punctuationSelected=0;
    punctuationIsDisplayed = false;
    setWordWrap(true);
}


// Methods :

void WordChoiceDisplayer::displayChoices()
{
    setText("");
    if ((TypedWord != NULL) && (TypedWord->getWordList().size()!=0))
    {
        int ChoosenWordIndex = TypedWord->getChoosenWordIndex();
        int i = 0;
        for (std::string word : TypedWord->getWordList())
        {
            if (i==ChoosenWordIndex)
                setText(text()+"<center><span style='background-color:grey;'>"+
                        QString::fromStdString(word)+
                        "</span></center>");
            else
                setText(text()+"<center>"+
                        QString::fromStdString(word)+
                        "</center>");

            i++;
        }
    }
}


// Slots :

void WordChoiceDisplayer::getNewWord(Word* newWord)
{
    TypedWord = newWord;
    displayChoices();
}


void WordChoiceDisplayer::moveUp()
{
    if (punctuationIsDisplayed){
        punctuationSelected = punctuationSelected-1;
        if (punctuationSelected<0)
            punctuationSelected = punctuationChoices->size()-1;
        displayPunctuation();
    } else {
        int newIndex = (TypedWord->getChoosenWordIndex()-1)%(TypedWord->getWordList().size());
        if (TypedWord->getChoosenWordIndex()==0)
            newIndex = TypedWord->getWordList().size()-1;
        TypedWord->changeChoosenWord(newIndex);
        displayChoices();
    }
}

void WordChoiceDisplayer::moveDown()
{
    if (punctuationIsDisplayed){
        punctuationSelected = (punctuationSelected+1)%punctuationChoices->size();
        displayPunctuation();
    } else {
        int newIndex = (TypedWord->getChoosenWordIndex()+1)%(TypedWord->getWordList().size());
        TypedWord->changeChoosenWord(newIndex);
        displayChoices();
    }
}

void WordChoiceDisplayer::select()
{
    if (punctuationIsDisplayed) {
        emit newPunctuationSelected(punctuationChoices->at(punctuationSelected));
        punctuationIsDisplayed = false;
    } else {
        if ((TypedWord != NULL) && (TypedWord->getWordList().size()!=0))
            emit newWordSelected(TypedWord);
    }

    TypedWord = NULL;
    displayChoices();
}

void WordChoiceDisplayer::displayPunctuation()
{
    setText("");

    for (int i=0; i<punctuationChoices->size(); i++) {
        if (i==punctuationSelected)
            setText(text()+"<center><span style='background-color:grey;'>"+
                    punctuationChoices->at(i)+
                    "</span></center>\n");
        else
            setText(text()+"<center>"+
                    punctuationChoices->at(i)+
                    "</center>\n");
    }
    punctuationIsDisplayed = true;
}
