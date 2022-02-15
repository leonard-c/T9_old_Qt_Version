//
//  word.cpp
//  T9
//
//  Created by Léonard Chanfreau on 01/02/2022.
//

#include <stdio.h>

#include "word.hpp"


Word::Word()
{
    mDigitSequence = "";
    mChoosenWord = -1;
    *mPointer = Dictionary();
}

Word::Word(Word const& aWord)
{
    this->mDigitSequence = aWord.mDigitSequence;
    this->mChoosenWord = aWord.mChoosenWord;
    this->mPointer = aWord.mPointer;
}

Word::Word(Dictionary* aDictionary)
{
    mDigitSequence = "";
    mChoosenWord = -1;
    mPointer = aDictionary;
}

Word::Word(Dictionary* aDictionary, std::string aDigitSequence)
{
    mDigitSequence = "";
    mChoosenWord = -1;
    mPointer = aDictionary;
    for (char c : aDigitSequence)
        this->addDigit(atoi(&c));
}


// ---------------------------------------------------------------------------------------

void Word::addDigit(const int digit)
{
    mDigitSequence.append(std::to_string(digit));
    mPointer = mPointer->getChild(digit-1);
    if (!isNull())
        mChoosenWord = (mPointer->getWordList().size()==0)? -1 : 0;
}

void Word::rmLastDigit()
{
    mDigitSequence.pop_back();
    mPointer = mPointer->getParent();
    mChoosenWord = (mPointer->getWordList().size()==0)? -1 : 0;
}

int Word::rmDigit(int at)
{
    try {
        // Ex : 123456 -> rmDigit(3) -> 12356
        // Return the distance to the last existing node

        // Changing the digit sequence
        std::string tmpDigitSequence = mDigitSequence;
        tmpDigitSequence.erase(at, 1);
        // Changing the pointer to the new sequence digit
        int beyondEndOfBranch = 0;
        mPointer = mPointer->goToDigit(tmpDigitSequence, &beyondEndOfBranch);
        // Managing the cases in which the node doesn't exists
        for (int i=0; i<beyondEndOfBranch; i++)
            tmpDigitSequence.pop_back();
        mDigitSequence = tmpDigitSequence;
        // Setting a default choosen word
        mChoosenWord = (mPointer->getWordList().size()==0)?  -1 : 0;
        // Return the number of digits that goes beyond the out of the branch to notify if the operation couldn't be completely done
        return beyondEndOfBranch;

    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return 0;
    }
}

int Word::insertDigit(const int digit, const int at)
{
    try {
        // Ex: 123456 -> rmDigit(9, 3) -> 1239456
        // Same principle as rmDigit
        std::string tmpDigitSequence = mDigitSequence;
        tmpDigitSequence.insert(at, std::to_string(digit));
        int *beyondEndOfBranch = new int(0);
        mPointer = mPointer->goToDigit(tmpDigitSequence, beyondEndOfBranch);
        for (int i=0; i<*beyondEndOfBranch; i++)
            tmpDigitSequence.pop_back();
        mDigitSequence = tmpDigitSequence;
        mChoosenWord = (mPointer->getWordList().size()==0)?  -1 : 0;

        return *beyondEndOfBranch;

    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return 0;
    }
}

int Word::changeDigit(const int into, const int at)
{
    try {
        // Ex: 123456 -> changeDigit(3,9) -> 123956
        // Again : same principle
        std::string tmpDigitSequence = mDigitSequence;
        tmpDigitSequence.replace(at, 1, std::to_string(into));
        int beyondEndOfBranch = 0;
        mPointer = mPointer->goToDigit(mDigitSequence, &beyondEndOfBranch);
        for (int i=0; i<beyondEndOfBranch; i++)
            tmpDigitSequence.pop_back();
        mDigitSequence = tmpDigitSequence;
        mChoosenWord = (mPointer->getWordList().size()==0)?  -1 : 0;

        return beyondEndOfBranch;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return 0;
    }
}

// ---------------------------------------------------------------------------------------

void Word::changeChoosenWord(const int position)
{
    try {
        if (position>=(int)mPointer->getWordList().size())
            throw std::out_of_range("Choosen word's position can't be greater than the size of the word list.");
        mChoosenWord = position;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}

// ---------------------------------------------------------------------------------------

std::string const Word::getDigitSequence()
{
    return mDigitSequence;
}

int const Word::getChoosenWordIndex()
{
    return mChoosenWord;
}

std::string const Word::getChoosenWord()
{
    try {
        if (mPointer->getWordList().size()==0)
            throw "Error in getChoosenWord: WordList is empty.";
        return mPointer->getWordList()[mChoosenWord];
    }  catch (std::string error) {
        std::cerr<<error<<std::endl;
        return NULL;
    }
}


std::vector<std::string> const& Word::getWordList()
{
    return mPointer->getWordList();
}


bool Word::isNull()
{
    return (mPointer==NULL);
}

bool Word::ChildIsNull(int i)
{
    try {
        return (mPointer->getChild(i-1)==NULL);
    }  catch (std::string error) {
        std::cerr<<error<<std::endl;
        return true;
    }
}
