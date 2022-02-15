//
//  sentence.hpp
//  T9
//
//  Created by Léonard Chanfreau on 30/01/2022.
//

#ifndef sentence_hpp
#define sentence_hpp

#include <stdio.h>
#include <iostream>
#include "word.hpp"

class Sentence {
private:
    std::vector<Word*> mWords;
    std::vector<std::string> mPunctuation;
    
public:
    Sentence(){};
    
    Word* getWord(int at);
    void setWord(int const at, Word *word);
    std::vector<Word*> const* getWords();
    int getNumberOfWords();
    int getWordSize(int const at);
    
    void addWord(Word* word); // At the back of the sentence
    void insertWord(Word *word, int at);
    void deleteWord(int at);
    
    int mergeWords(int const first, int const second);
    int unmergeWords(int first, int sizeOfFirst, Dictionary* dic);
    
    void addPunctuation(std::string punctuation);
    void insertPunctuation(int at, std::string punctuation);
    std::string getPunctuation(int at);
    void setPunctuation(int at, std::string punctuation);

    /*struct CursorPosition{
        int wordIndex;
        int relativePosition;
        int wordSize;
    };
    CursorPosition position(int at);*/ /* Useful for the cursor */
//    int getWordIndex(int at);
};

#endif /* sentence_hpp */
