//
//  sentence.cpp
//  T9
//
//  Created by Léonard Chanfreau on 30/01/2022.
//

#include "sentence.hpp"

/*//////////////////////////////////////////////////////////////////////////////////////*/

Word* Sentence::getWord(int at)
{
    if (at==-1)
        return mWords.back();
    try {
        return mWords[at];
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return NULL;
    }
}

void Sentence::setWord(int const at, Word *word)
{
    if (at==-1)
        mWords.back() = word;
    try {
        mWords[at] = word;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}

std::vector<Word*> const* Sentence::getWords()
{
    return &mWords;
}

int Sentence::getNumberOfWords()
{
    return (int)mWords.size();
}

int Sentence::getWordSize(const int at)
{
    try {
        return mWords[at]->getDigitSequence().size();
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return 0;
    }
}

// ---------------------------------------------------------------------------------------

void Sentence::addWord(Word* word)
{
    mWords.push_back(word);
    mPunctuation.push_back("");
}

void Sentence::insertWord(Word *word, int at)
{
    try {
        mWords.insert(mWords.begin()+at, word);
        mPunctuation.insert(mPunctuation.begin()+at, "");
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}

void Sentence::deleteWord(int at)
{
    if (at==-1)
    {
        mWords.pop_back();
        mPunctuation.pop_back();
    } else {
        try {
            mWords.erase(mWords.begin()+at);
            mPunctuation.erase(mPunctuation.begin()+at);
        }  catch (const std::out_of_range& err) {
            std::cerr << "Out of Range error: " << err.what() << '\n';
        }
    }
}


// ---------------------------------------------------------------------------------------

int Sentence::mergeWords(const int first, const int second)
{
    try {
        int beyondEndOfBranch=0;
        int i=0;
        for (char digit : mWords[second]->getDigitSequence())
        {
            if (!mWords[first]->ChildIsNull(atoi(&digit)))
                mWords[first]->addDigit(atoi(&digit));
            else {
                beyondEndOfBranch=mWords[second]->getDigitSequence().size()-i;
                break;
            }
            i++;
        }
        mWords.erase(mWords.begin()+second);
        mPunctuation.erase(mPunctuation.begin()+first);
        return beyondEndOfBranch;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return 0;
    }
}

int Sentence::unmergeWords(int first, int sizeOfFirst, Dictionary* dic)
{
    try {
        int beyondEndOfBranch=0;

        std::string fulldigitSequence = mWords[first]->getDigitSequence();
        Word *second = new Word(dic);
        for (int i=sizeOfFirst; i<(int)fulldigitSequence.size(); i++)
        {
            char digit = fulldigitSequence[i];
            if (!second->ChildIsNull(atoi(&digit)))
                second->addDigit(atoi(&digit));
            else {
                beyondEndOfBranch=fulldigitSequence.size()-sizeOfFirst-i;
                break;
            }
        }
        insertWord(second, first+1);
        for (int i=sizeOfFirst; i<(int)fulldigitSequence.size(); i++)
        {
            mWords[first]->rmLastDigit();
        }
        return beyondEndOfBranch;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return 0;
    }
}


// ---------------------------------------------------------------------------------------

void Sentence::addPunctuation(std::string punctuation)
{
    mPunctuation.push_back(punctuation);
}

void Sentence::insertPunctuation(int at, std::string punctuation)
{
    try {
        if (at==-1) at = (int)mPunctuation.size()-1;
        mPunctuation.insert(mPunctuation.begin()+at, punctuation);
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}

std::string Sentence::getPunctuation(int at)
{
    if (at==-1)
        return mPunctuation.back();
    try {
        return mPunctuation[at];
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return NULL;
    }
}

void Sentence::setPunctuation(int at, std::string punctuation)
{
    try {
        mPunctuation[at]=punctuation;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}
