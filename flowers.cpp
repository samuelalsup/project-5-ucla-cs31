//
//  flowers.cpp
//  Project_5_CStrings
//
//  Created by Sam Alsup on 11/11/19.
//  Copyright © 2019 Sam Alsup. All rights reserved.
// Name : Samuel Alsup   UID: 805371633

#include "utilities.h"
#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum);

const char WORDFILENAME[] = "/Users/samalsup/Desktop/words.txt";
const int MAXWORDS = 10000;
const int MAXWORDLENGTH = 6;
const int MINWORDLENGTH = 4;
const int MAXCHARS = 100;

int main()
{
    int numRounds = 0;
    char arrayOfWords[MAXWORDS][MAXWORDLENGTH + 1]; // creates the main array of words to be filled from the file
    int numWords = getWords(arrayOfWords, MAXWORDS, WORDFILENAME); // keeps track of amount of words in the file; also puts them into arrayOfWords
    if ((numWords < 1) || (numWords > MAXWORDS))
    {
        cout << "No words were loaded, so I can't play the game." << endl;
        return 1;
    }
    
    cout << "How many rounds do you want to play? ";
    cin >> numRounds;
    cin.ignore(10000, '\n'); // throws out the \n character
    int sumOfTries = 0; // used for the average
    int minimumOfTries = 100000; // used for the minimum
    int maximumOfTries = 0; // used for the maximum
    int roundsSoFar = 1; // used for the average
    cout.setf(ios::fixed);
    cout.precision(2); // sets the average to have two decimal places

    if (numRounds <= 0) // error checking
    {
        cout << "The number of rounds must be positive." << endl;
        return 9;
    }
    //cout << "\n";
    for (int i = 0; i < numRounds; i++)
    {
        cout << "\n";
        int randomNum = randInt(0, numWords - 1);
        cout << "Round " << roundsSoFar << endl;
        cout << "The mystery word is " << strlen(arrayOfWords[randomNum]) << " letters long." << endl;
        int tries = playOneRound(arrayOfWords, numWords, randomNum); // gets number of tries it took the user
        if (tries == 1)
            cout << "You got it in 1 try." << endl;
        else
            cout << "You got it in " << tries << " tries." << endl;
        
        sumOfTries += tries;
        if (tries > maximumOfTries)
            maximumOfTries = tries;
        if (tries < minimumOfTries)
            minimumOfTries = tries;
        double average = double(sumOfTries) / roundsSoFar;
        cout << "Average: " << average << ", minimum: " << minimumOfTries << ", maximum: " << maximumOfTries << endl;
        
        roundsSoFar++;
    }
}

int playOneRound(const char words[][MAXWORDLEN + 1], int nWords, int wordnum)
{
    int tries = 1;
    if ((nWords <= 0) || (wordnum < 0) || (wordnum >= nWords)) // error checking
        return -1;
    char theword[MAXWORDLENGTH +1];
    char trialword[MAXCHARS];
    
    for (;;)
    {
        strcpy(theword, words[wordnum]); // copies the word into a separate character array
        int flowers = 0;
        int bees = 0;
        cout << "Trial word: ";
        cin.getline(trialword, MAXCHARS);
        
        bool hasUpperCase = false;
        for (int i = 0; trialword[i] != '\0'; i++) // checks to see if there are any characters that aren't lowercase
        {
            if ( ! (islower(trialword[i])))
                hasUpperCase = true;
        }
        
        if (strlen(trialword) < MINWORDLENGTH || strlen(trialword) > MAXWORDLENGTH || hasUpperCase) // error checking
        {
            cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            continue;
        }
        
        bool notAWord = true;
        for (int i = 0; i < nWords; i++)
        {
            if (strcmp(words[i], trialword) == 0)
                notAWord = false;
        }
        if (notAWord)
        {
            cout << "I don't know that word." << endl;
            continue;
        }
            
        if (strcmp(trialword, theword) == 0) // checks to see if method is finished
            return tries;
        
        for (int i = 0; (trialword[i] != '\0' && theword[i] != '\0'); i++) // checks for flowers
        {
            if (trialword[i] == theword[i]) // if a flower is found, changes the letters to a number so they won't make a bee later on
            {
                flowers++;
                trialword[i] = '0';
                theword[i] = '1';
            }
        }
        
        for (int i = 0; trialword[i] != '\0'; i++) // checks for bees
        {
            for (int j = 0; theword[j] != '\0'; j++)
            {
                if (trialword[i] == theword[j]) // if a bee is found, changes the letters to a number so that it won't be counted as another bee later on
                {
                    bees++;
                    trialword[i] = '0';
                    theword[j] = '1';
                }
            }
        }
        cout << "Flowers: " << flowers << ", Bees: " << bees << endl;
        tries++;
    }
}
