// 

#include "quadratic_probing.h"
#include "double_hashing.h"
#include "linear_probing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <algorithm>
#include <cctype>
using namespace std;

/*
*   Inserts a dictionary file into a hash table
*/
template <typename HashTableType>
void MakeDictionary(HashTableType &hash_table, const string dictionary_filename)
{
    // Initializes an ifstream object named dict_file
    std::ifstream dictionary_file;
    // Opens @dictionary_filename
    dictionary_file.open(dictionary_filename);
    // Checks if file was able to open or located
    if (dictionary_file.fail())
    {
        // Prints error message
        std::cout << "Unable to open file or file does not exist!" << std::endl;
        // Exits
        exit(1);
    }
    // Words from dictionary file will be stored here
    std::string dictionary_line;
    // Scans the text file line by line
    while (dictionary_file >> dictionary_line)
    {
        // Inserts current line to hash table
        hash_table.Insert(dictionary_line);
    }
    // Close file
    dictionary_file.close();
}

template <typename HashTableType>
void SpellChecker(HashTableType &hash_table, std::string &line)
{
    // newWord will be corrected or printed if already correct
    std::string newWord = line;
    // If the word is not found in dictionary (hash table)
    if (hash_table.Contains(newWord))
    {
        // prints that word is correct
        std::cout << line << " is " << "CORRECT" << std::endl;
    }
    else
    {
        // Prints that word is incorrect
        std::cout << line << " is " << "INCORRECT" << std::endl;
        // Stores word length
        int size = line.length();

        // First case: Add one character in any possible position
        for (int i = 0; i < size + 1; i++)
        {
            // Inserts a letter from a-z at current index
            for (char ch = 97; ch <= 122; ch++)
            {
                // inserts character into word
                newWord.insert(i, 1, ch);
                // if the newWord is now found in the dictionary
                if (hash_table.Contains(newWord))
                {
                    // Print that old word with the correct spelling
                    std::cout << "*** " << line << " -> " << newWord << " *** case A" <<  std::endl;
                }
                // Reset string
                newWord = line;
            }
        }
        
        // Second case: Removes one character from the newWord
        for (int i = 0; i < size; i++)
        {
            // removes character at current pos
            newWord.erase(i, 1);
            // if the newWord is now found in the dictionary (hash_table)
            if (hash_table.Contains(newWord))
            {
                //  Print that old word with the correct spelling
                std::cout << "*** " << line << " -> " << newWord << " *** case B" <<  std::endl;
            }
            // reset string
            newWord = line;
        }
        // Third case: Swap adjacent characters in the newWord
        for (int i = 0; i < size - 1; i++)
        {
            // Swaps adjacent character
            swap(newWord[i], newWord[i + 1]);
            // if the newWord is now found in the dictionary (hash_table)
            if (hash_table.Contains(newWord))
            {
                //  Print that old word with the correct spelling
                std::cout << "*** " << line << " -> " << newWord << " *** case C" <<  std::endl;
            }
            // reset string
            newWord = line;
        }
    }
}

int testSpellingWrapper(int argument_count, char **argument_list)
{
    const string document_filename(argument_list[1]);
    const string dictionary_filename(argument_list[2]);

    // Call functions implementing the assignment requirements.
    HashTable<string> dictionary;
    // Inserts dictionary file into dictionary (hash table)
    MakeDictionary(dictionary, dictionary_filename);


    // Initializes an ifstream object named document_file
    std::ifstream document_file;
    // Opens @document_filename
    document_file.open(document_filename);
    // Checks if file was able to open or located
    if (document_file.fail())
    {
        // Prints error message
        std::cout << "Unable to open file or file does not exist!" << std::endl;
        // exits
        exit(1);
    }
    // Comparator string and Inserts document file into h_line
    std::string db_line; 
    // This string will take one word at a time
    std::string word;
    while(getline(document_file, db_line))
    {
        std::stringstream ss_dbline(db_line);
        while (getline(ss_dbline, word, ' '))
        {
            for (size_t i = 0; i < word.length(); i++)
            {
                word[i] = tolower(word[i]);
                if (!isalpha(word[i]))
                {
                    word.erase(i);
                }
            }
            // Checks spelling of current word
            SpellChecker(dictionary, word);
        }   
    }
    return 0;
}

// Sample main for program spell_check.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testSpellingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
             << endl;
        return 0;
    }

    testSpellingWrapper(argc, argv);

    return 0;
}