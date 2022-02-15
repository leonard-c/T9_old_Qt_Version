//
//  word.hpp
//  T9
//
//  Created by Léonard Chanfreau on 07/01/2022.
//

#ifndef word_hpp
#define word_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "dictionary.hpp"

class Word          // Héritage ??
{
private:
    std::string mDigitSequence;
//    std::vector<std::string> mWordList;     // Nécessaire ? => si on a le dico
    int mChoosenWord;                       // int ou str ?
    Dictionary* mPointer;
    
public:
    Word();
    Word(Word const& aWord);
    Word(Dictionary* aDictionary);
    Word(Dictionary* aDictionary, std::string aDigitSequence);
    
    void addDigit(const int digit);
    void rmLastDigit();
    int rmDigit(int at);
    int insertDigit(const int digit, const int at); // at : relative position (starting from the left)
    int changeDigit(const int into, const int at);
    
    void changeChoosenWord(int const position);
    
    // Getters
    std::string const getDigitSequence();
    int const getChoosenWordIndex();
    std::string const getChoosenWord();
    std::vector<std::string> const& getWordList();
    //Dictionary* getDictionary();
    bool isNull();
    bool ChildIsNull(int i);
};

#endif /* word_hpp */
