#include "textdisplayer.h"
#include <QApplication>

TextDisplayer::TextDisplayer() : QLabel()
{
    usedDic = new Dictionary("../../../../model/WordList/fr_sans_accents.txt");
    Word *firstWord = new Word(usedDic);
    phrase = new Sentence;
    phrase->addWord(firstWord);

    displayedText = "";
    currentWordDigits = "";
    cursor.position = 0;
    cursor.wordIndex=0;
    cursor.wordSize = 0;
    cursor.relativePosition = 0;
    cursor.numberOfWords = 1;
    cursor.isEditing = true;
    cursor.wordHasPunctuation = false;

    displayCursor();
    setWordWrap(true);
}

TextDisplayer::TextDisplayer(std::string filename) : QLabel()
{
    usedDic = new Dictionary(filename);
    Word *firstWord = new Word(usedDic);
    phrase = new Sentence;
    phrase->addWord(firstWord);

    displayedText = "";
    currentWordDigits = "";
    cursor.position = 0;
    cursor.wordIndex=0;
    cursor.wordSize = 0;
    cursor.relativePosition = 0;
    cursor.numberOfWords = 1;
    cursor.isEditing = true;
    cursor.wordHasPunctuation = false;

    displayCursor();
    setWordWrap(true);
}


// ------------------------------------------------------------------------------------------
// Methods :

void TextDisplayer::refreshfullSentence()
{
    displayedText = "";
    int i = 0;
    for (Word *wordOnPhrase : *phrase->getWords())
    {
        if (i!=cursor.numberOfWords) {
            displayedText+=QString::fromStdString(wordOnPhrase->getChoosenWord());
            displayedText.chop(1);
        } else
            displayedText+=QString::fromStdString(wordOnPhrase->getDigitSequence());
        displayedText+=QString::fromStdString(phrase->getPunctuation(i));
        i++;
    }
    displayCursor();
}

void TextDisplayer::displayCursor()
{
   QString textWithCursor = displayedText;
    if (cursor.position == (int)textWithCursor.size())
        textWithCursor+="<span style='background-color:grey;'>&nbsp;</span>";
    else
        textWithCursor.replace(cursor.position, 1,
                               "<span style='background-color:grey;'>"+(QString)textWithCursor.at(cursor.position)+"</span>");
    setText(textWithCursor);
}

void TextDisplayer::updateWord(int position, int relativePosition, int originalWordSize, QString updated)
{
    try {
        if (updated.size()==originalWordSize)
            displayedText.replace(position-relativePosition, originalWordSize, updated);
        else if (updated.size()>originalWordSize) {
            for (int i=0; i<updated.size()-originalWordSize; i++)
                displayedText.insert(position, " ");
            displayedText.replace(position-relativePosition, updated.size(), updated);
        } else {
            displayedText.remove(position-(originalWordSize-updated.size()), originalWordSize-updated.size());
            displayedText.replace(position-relativePosition, updated.size(), updated);
        }
        displayCursor();
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}


// ------------------------------------------------------------------------------------------
// Slots :

void TextDisplayer::addDigit(int digit)
{
    // Indicators
    bool endOfbranchIsReached = false;    // Indicate if we must execute the Vue part or not
    int beyondEndOfBranch=0;

    if(cursor.wordHasPunctuation&&(cursor.relativePosition==cursor.wordSize+1)) {
        /* There is punctuation and the cursor is right behind it */
        QMessageBox *reachedEndOfbranch = new QMessageBox;
        reachedEndOfbranch->setText("You can't add a word here.\nPlease type your word after the space.");
        reachedEndOfbranch->exec();
        return ;
    }


    // Dealing with the model part
    if (cursor.relativePosition==cursor.wordSize) {
        /* The cursor is at the end of the word */
        if (!phrase->getWord(cursor.wordIndex)->ChildIsNull(digit)) {
            phrase->getWord(cursor.wordIndex)->addDigit(digit);
            emit newDigitSequence(phrase->getWord(cursor.wordIndex));
        } else {
            QMessageBox *reachedEndOfbranch = new QMessageBox;
            reachedEndOfbranch->setText("There's no word begining by "+
                                        QString::fromStdString(currentWordDigits+std::to_string(digit)));
            reachedEndOfbranch->exec();
            endOfbranchIsReached = true;
        }
    } else {
        /* The cursor is at the beginnig or in the middle of the word */
        Word *tmpWord = new Word(*phrase->getWord(cursor.wordIndex));
        beyondEndOfBranch = tmpWord->insertDigit(digit, cursor.relativePosition);

        if (beyondEndOfBranch>0) {
            /* The digit sequence can't lead to any word */
            QMessageBox *reachedEndOfbranch = new QMessageBox;
            QString typedDigits = QString::fromStdString(currentWordDigits);
            typedDigits.insert(cursor.relativePosition, QString::number(digit));
            reachedEndOfbranch->setText("There's no word begining by "+ typedDigits+
                                        "\nThe last "+QString::number(beyondEndOfBranch)+" digits will be removed,"+
                                        "and your new word will be "+typedDigits.mid(0,typedDigits.size()-beyondEndOfBranch));
            reachedEndOfbranch->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            reachedEndOfbranch->setDefaultButton(QMessageBox::Ok);
            int ret = reachedEndOfbranch->exec();
            if (ret==QMessageBox::Ok) {
                phrase->setWord(cursor.wordIndex, tmpWord);
                emit newDigitSequence(phrase->getWord(cursor.wordIndex));
            }
            else    // ret = QMessageBox::Cancel
                endOfbranchIsReached=true;
        }
        else {
            /* The digit sequence exists */
            phrase->setWord(cursor.wordIndex, tmpWord);
            emit newDigitSequence(phrase->getWord(cursor.wordIndex));
        }
    }

    // Dealing with the vue part
    if (!endOfbranchIsReached) {
        cursor.position += 1;
        if (cursor.position==(int)(displayedText.size())+1) {    // End of the sentence
            currentWordDigits.append(std::to_string(digit));
            displayedText.append(QString::number(digit));
            displayCursor();
        } else {
            currentWordDigits.insert(cursor.relativePosition, std::to_string(digit));
            for (int i=0; i<beyondEndOfBranch; i++)
                currentWordDigits.pop_back();
            updateWord(cursor.position-1, cursor.relativePosition, cursor.wordSize,
                       QString::fromStdString(currentWordDigits));
        }
        cursor.wordSize += 1-beyondEndOfBranch;
        cursor.relativePosition += 1;
        if (cursor.relativePosition>cursor.wordSize) {
            cursor.position = cursor.position - cursor.relativePosition + cursor.wordSize;
            cursor.relativePosition=cursor.wordSize;
        }
        cursor.isEditing=true;
        if (cursor.relativePosition==1)
            emit disablePunctuation();
    }
}

void TextDisplayer::rmDigit()
{
    if (cursor.position==0) return; // Impossible to remove a digit at the begining of the text

    if (cursor.wordHasPunctuation&&(cursor.relativePosition==cursor.wordSize+1)) {
        /* There is punctuation and the cursor is right behind it --> just remove it */
        // Model
        phrase->setPunctuation(cursor.wordIndex, "");

        // Vue
        displayedText.remove(cursor.position-1, 1);
        cursor.position --;
        cursor.relativePosition--;
        cursor.wordHasPunctuation=false;
        displayCursor();
        return ;
    }

    /* If we are in the middle (or at the end) of a word -> just remove the digit */
    if (cursor.relativePosition>0)
    {
        // Indicators
        bool endOfbranchIsReached = false;    // Indicate if we must execute the Vue part or not
        int beyondEndOfBranch=0;


        // Model
        if (cursor.relativePosition==cursor.wordSize) {
            phrase->getWord(cursor.wordIndex)->rmLastDigit();           // Faire une gestion des erreurs si il n'y a pas de digits
            emit newDigitSequence(phrase->getWord(cursor.wordIndex));
        }
        else {
            Word *tmpWord = new Word(*phrase->getWord(cursor.wordIndex));
            beyondEndOfBranch = tmpWord->rmDigit(cursor.relativePosition-1);
            if (beyondEndOfBranch>0) {
                QMessageBox *reachedEndOfbranch = new QMessageBox;
                QString typedDigits = QString::fromStdString(currentWordDigits);
                typedDigits.remove(cursor.position-1, 1);
                reachedEndOfbranch->setText("There's no word begining by "+ typedDigits+
                                            "\nThe last "+QString::number(beyondEndOfBranch)+" digits will be removed,"+
                                            "and your new word will be "+typedDigits.mid(0,typedDigits.size()-beyondEndOfBranch));
                reachedEndOfbranch->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                reachedEndOfbranch->setDefaultButton(QMessageBox::Ok);
                int ret = reachedEndOfbranch->exec();
                if (ret==QMessageBox::Ok) {
                    phrase->setWord(cursor.wordIndex, tmpWord);
                    emit newDigitSequence(phrase->getWord(cursor.wordIndex));
                }
                else    // ret = QMessageBox::Cancel
                    endOfbranchIsReached=true;
            }
            else {
                phrase->setWord(cursor.wordIndex, tmpWord);
                emit newDigitSequence(phrase->getWord(cursor.wordIndex));
            }
        }

        // Vue
        if (!endOfbranchIsReached) {
            cursor.position -= 1;
            if (cursor.position+1==(int)(displayedText.size())) {    // End of the sentence
                currentWordDigits.pop_back();
                displayedText.chop(1);
                displayCursor();
            } else {
                currentWordDigits.erase(cursor.relativePosition-1, 1);
                for (int i=0; i<beyondEndOfBranch; i++)
                    currentWordDigits.pop_back();
                updateWord(cursor.position+1, cursor.relativePosition, cursor.wordSize,
                           QString::fromStdString(currentWordDigits));
            }
            cursor.wordSize -= 1+beyondEndOfBranch;
            cursor.relativePosition -= 1;
            if (cursor.relativePosition>cursor.wordSize) {
                cursor.position = cursor.position - cursor.relativePosition + cursor.wordSize;
                cursor.relativePosition=cursor.wordSize;
            }
            cursor.isEditing=true;
            if (cursor.relativePosition==0 && phrase->getPunctuation(cursor.wordIndex-1)=="")
                emit enablePunctuation();
        }
    }
    /* Else, if this is the last word remove the space and start editing the last word again, else just merge the two words */
    else { // cursor.relativePosition==0
        // Indicators
        bool endOfbranchIsReached = false;    // Indicate if we must execute the Vue part or not
        int beyondEndOfBranch=0;
        int sizeOfFirst = phrase->getWord(cursor.wordIndex-1)->getDigitSequence().size();
        int sizeOfSecond = phrase->getWord(cursor.wordIndex)->getDigitSequence().size();
        bool previousWordHasPunctuation = (phrase->getPunctuation(cursor.wordIndex-1)!="");

        // Model
        if  (cursor.position == displayedText.size()) {   // We're at the end of the sentence
            phrase->deleteWord(-1);
            currentWordDigits = phrase->getWord(-1)->getDigitSequence();
            emit newDigitSequence(phrase->getWord(-1));
        } else {          // We're at the middle of the sentence
            // Cache in case of cancel
            Word *copyOfSecond = new Word(*phrase->getWord(cursor.wordIndex));
            std::string copyOfFirstPuctuation = phrase->getPunctuation(cursor.wordIndex-1);

            QString potentialDigitSequence = QString::fromStdString(phrase->getWord(cursor.wordIndex-1)->getDigitSequence()+
                                                                    phrase->getWord(cursor.wordIndex)->getDigitSequence());
            beyondEndOfBranch = phrase->mergeWords(cursor.wordIndex-1, cursor.wordIndex);
            if (beyondEndOfBranch>0) {
                QMessageBox *reachedEndOfbranch = new QMessageBox;
                reachedEndOfbranch->setText("There's no word begining by "+ potentialDigitSequence+
                                            "\nThe last "+QString::number(beyondEndOfBranch)+" digits will be removed,"+
                                            "and your new word will be "+
                                            potentialDigitSequence.mid(0,potentialDigitSequence.size()-beyondEndOfBranch));
                reachedEndOfbranch->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
                reachedEndOfbranch->setDefaultButton(QMessageBox::Ok);
                int ret = reachedEndOfbranch->exec();
                if (ret==QMessageBox::Ok) {
                    emit newDigitSequence(phrase->getWord(cursor.wordIndex-1));
                }
                else {    // ret = QMessageBox::Cancel
                    phrase->unmergeWords(cursor.wordIndex-1, sizeOfFirst, usedDic);
                    phrase->setWord(cursor.wordIndex, copyOfSecond);
                    phrase->setPunctuation(cursor.wordIndex-1, copyOfFirstPuctuation);
                    endOfbranchIsReached=true;
                }
            }
            else {
                emit newDigitSequence(phrase->getWord(cursor.wordIndex-1));
            }
        }

        // Vue
        if (!endOfbranchIsReached) {
            if (previousWordHasPunctuation) {
                phrase->setPunctuation(cursor.wordIndex-1, "");

                displayedText.remove(cursor.position-2, 1);
                cursor.position--;
            }
            cursor.position --;
            if  (cursor.position == displayedText.size()) {   // We're at the end of the sentence
                displayedText.chop(currentWordDigits.size()+1);
                displayedText.append(QString::fromStdString(currentWordDigits));
                displayCursor();
            } else {          // We're at the middle of the sentence
                currentWordDigits = phrase->getWord(cursor.wordIndex-1)->getDigitSequence();
                updateWord(cursor.position+1, sizeOfFirst+1, sizeOfFirst+1+sizeOfSecond, QString::fromStdString(currentWordDigits));
            }
            cursor.wordIndex--;
            cursor.relativePosition=sizeOfFirst;
            cursor.wordSize = currentWordDigits.size();
            cursor.numberOfWords--;
            cursor.isEditing=true;
            // cursor.wordHasPunctuation doesn't change (if the second had puctuation, the word still has it)
            emit disablePunctuation();
        }
    }
}

void TextDisplayer::addWord(Word* SelectedWord)
{
    // Model
    phrase->setWord(cursor.wordIndex, SelectedWord);
    if (cursor.wordIndex==cursor.numberOfWords-1) {
        /* No need to add a word if we are not at the end of the text. */
        Word *newWord = new Word(usedDic);
        phrase->addWord(newWord);
    }

    //Vue
    QString selectedWordString = QString::fromStdString(SelectedWord->getChoosenWord());
    selectedWordString.chop(1); // Removing the "\n"
    int tmpCursor;
    if (cursor.wordIndex==cursor.numberOfWords-1) { // End of the text
        currentWordDigits = "";
        displayedText+=" ";
        tmpCursor = cursor.position;
        cursor.position += cursor.wordSize-cursor.relativePosition+1;
        updateWord(tmpCursor, cursor.relativePosition, cursor.wordSize, selectedWordString);
        cursor.wordSize = 0;
        cursor.wordIndex++;
        cursor.numberOfWords++;
    } else {
        currentWordDigits = phrase->getWord(cursor.wordIndex+1)->getDigitSequence();
        tmpCursor = cursor.position;
        cursor.position += cursor.wordSize-cursor.relativePosition+1;
        updateWord(tmpCursor, cursor.relativePosition, cursor.wordSize, selectedWordString);
        cursor.wordIndex++;
        cursor.wordSize = currentWordDigits.size();
    }
    cursor.relativePosition = 0;
    cursor.isEditing=false;
    if (!cursor.wordHasPunctuation) // i.e. the word that we're adding
        emit enablePunctuation();
    cursor.wordHasPunctuation = (phrase->getPunctuation(cursor.wordIndex)!="");
}

void TextDisplayer::addPunctuation(QString punctuation)
{
    /* Only possible if you are at the very beginning of a word, otherwise deactivate the button. */
    // Model
    phrase->setPunctuation(cursor.wordIndex-1, punctuation.toStdString());

    // Vue
    displayedText.insert(cursor.position-1, punctuation);
    cursor.position ++;
    // cursor.relativePosition stays to 0
    displayCursor();
    emit disablePunctuation();
}

void TextDisplayer::moveLeft()
{
    if (cursor.position >0 ) {
        // Model
        if (displayedText[cursor.position-1]==' ') {
            /* On change de mot si on peut */
            if (cursor.isEditing) {
                QMessageBox *cantLeaveWord = new QMessageBox;
                cantLeaveWord->setText("This word is being edited.\nTry to commit or delete it before going left.");
                int ret = cantLeaveWord->exec();
                if (ret==QMessageBox::Ok)
                    return ;
            }
            cursor.wordIndex-=1;
            cursor.relativePosition = phrase->getWordSize(cursor.wordIndex);
            cursor.wordSize = cursor.relativePosition;
            if (phrase->getPunctuation(cursor.wordIndex)!="") {
                cursor.relativePosition++;
                cursor.wordHasPunctuation = true;
            } else {
                cursor.wordHasPunctuation = false;
            }
            currentWordDigits = phrase->getWord(cursor.wordIndex)->getDigitSequence();
            emit disablePunctuation();
        } else {
            cursor.relativePosition--;
            if (cursor.relativePosition==0 && (cursor.position-1)!=0)
                emit enablePunctuation();
        }

        // Vue
        cursor.position --;
        displayCursor();
//        qDebug()<<"move, position, wordIndex, relativePosition, wordSize, numberOfWords, isEditing, wordHasPunctuation"<<
//                cursor.position<<cursor.wordIndex<<cursor.relativePosition<<cursor.wordSize<<cursor.numberOfWords<<
//                cursor.isEditing<<cursor.wordHasPunctuation;
    }
}

void TextDisplayer::moveRight()
{
    int sizeOfText = displayedText.size();
    if (cursor.position < sizeOfText) {
        // Model
        if (displayedText[cursor.position]==' ') {
            /* On change de mot si on peut */
            if (cursor.isEditing) {
                QMessageBox *cantLeaveWord = new QMessageBox;
                cantLeaveWord->setText("This word is being edited.\nTry to commit or delete it before going right.");
                int ret = cantLeaveWord->exec();
                if (ret==QMessageBox::Ok)
                    return ;
            }
            if (!cursor.wordHasPunctuation) // The word we're leaving
                emit enablePunctuation();
            cursor.wordIndex+=1;
            cursor.relativePosition=0;
            cursor.wordSize = phrase->getWordSize(cursor.wordIndex);
            if (phrase->getPunctuation(cursor.wordIndex)!="")
                cursor.wordHasPunctuation = true;
            else
                cursor.wordHasPunctuation = false;
            currentWordDigits = phrase->getWord(cursor.wordIndex)->getDigitSequence();
        } else {
            cursor.relativePosition++;
            if (cursor.relativePosition==1)
                emit disablePunctuation();
        }

        // Vue
        cursor.position += 1;
        displayCursor();
//        qDebug()<<"move, position, wordIndex, relativePosition, wordSize, numberOfWords, isEditing, wordHasPunctuation"<<
//                cursor.position<<cursor.wordIndex<<cursor.relativePosition<<cursor.wordSize<<cursor.numberOfWords<<
//                cursor.isEditing<<cursor.wordHasPunctuation;
    }
}

