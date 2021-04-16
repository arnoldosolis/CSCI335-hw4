// Arnoldo Solis

#include "quadratic_probing.h"
/*
*   Included Linear Probing and Double Hashing
*/
#include "linear_probing.h"
#include "double_hashing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename)
{
    // cout << "TestFunctionForHashTables..." << endl;
    // cout << "Words filename: " << words_filename << endl;
    // cout << "Query filename: " << query_filename << endl;
    // hash_table.MakeEmpty();
    //..Insert your own code
    cout << "number_of_elements: " << hash_table.getElementCount() << endl;
    cout << "size_of_table: " << hash_table.getCurrentSize() << "\n";
    cout << "load_factor: " << hash_table.theLoadFactor() << endl;
    cout << "average_collisions: " << hash_table.averageCollisions() << endl;
    cout << "total_collisions: " << hash_table.collisionCount() << endl;
    std::cout << std::endl; // < new line>
}

// namespace PROTECTED {

int testHashingWrapper(int argument_count, char **argument_list)
{
    const string words_filename(argument_list[1]);
    const string query_filename(argument_list[2]);
    const string param_flag(argument_list[3]);
    // Default R value set to 23
    int R = 23;

    if (argument_count == 5)
    {
        const string rvalue(argument_list[4]);
        R = stoi(rvalue);
    }

    if (param_flag == "linear")
    {
        // cout << "Linear:" << endl; // Testing
        // Creates ifstream object
        std::ifstream words;
        // Opens file
        words.open(words_filename);
        // Checks if file is able to open or if it exists
        if (words.fail())
        {
            // Prints error message
            std::cout << "Unable to open file or file does not exist!" << std::endl;
            // Exits
            exit(1);
        }

        // Takes in strings from "words_filename"
        std::string h_line;
        // Creates HashTable
        HashTableLinear<string> linear_probing_table;
        // Reads the file line by line
        while (getline(words, h_line) && !h_line.empty())
        {
            // Inserts word into hash table
            linear_probing_table.Insert(h_line);
        }
        // Prints out required output
        TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);

        // Creates ifstream object
        std::ifstream query;
        // Opens file
        query.open(query_filename);
        // Checks if file is able to open or if it existss
        if (query.fail())
        {
            // Prints error message
            std::cout << "Unable to open file or file does not exist!" << std::endl;
            // Exits
            exit(1);
        }

        // Resets collisions to count probes
        linear_probing_table.resetCollisionCount();
        // Gets all the words from the query file
        while (getline(query, h_line))
        {
            // If the word from the query file is in the hash table that means that it is found
            if (linear_probing_table.Contains(h_line))
            {
                // Prints that word was found and how many times it took to search for the word
                std::cout << h_line << " Found " << linear_probing_table.collisionCount() + 1 << std::endl;
                // Resets collision to count probes for anothe word
                linear_probing_table.resetCollisionCount();
            }
            else // If the word from the query file is not in the hash table that means that it was not found
            {
                // Prints that word was not found and how many times it too search
                cout << h_line << " Not_Found " << linear_probing_table.collisionCount() + 1 << std::endl;
                // Resets collision to count probes for anothe word
                linear_probing_table.resetCollisionCount();
            }
        }
    }
    else if (param_flag == "quadratic")
    {
        // cout << "Quadratic:" << endl; // Testing
        // Creates ifstream object
        std::ifstream words;
        // Opens file
        words.open(words_filename);
        // Checks if file is able to open or if it exists
        if (words.fail())
        {
            // Prints error message
            std::cout << "Unable to open file or file does not exist!" << std::endl;
            // Exits
            exit(1);
        }

        // Takes in strings from "words_filename"
        std::string h_line;
        // Creates HashTable
        HashTable<string> quadratic_probing_table;
        // Reads the file line by line
        while (getline(words, h_line) && !h_line.empty())
        {
            // Inserts word into hash table
            quadratic_probing_table.Insert(h_line);
        }
        // Prints out required output
        TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);

        // Creates ifstream object
        std::ifstream query;
        //Opens file
        query.open(query_filename);
        // Checks if file is able to open or if it existss
        if (query.fail())
        {
            // Prints error message
            std::cout << "Unable to open file or file does not exist!" << std::endl;
            // Exits
            exit(1);
        }

        // Resets collisions to count probes
        quadratic_probing_table.resetCollisionCount();

        // Gets all the words from the query file
        while (getline(query, h_line))
        {
            // If the word from the query file is in the hash table that means that it is found
            if (quadratic_probing_table.Contains(h_line))
            {
                // Prints that word was found and how many times it took to search for the word
                std::cout << h_line << " Found " << quadratic_probing_table.collisionCount() + 1 << std::endl;
                // Resets collision to count probes for anothe word
                quadratic_probing_table.resetCollisionCount();
            }
            else
            {
                // Prints that word was not found and how many times it too search
                cout << h_line << " Not_Found " << quadratic_probing_table.collisionCount() + 1 << std::endl;
                // Resets collision to count probes for anothe word
                quadratic_probing_table.resetCollisionCount();
            }
        }
    }
    else if (param_flag == "double")
    {
        // cout << "Double:" << endl; // Testing
        HashTableDouble<string> double_probing_table;
        double_probing_table.setR(R);
        cout << "r_value: " << R << endl;
        // Creates ifstream object
        std::ifstream words;
        // Opens file
        words.open(words_filename);
        // Checks if file is able to open or if it exists
        if (words.fail())
        {
            // Prints error message
            std::cout << "Unable to open file or file does not exist!" << std::endl;
            // Exits
            exit(1);
        }

        // Takes in strings from "words_filename"
        std::string h_line;
        // Reads the file line by line
        while (getline(words, h_line) && !h_line.empty())
        {
            // Inserts word into hash table
            double_probing_table.Insert(h_line);
        }

        // Prints out required output
        TestFunctionForHashTable(double_probing_table, words_filename, query_filename);

        // Creates ifstream object
        std::ifstream query;
        //Opens file
        query.open(query_filename);
        // Checks if file is able to open or if it existss
        if (query.fail())
        {
            // Prints error message
            std::cout << "Unable to open file or file does not exist!" << std::endl;
            // Exits
            exit(1);
        }

        // Resets collisions to count probes
        double_probing_table.resetCollisionCount();

        // Gets all the words from the query file
        while (getline(query, h_line))
        {
            if (double_probing_table.Contains(h_line))
            {
                // Prints that word was found and how many times it took to search for the word
                std::cout << h_line << " Found " << double_probing_table.collisionCount() + 1 << std::endl;
                // Resets collision to count probes for anothe word
                double_probing_table.resetCollisionCount();
            }
            else
            {
                // Prints that word was not found and how many times it too search
                cout << h_line << " Not_Found " << double_probing_table.collisionCount() + 1 << std::endl;
                // Resets collision to count probes for anothe word
                double_probing_table.resetCollisionCount();
            }
        }
    }
    else
    {
        cout << "Unknown hash type " << param_flag
             << " (User should provide linear, quadratic, or double)" << endl;
    }
    return 0;
}

// Sample main for program create_and_test_hash.
// WE WILL NOT USE YOUR MAIN IN TESTING. DO NOT CODE FUNCTIONALITY INTO THE
// MAIN. WE WILL DIRECTLY CALL testHashingWrapper. ALL FUNCTIONALITY SHOULD BE
// THERE. This main is only here for your own testing purposes.
int main(int argc, char **argv)
{
    if (argc != 4 and argc != 5)
    {
        cout << "Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag>" << endl;
        cout << "or Usage: " << argv[0]
             << " <wordsfilename> <queryfilename> <flag> <rvalue>" << endl;
        return 0;
    }

    testHashingWrapper(argc, argv);
    return 0;
}

//};  // namespace PROTECTED
