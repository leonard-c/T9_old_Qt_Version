//
//  dictionary.hpp
//  T9
//
//  Created by Léonard Chanfreau on 01/01/2022.
//

#ifndef dictionary_hpp
#define dictionary_hpp

#include <stdio.h>

#include <vector>
#include <string>


class Dictionary
{
    private :
        std::string mDigitSequence;
        std::vector<std::string> mWordList;
        Dictionary* mChildren[10];                 // Size 10
        Dictionary* mParent;
    
    public :
        Dictionary();
        Dictionary(std::string const fileName);
        Dictionary(Dictionary const& model);
        Dictionary(std::string const digitSequence, Dictionary *parent);
    
        void addChild(std::string const word);
        Dictionary* goToDigit(std::string const digitSequence, int* beyondEndOfBranch);
    
        std::vector<std::string> const& getWordList();
        std::string getDigitSequence() const;

        Dictionary* getChild(const int typedNumber);
        Dictionary* getParent();
        
        void setChild(Dictionary& child, int at);
    
        void addWordToList(std::string const word);
};



#endif /* dictionary_hpp */
