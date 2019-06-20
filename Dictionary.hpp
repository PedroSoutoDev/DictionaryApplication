#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <fstream>
#include <locale>

#include "Word.hpp"

using namespace std;

class Dictionary
{
public:
    
    void init(string, string);
    
    vector<string> querryDictionary(string, string, bool);
    
    vector<string> parseInput(string);
    
    //Static helper functions.
    static bool wordHasAleradyBeenAdded(vector<Word>, Word);
    static int getNumberOfWordsInLine(string);
    
private:
    
    void processWordsFromLine(string);
    
    bool isPartOfSpeech(string);
    
    bool stringIsContainedIn(string[], vector<string>);
    
    vector<Word> dictionaryWordList;
};

//Template for a delimiter for using split function.
template<char delimiter>
class WordDelimitedBy : public string
{};
