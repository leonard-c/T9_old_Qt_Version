//
//  dictionary.cpp
//  T9
//
//  Created by Léonard Chanfreau on 01/02/2022.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>
#include <string>

#include <QFile>

#include "dictionary.hpp"


Dictionary::Dictionary()
{
    mParent = NULL;
    for (int i=0; i<10; i++)
        mChildren[i] = NULL;
}

Dictionary::Dictionary(Dictionary const& model)
{
    mDigitSequence = model.mDigitSequence;
    mWordList = model.mWordList;
    mParent = model.mParent;
    for (int i=0; i<10; i++)
        mChildren[i] = model.mChildren[i];
}

Dictionary::Dictionary(std::string const digitSequence, Dictionary* parent)
{
    mDigitSequence = digitSequence;
    mParent = parent;
    for (int i=0; i<10; i++)
        mChildren[i] = NULL;
}

Dictionary::Dictionary(std::string const fileName)
{
    mParent = NULL;
    for (int i=0; i<10; i++)
        mChildren[i] = NULL;
    /* Create a dictionary from a list of word */
    char tmp[256];
    getcwd(tmp, 256);
    std::cout << "Current working directory: " << tmp << std::endl;
    
    // Create a text string, which is used to output the text file
    // std::string word;
    // Read from the text file
//    std::ifstream file(fileName);
    QFile file(QString::fromStdString(fileName));
    
    if (!file.exists()) {
        std::cerr<<"Error: File doesn't exist"<<std::endl;
        exit(EXIT_FAILURE);
    }
    // !file.is_open()
    if ( !file.open((QIODevice::ReadOnly | QIODevice::Text)) )
    {
        std::cerr<<"Error: File couldn't be oppened"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    // std::getline(file, word)
    while (!file.atEnd())
    {
        QString word = file.readLine();
        this->addChild(word.toStdString());
    }
    file.close();
}

void Dictionary::addChild(std::string const word)
{
    // Convert word into a digit sequence
    std::string digitSequence;
    for ( char c : word )                                       // Voire comment on peut gérer les accents
    {
        if (c=='a' || c=='b' || c=='c') digitSequence.push_back('1');
        else if (c=='d' || c=='e' || c=='f') digitSequence.push_back('2');
        else if (c=='g' || c=='h' || c=='i') digitSequence.push_back('3');
        else if (c=='j' || c=='k' || c=='l') digitSequence.push_back('4');
        else if (c=='m' || c=='n' || c=='o') digitSequence.push_back('5');
        else if (c=='p' || c=='q' || c=='r') digitSequence.push_back('6');
        else if (c=='s' || c=='t' || c=='u') digitSequence.push_back('7');
        else if (c=='v' || c=='w' || c=='x') digitSequence.push_back('8');
        else if (c=='y' || c=='z' || c=='-') digitSequence.push_back('9');
    }

    // Going back to the origin
    Dictionary *navigator = this;
    for ( char c : mDigitSequence ) navigator = navigator->getParent();
    if (navigator == NULL)
    {
        std::cerr<<"Error when adding a child: unable to go back to the origin of the dictionary"<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Navigating or creating all the branches to the leave
    for ( int i=0; i<(int)digitSequence.size(); i++ )
    {
        char c = digitSequence[i];
        int key = atoi(&c)-1;
        Dictionary *child = navigator->getChild(key);
        if (child==NULL)
        {
            std::string newDigitSequence = digitSequence.substr(0,i+1);
            Dictionary *newChild = new Dictionary(newDigitSequence, navigator);
            navigator->setChild(*newChild, key);
            child = navigator->getChild(key);
        }
        navigator = child;
    }
    
    // Verifying that the xord is not already on the list
    std::vector<std::string> wordList = navigator->getWordList();
    bool notOnTheList = true;
    for ( int i=0; i<(int)wordList.size(); i++ )
        if (wordList[i]==word)
            notOnTheList = false;
    
    // Adding the word on the list
    if (notOnTheList) { navigator->addWordToList(word); }
}

Dictionary* Dictionary::goToDigit(const std::string digitSequence, int* beyondEndOfBranch)
{
    // Counting the number of shared digit at the beginning of the word
    int countSharedDigit=0;
    int minSequenceLength = (mDigitSequence.length()<digitSequence.length())? (int)mDigitSequence.length() : (int)digitSequence.length();
    int i=0;
    while (i<minSequenceLength && mDigitSequence[i]==digitSequence[i]) {
        countSharedDigit+=1;
        i++;
    }
    
    // Navigating up to the last shared digit
    Dictionary *navigator = this;
    for (int j=0; j<(int)mDigitSequence.length()-countSharedDigit; j++)
        navigator = navigator->getParent();
    
    //Navigating down to the last wanted digit
    *beyondEndOfBranch = 0;
    for (int j=countSharedDigit; j<(int)digitSequence.length(); j++) {
        char digit = digitSequence[j];
        Dictionary *tmpChild = navigator->getChild(atoi(&digit)-1);
        if (tmpChild==NULL) {
            *beyondEndOfBranch+=1;
        }
        else {
            navigator = tmpChild;
        }
    }
    return navigator;       // Remark: could probably be upgraded a bit (in certain conditions : shorter to start from the root)
}

//----------------------------------------------------------------------------

std::vector<std::string> const& Dictionary::getWordList()
{
    return mWordList;
}
std::string Dictionary::getDigitSequence() const
{
    return mDigitSequence;
}

//----------------------------------------------------------------------------

Dictionary* Dictionary::getChild(const int typedNumber)
{
    try {
        return mChildren[typedNumber];
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        return NULL;
    }
}
Dictionary* Dictionary::getParent()
{
    return mParent;
}

//----------------------------------------------------------------------------

void Dictionary::setChild(Dictionary& child, int at)
{
    try {
        mChildren[at] = &child;
    }  catch (const std::out_of_range& err) {
        std::cerr << "Out of Range error: " << err.what() << '\n';
    }
}

//-----------------------------------------------------------------------------

void Dictionary::addWordToList(std::string const word)
{
    mWordList.push_back(word);
}
