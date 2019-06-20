#include "Word.hpp"

Word::Word(string wrd, string speech, string def)
    :word(wrd), partOfSpeech(speech), definition(def)
{
    
}

string Word::getWord()
{
    return word;
}

string Word::getPartOfSpeech()
{
    return partOfSpeech;
}

string Word::getDefinition()
{
    return definition;
}

//EX: for a word named "word" ----          "Word [partOfSpeech1] : Definition"
string Word::getWordAsString()
{
    string temp = (word + " [" + partOfSpeech + "] : " + definition);
    
    //Turn the first character into uppercase, for the correct formating.
    temp[0] = toupper(temp[0]);
    return temp;
}
