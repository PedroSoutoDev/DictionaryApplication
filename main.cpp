#include "Dictionary.hpp"

using namespace std;

bool stringToBool(string);

int main()
{
    //Diction name and path of file to open.
    string filePath = "Data.CS.SFSU.txt";
    string dictionaryName = "----- DICTIONARY 340 JAVA-----";

    //Create an instance of dictionary, using the data from the file above.
    //This implementation allows for the possibility to create many dictionaries with different data sets.
    Dictionary d;
    d.init(dictionaryName, filePath);
    
    //Holds raw user input.
    string userInput;
    
    //Holds parsed user input. Size will always be 3, since querryDictionary() takes 2 arguments.
    vector<string> words;
    while(true)
    {
        cout << ("Search: ");
        
        //Take user input.
        getline (cin, userInput);
        //Turn user input into all lowercase
        transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
        
        //Quit if user enters !Q or !q
        if(userInput == "!q")
            break;
        
        //If the user entered nothing, skip to top and ask them to enter something in again.
        if(userInput == "")
        {
            cout << ("   |") << "\n";
            cout << ("    <Cannot search for an empty string. Please enter a valid search term>") << "\n";
            cout << ("   |") << "\n";
            continue;
        }
        
        //Parse user input into 3 seperate string arguments for the query function.
        vector<string> queryArguments  = d.parseInput(userInput);
        
        //Call the query function using the 3 arguments from user input.
        vector<string> wordsThatMatchedSearch = d.querryDictionary(queryArguments.at(0), queryArguments.at(1), stringToBool(queryArguments.at(2)));
        
        //Print out the words that matched the query.
        cout << ("   |") << "\n";
        for (string matchedWords : wordsThatMatchedSearch)
        {
            cout << ("    " + matchedWords + "\n");
        }
        cout << ("   |") << "\n";
        
    }
    cout << ("\n-----THANK YOU-----") << "\n";
}

//Simple function to turn a string into bool
bool stringToBool(string str)
{
    if(str == "true")
        return true;
    return false;
}
