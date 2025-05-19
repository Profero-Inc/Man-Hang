#include <iostream>
#include <fstream>
#include <string>

using namespace std;
bool check(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (!isalpha(word[i]))
        {
            return false;
        }
    }
    return true;
}
void sorting(string w)
{
    ifstream Sample(w);
    ofstream Easy("EASY.txt", ios::app);
    ofstream Medium("NORMAL.txt", ios::app);
    ofstream Hard("HARD.txt", ios::app);  
    string word;
    if (Sample.is_open())
    {
        while (getline(Sample, word))
        {
            if (check(word) == false)
            {
                cout << "Invalid word: " << word << endl;
                continue; // Skip invalid words
            }
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
        cout << "File not found" << endl;
    }
}
int main()
{
    sorting("words.txt");
    sorting("Hard(Additional).txt");
    return 0;
}