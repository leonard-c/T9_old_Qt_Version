//
//  main.cpp
//  T9
//
//  Created by Léonard Chanfreau on 31/12/2021.
//

#include <iostream>

#include "model/dictionary.hpp"
#include "model/word.hpp"
#include "model/sentence.hpp"

/* Ce fichier main.cpp ne sert qu'à tester la partie model de l'application. */

int main(int argc, const char * argv[])
{
    Dictionary french("model/WordList/fr_sans_accents.txt");
    Word mot1(&french, "71477");
    Word mot2(&french, "42");
    mot2.changeChoosenWord(1);
    Word mot3(&french, "55522");
    Sentence phrase;
    
    phrase.addWord(mot1);
    phrase.addWord(mot2);
    phrase.addWord(mot3);
    phrase.insertPunctuation(-1, ".");
    
    int i = 0;
    for (Word wordOnPhrase : *phrase.getWords())
    {
        std::cout<<wordOnPhrase.getChoosenWord()<<phrase.getPunctuation(i);
        i++;
    }
    std::cout<<std::endl;
    
    Word mot4(&french, "7577");
    mot4.changeChoosenWord(3);
    phrase.insertWord(mot4, 1);
    
    i = 0;
    for (Word wordOnPhrase : *phrase.getWords())
    {
        std::cout<<wordOnPhrase.getChoosenWord()<<phrase.getPunctuation(i);
        i++;
    }
    std::cout<<std::endl;
    
    return 0;
}
