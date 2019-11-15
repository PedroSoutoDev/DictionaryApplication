# Dictionary
Spring 2019 class project, creating a searchable dictionary from a text-file based word database.

### Data.CS.SFSU.txt
Stores words, parts of speech, and definitions.  
Sample words:
> book|noun -=>> A set of pages.|verb -=>> To arrange something on a particular date.|verb -=>> To arrange arrange for someone to have a seat on a plane.|noun -=>> A written work published in printed or electronic form.
>
> bookcase|noun -=>> A piece of furniture with shelves.  
> .  
> ..  
> ...  

### Word.cpp
Class used to store words. As words are scanned from the text file, they are converted into *word objects* that are easy to work with. This makes it possible to search, sort, print, remove, and add new entries to the dictionary without having to rescan the entire file every time.

### Dictionary.cpp
Responsible for populating and maintaining a list of words. The user can use search parameters to search the database of words.  

For instance the user may simply enter the search parameters: *"book"*  
This would result in the following result:
> Book \[Noun\] : A set of pages.  
> Book \[Verb\] : To arrange something on a particular date.  
> book \[Verb\] : To arrange arrange for someone to have a seat on a plane.  
> book \[Verb\] : A written work published in printed or electronic form.  

The use may also enter the search parameter: *"book noun"*  
This would result in the following result:
> Book \[Noun\] : A set of pages.

By tokenizing the user's input, the Dictionary class is able to follow a strict searching algorithm, without worrying about correct input formatting.
