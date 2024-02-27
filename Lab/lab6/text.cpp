/*
 * File: lab6_skeleton.cpp
 *
 * Lab 6: Recursion - Alien Word Parsing
 */

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_LEN = 256;

bool correct_word(char word[MAX_LEN], int index, int length)
{

    /* ADD YOUR CODE HERE */
    /* THIS MUST BE A RECURSIVE FUNCTION */

    // Task 1: Base case with only a single character
    if (length == index && word[index] >= 'a' && word[index] <= 'z')
    {
        return true;
    }

    // Task 2: Recursive case with suffix characters '@', or '#'
    if ((word[length] == '@' || word[length] == '#') && correct_word(word, index, length - 1))
    {
        return true;
    }

    // Task 3: Recursive case with concatenation characters '|' at suffix position.
    if (word[length] == '|')
    {
        for (int i = 0; i < length; i++)
        {
            if (correct_word(word, index, i) && correct_word(word, i + 1, length - 1))
            {
                return true;
            }
        }
    }

    // Task 4: Recursive case with concatenation characters '#' at prefix position.
    if (word[index] == '#')
    {
        for (int i = 1; i <= length; i++)
        {
            if (correct_word(word, index + 1, i) && correct_word(word, i + 1, length))
            {
                return true;
            }
        }
    }

    // All remaining cases are wrong
    return false;
}

int main()
{
    char word[MAX_LEN];
    char c;

    do
    {
        cout << "Enter a word: ";
        cin >> word;
        if (correct_word(word, 0, strlen(word) - 1))
            cout << "The word is CORRECT!\n";
        else
            cout << "The word is INCORRECT!\n";
        cout << "Do you want to enter a new word ('Y'/'y' for Yes, 'N'/'n' for No)? ";
        cin >> c;
    } while (c == 'Y' || c == 'y');

    return 0;
}