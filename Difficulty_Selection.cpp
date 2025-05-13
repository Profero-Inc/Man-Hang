#include <iostream>
#include <fstream>
#include <string>

using namespace std;
bool check(string word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (!(isalpha(word[i])))
        {
            return false;
        }
    }
    return true;
}
void sorting()
{
    ifstream Sample("words.txt");
    ofstream Easy("easy.txt", ios::app);
    ofstream Medium("medium.txt", ios::app);
    ofstream Hard("hard.txt", ios::app);
    string word;
    if (Sample.is_open())
    {
        while (getline(Sample, word))
        {
            if (check(word) == false)
            {
                cout << "Invalid word: " << word << endl;
                continue;
            }
            else if (word.length() >= 10)
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
    sorting();
    return 0;
}