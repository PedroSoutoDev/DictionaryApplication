#pragma once
#include <string>

using namespace std;

class Word
{
public:
    Word(string, string, string);
    string getWord();
    string getPartOfSpeech();
    string getDefinition();
    string getWordAsString();
    
private:
    string word;
    string partOfSpeech;
    string definition;
};
