#include <iostream>   // For input and output
#include <fstream>    // For working with files
#include <string>     // For using strings

using namespace std;

// Check if the word has only letters
bool check(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (!isalpha(word[i]))
        {
            return false;    // Return false if a character is not a letter
        }
    }
    return true;             // Return true if all characters are letters
}

// Sort words by their length and save them into different files
void sorting()
{
    ifstream Sample("words.txt");                // Open the file to read words
    ofstream Easy("easy.txt", ios::app);          // Open file for easy words
    ofstream Medium("medium.txt", ios::app);      // Open file for medium words
    ofstream Hard("hard.txt", ios::app);          // Open file for hard words

    string word;   // Store the word

    if (Sample.is_open())   // Check if the file opened correctly
    {
        while (getline(Sample, word))   // Read words one by one
        {
            if (check(word) == false)   // If the word is invalid, skip it
            {
                cout << "Invalid word: " << word << endl;
                continue;
            }

            // Save the word to the correct file based on its length
            if (word.length() >= 10)
            {
                Hard << word << endl;
            }
            else if (word.length() > 5 && word.length() < 10)
            {
                Medium << word << endl;
            }
            else if (word.length() <= 5 && word.length() >= 3)
            {
                Easy << word << endl;
            }
        }
    }
    else
    {
        cout << "File not found" << endl;   // Show error if file not opened
    }
}

int main()
{
    sorting();    // Start sorting the words
    return 0;     // End the program
}
