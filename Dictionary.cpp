#include "Dictionary.hpp"

void Dictionary::init(string dictionaryName, string filePath)
{
    //Open the text file.
    ifstream file(filePath);
    if(file.is_open())
    {
        cout << "! Opening data file... ./" << filePath << "\n";
        cout << ("! Loading data...\n");
        
        
    }
    else
    {
        cout << ("Error. File not found.\n");
        exit(1);
    }
    
    
    //Iterate through the file and create word objects for the dictionaryWordList.
    string entireLine;
    while(!file.eof())
    {
        getline(file, entireLine);
        processWordsFromLine(entireLine);
    }
    
    cout << ("! Loading completed...\n");
    cout << "! Closing data file... ./" << filePath << "\n\n";
    cout << dictionaryName << "\n\n";
    file.close();
}

void Dictionary::processWordsFromLine(string fileLine)
{
    //Turn string into stringstream.
    stringstream entireLine(fileLine);
    string wordName;
    
    getline(entireLine, wordName, '|');
    
    int numOfWords = Dictionary::getNumberOfWordsInLine(fileLine);
    vector<string> partsOfSpeech;
    vector<string> definitions;
    
    string tempPartOfSpeech;
    string tempDefinition;
    string tempThrowaway;
    for (int i = 0; i < numOfWords; i++)
    {
        //Store whats between '|' and ' ' , which will be the part of speech.
        getline(entireLine, tempPartOfSpeech, ' ');
        
        //Move the pointer to the next space(' '), which will skip the "-=>>".
        getline(entireLine, tempThrowaway, ' ');
        
        //Store whats between ' ' and '|' , which will be definition of the word.
        getline(entireLine, tempDefinition, '|');
        
        dictionaryWordList.push_back(*new Word(wordName, tempPartOfSpeech, tempDefinition));
    }
}

int Dictionary::getNumberOfWordsInLine(string str)
{
    int count = 0;
    
    for (int i = 0; i < str.size(); i++)
        if (str[i] == '|')
            count++;
    
    return count;
}

 vector<string> Dictionary::querryDictionary(string word, string speechType, bool distinct)
{
    //Final array to be returned. This array should be properly formated to be.
    //EX: for a word named "word" ["Word [PartOfSpeech1] : Definition1", "Word [PartOfSpeech2] : Definition2"]
    vector<string> finalArray;
    
    //Keeps tracks of all the words that matched, as you add them.
    vector<Word> wordsAlreadyAdded;
    
    //If the speechType is "Error" then that means the user input words in the wrong order.
    if (speechType == "ErrorSecondArgument")
    {
        finalArray.push_back("<Second argument must be part of speech or \'distinct\'>");
        return finalArray;
    }
    
    //If the speechType is "Error" then that means the user input too many arguments.
    else if (speechType == "ErrorTooManyArgument")
    {
        finalArray.push_back("<Invalid entry. Search again>");
        return finalArray;
    }
    
    //If they give us no word, then no words will match.
    else if (word == "null")
    {
        finalArray.push_back("<Not found in dictionary>");
        return finalArray;
    }
    
    //Go through all the words in the dictionary and see which words match our criteria.
    for (Word currentWord : dictionaryWordList)
    {
        //Check if the word queried matches the word we are looking at in the dictionary.
        //If the given word does not match, then move onto the next word in the dictionary.
        if (!(word == currentWord.getWord()))
            continue;
        
        //* AT THIS POINT WE KNOW THAT THE WORD GIVEN MATCHES THE WORDOBJECT BEING SEARCHED *//
        
        //If the word does not depend on the part of speech and it doesnt have to be distinct, we simply add the word to the list.
        if (speechType == "null" && !distinct)
        {
            finalArray.push_back(currentWord.getWordAsString());
            wordsAlreadyAdded.push_back(currentWord);
            continue;
        }
        
        //If the word has to be a certain part of speech, but not distinct, we simply check the part of speech before adding it.
        else if (!(speechType == "null") && !distinct)
        {
            if(currentWord.getPartOfSpeech() == (speechType))
            {
                finalArray.push_back(currentWord.getWordAsString());
                wordsAlreadyAdded.push_back(currentWord);
            }
            continue;
        }
        
        //If the word does not depend on the type of speech, but has to be unique, we have to make sure that we dont add a word with repeating definitions.
        else if (speechType == "null" && distinct)
        {
            //If the current word we are checking has not already been added, then we can add it to the words that match.
            if(!(Dictionary::wordHasAleradyBeenAdded(wordsAlreadyAdded, currentWord)))
            {
                finalArray.push_back(currentWord.getWordAsString());
                wordsAlreadyAdded.push_back(currentWord);
                continue;
            }
        }
        
        //If the word DOES depend on the type of speech AND has to be unique, we first check to make sure that the type of speech matches. THEN we have to make sure that we dont add a word with repeating definitions.
        else if (!(speechType == "null") && distinct)
        {
            if (currentWord.getPartOfSpeech() == speechType)
            {
                if(!(Dictionary::wordHasAleradyBeenAdded(wordsAlreadyAdded, currentWord)))
                {
                    finalArray.push_back(currentWord.getWordAsString());
                    wordsAlreadyAdded.push_back(currentWord);
                    continue;
                }
            }
        }
        
        else
        {
            //Something went wrong, all parameters should have been checked.
            cout << "Something went wrong, all parameters should have been checked. Check your query logic.";
            break;
        }
    }
    
    //If nothing was added to the array, no words were found.
    if(finalArray.empty())
    {
        finalArray.push_back("<Not found in dictionary>");
    }
    
    return finalArray;
}

//Takes in a user inputed string and parses it, passsing back the 3 appropriate arguments for the diction query.
//string[0] represents the word.
//string[1] represents the part of speech.
//string[2] represents the boolean for distinct or not.
 vector<string> Dictionary::parseInput(string input)
{
    //Vector to be returned. Only 3 parameters, which will be used in querryDictionary().
    vector<string> finalParse;
    
    //Break user input into strings based on spaces.
    istringstream iss(input);
    vector<string> parts((istream_iterator<WordDelimitedBy<' '>>(iss)),
                                     istream_iterator<WordDelimitedBy<' '>>());
    
    //If user enters only one argument, then that argument is the word to be searched.
    //It is assumed that any part of speech is allowed, and distinct is false.
    if (parts.size() == 1)
    {
        finalParse.push_back(parts.at(0));
        finalParse.push_back("null");
        finalParse.push_back("false");
        return finalParse;
    }
    
    //If the user enter 2 arguments, then the first argument is the word.
    //The second must be check to see if it distinct, or a part of speech.
    else if (parts.size() == 2)
    {
        //If the second word is distinct, then any part of speech is fine. Distinct will be true.
        if (parts.at(1) == ("distinct"))
        {
            finalParse.push_back(parts.at(0));
            finalParse.push_back("null");
            finalParse.push_back("true");
            return finalParse;
        }
        
        //If the second word if a part of speech, then distinct is false. And that part of speech is required.
        else if (isPartOfSpeech(parts.at(1)))
        {
            finalParse.push_back(parts.at(0));
            finalParse.push_back(parts.at(1));
            finalParse.push_back("false");
            return finalParse;
        }
        
        //If the second word is not distinct or a part of speech, it will be an error.
        else
        {
            finalParse.push_back("null");
            finalParse.push_back("ErrorSecondArgument");
            finalParse.push_back("false");
            return finalParse;
        }
        
    }
    
    //If the user enters 3 argument, the first argument will be the word.
    //We must check if the second word is either distinct or a part of speech.
    else if(parts.size() == 3)
    {
        //If the second word is a part of speech and the third word is distinct then that if good.
        if (isPartOfSpeech(parts.at(1)) && parts.at(2) == "distinct")
        {
            finalParse.push_back(parts.at(0));
            finalParse.push_back(parts.at(1));
            finalParse.push_back("true");
            return finalParse;
        }
        
        //Otherwise, there is an error in format and we return the format error using part of speech.
        else
        {
            finalParse.push_back("null");
            finalParse.push_back("ErrorSecondArgument");
            finalParse.push_back("false");
            return finalParse;
        }
    }
    
    //If the user enters more than 3 arguments return a null.
    //This means (parts.size() > 3) or it was empty.
    else
    {
        finalParse.push_back("null");
        finalParse.push_back("ErrorTooManyArgument");
        finalParse.push_back("false");
        return finalParse;
    }
}

//Take a string in and returns a boolean reprenting wheter or not that string is a part of speech.
 bool Dictionary::isPartOfSpeech(string input)
{
    if (input == "noun" || input == "adjective" || input == "adverb"
        || input == "conjection" || input == "interjection" || input == "preposition"
        || input == "pronoun" || input == "verb")
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

//Check if a single word is contained within the Word Vector passed.
bool Dictionary::wordHasAleradyBeenAdded(vector<Word> vectorToCheck, Word wordToCheck)
{
    for (Word currentWord : vectorToCheck)
    {
        if(currentWord.getWordAsString() == wordToCheck.getWordAsString())
        {
            return true;
        }
    }
    return false;
}
