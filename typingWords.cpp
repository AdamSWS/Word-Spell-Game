#include <iostream>// For Input and Output
#include <fstream>// For file input and output
#include <vector>// Input file is stored in a vector
#include <cctype>// Allows using the tolower() function
#include <cstdlib>//random number generator
#include <ctime> //remove pseudo random

using namespace std;
int score= 0; // global score variable
int bestscore = 0; //default best score global variable
int wordLength = 5; //default length of word
int queue = 0; //variable to display the welcomeMessage function just once

void welcomeMessage(vector <string> dictionary, vector <string> misspelled) {  //numWords in each txt file
    cout << "There are " << dictionary.size() << " words in the full dictionary." << endl; //calls dictionary vector size
    cout << "There are " << misspelled.size() << " commonly misspelled words." << endl; //calls misspelled vector size
}

int spellWordGenerator(vector <string> wordsUsage, vector <string> wordSearch, int &score, int wordLength = 0) {
    int points = 3; //each point is worth 3
    int elapsedTime = 0; //initializing integer
    int mistakeCount = 0;//initializing integer
    int maxSearch = 5; //maxWord search
    int maxTime = 15; //max seconds in run
    string userWords; //defines variable as string for user input
    vector <string> mustType; //creates a vector, and push back values from userWords
    vector <string> typedWords; //take words from misspelled or dictionary and creates a vector with each set
    vector <string> correctVersion; // takes the second half of misspelledWords
    int i = 0;
    while ( i < maxSearch) { //must use while loop so rand() gets updated
        int index = rand() % wordsUsage.size(); //creates a random index bounded by the size of the allowed word size
        if (wordLength != 0 && wordsUsage.at(index).length() != wordLength) {//makes sure that the word is bounded by the condition of the menu case
            continue;
        }
        correctVersion.push_back(wordSearch.at(index)); //creates a vector of words to check the user's input
        mustType.push_back(wordsUsage.at(index)); //creates a vector of words that the user must input
        cout << wordsUsage.at(index) << " ";
        i++; //runs while look until i = 5
    }
    time_t startTime = time(NULL); //count seconds
    cout << endl << "Type in those words within goal of " << maxTime << " seconds:" << endl;
    for (int x = 0; x < maxSearch; x++) {
        cin >> userWords;
        typedWords.push_back(userWords); //stores a vector of user input
        if (typedWords[x] != correctVersion[x]) {
            mistakeCount++; //records the amount of times user misspells words
        }
    }
    if (mistakeCount != 0) {
        cout << "Misspelled words:" << endl;
        for (int x = 0; x < maxSearch; x++) {
            if (typedWords[x] != correctVersion[x]) {
                cout << typedWords[x] << " should be: " << correctVersion[x] << endl;
            }
        }
    } else {
        cout << "No misspelled words!" << endl;
    }
    elapsedTime = difftime(time(NULL), startTime); //stops the stopwatch
    if (elapsedTime < maxTime) {
        int timeRemaining = (maxTime - elapsedTime); //calculates the time remaining
        int bonusPoints = timeRemaining * 2;
        cout << "Elapsed time: " << elapsedTime << " seconds. " << bonusPoints << " point bonus for finishing " << timeRemaining << " seconds early.";
    }
    if (elapsedTime > maxTime) {
        int timeAfter = (elapsedTime - maxTime); //calculates the time after clock
        int pointReduction = -1 * (timeAfter) * 3; //calls for point reduction
        cout << pointReduction << " points for finishing " << timeAfter << " seconds late.";
    }
    cout << endl;
    if (wordLength != 0) {
        points = wordLength - 4;
    }
    cout << "  " << ((5 - mistakeCount) * points) << " points: " << (5 - mistakeCount) << " spelled correctly x " << points << " points each" << endl;
    if (mistakeCount > 0) {
        int pointReduction2 = points * 2;
        cout << "  " << mistakeCount * pointReduction2 << " point penalty: " << mistakeCount << " spelled incorrectly x" << pointReduction2 << " points each" << endl;
    }
    score = ((5 - mistakeCount) * points) - (mistakeCount * (points * 2)) + ((maxTime - elapsedTime) * 2);
    cout << "  " << "Score: " << score << endl;
    return score;
}

int dictionaryIndex(int lowerBound, int upperBound, vector <string> dictionary) {
    for (int i = lowerBound; i <= upperBound; i++) {// sets bounds for dictionary search
        cout << " " << i << ". " << dictionary.at(i) << endl;
    }
    return 0;
}

int misspelledIndex(int lowerBound, int upperBound, vector <string> misspelled) {
    for (int i = lowerBound; i <= upperBound; i++) {//sets bounds for misspelled search
        cout << " " << i << ". " << misspelled.at(i) << endl;
    }
    return 0;
}

int correctIndex(int lowerBound, int upperBound, vector <string> correct) {
    for (int i = lowerBound; i <= upperBound; i++) {//sets bounds for correct search
        cout << " " << i << ". " << correct.at(i) << endl;
    }
    return 0;
}

int binarySearch(string lookupWord, vector<string> dictionary) {
    int lowestVal = 0; //lowerBound
    int highestVal = dictionary.size() - 1; //upperBound
    int count = 1;
    vector <int> pastPnts; //sets a vector of past midpoints
    for (int i = 0; i < 20 ; i++) {
        int midPnt = (highestVal + lowestVal) / 2; //creates new point
        pastPnts.push_back(midPnt);
        if (midPnt == pastPnts[(i-2)] || midPnt == pastPnts[(i-1)]) {//checks if a midPnt has previously been found
            cout << lookupWord << " was NOT found." << endl; //failed output
            break;
        }
        if (lookupWord > dictionary.at(midPnt)) {
            lowestVal = midPnt + 1;
            cout << " " << count << ". Comparing to: " << dictionary.at(midPnt) << endl; //execution of comparison values
            count++;
        } else if (lookupWord < dictionary.at(midPnt)) {
            highestVal = midPnt - 1;
            cout << " " << count << ". Comparing to: " << dictionary.at(midPnt) << endl;//execution of comparison values
            count++;
        } else if (lookupWord == dictionary.at(midPnt)) {
            cout << " " << count << ". Comparing to: " << dictionary[midPnt] << endl;//execution of comparison values
            cout << dictionary.at(midPnt) << " was found." << endl; //successful output
            break;
        }
    }
    return 0;
}

int menuFunction() {
    int choice;
    cout << endl << "Select a menu option: " << endl;
    cout << " 1. Spell commonly misspelled words (timed)" << endl;
    cout << " 2. Type random words from full dictionary (timed)" << endl;
    cout << " 3. Display some words from one of the lists" << endl;
    cout << " 4. Use binary search to lookup a word in full dictionary" << endl;
    cout << " 5. Set word length to use with full dictionary" << endl;
    cout << " 6. Exit the program" << endl;
    cout << "Your choice --> ";
    cin >> choice;
    return choice; //returns switch choice
}

void dictionaryToVector(vector <string> &dictionary) {
    dictionary.clear();
    string word;
    ifstream fin;
    fin.open("dictionary.txt");
    while (fin >> word) { //saves every other index value to a certain vector
        dictionary.push_back(word);
    }
    fin.close();
}

void misspelledToVector(vector <string> &misspelled, vector <string> &correct) {
    misspelled.clear();
    correct.clear();
    string incorrectWord;
    string correctWord;
    ifstream fin;
    fin.open("misspelledWords.txt");
    while (fin >> incorrectWord >> correctWord) {//saves every other index value to a certain vector
        misspelled.push_back(incorrectWord);
        correct.push_back(correctWord);
    }
    fin.close();
}

int main() {
    vector <string> dictionary; //dictionary vector
    vector <string> misspelled; //misspelled words vector
    vector <string> correct; //correctly spelled words vector
    dictionaryToVector(dictionary);
    misspelledToVector(misspelled, correct);
    while (queue == 0) {//queue while statement for only 1 update
        welcomeMessage(dictionary, misspelled);
        queue++; //outputs once
        srand(1); //seed random
    }
    string lookupWord;
    switch (int choice = menuFunction()) {
        case 1: //misspelled spelling game
            cout << "Using commonly misspelled words" << endl;
            spellWordGenerator(misspelled, correct, score);
            if(score > bestscore) {
                bestscore = score;
            }
            main();
            break;
        case 2: //dictionary spelling game
            cout << "Using full dictionary" << endl;
            spellWordGenerator(dictionary, dictionary, score, wordLength);
            wordLength++;
            if(score > bestscore) {
                bestscore = score;
            }
            main();
            break;
        case 3: //index lookup
            char choice2;
            cout << " Displaying word list entries." << endl;
            cout << " Which words do you want to display?" << endl;
            cout << "   A. Dictionary of all words" << endl;
            cout << "   B. Wrongly spelled common misspelled words" << endl;
            cout << "   C. Correctly spelled common misspelled words" << endl;
            cout << "Your choice --> ";
            cin >> choice2;
            choice2 = tolower(choice2);
            switch (choice2) {//index lookup
                case 'a': //upper and lower bound dict
                    int lowerBound;
                    int upperBound;
                    cout << "Enter the start and end indices between 0 and 263532:" << endl;
                    cin >> lowerBound;
                    cin >> upperBound;
                    dictionaryIndex(lowerBound, upperBound, dictionary);
                    main();
                    break;
                case 'b': //upper and lower bound misspelled
                    int lowerBound2;
                    int upperBound2;
                    cout << "Enter the start and end indices between 0 and 113:" << endl;
                    cin >> lowerBound2;
                    cin >> upperBound2;
                    misspelledIndex(lowerBound2, upperBound2, misspelled);
                    main();
                    break;
                case 'c': //upper and lower bound correct
                    int lowerBound3;
                    int upperBound3;
                    cout << "Enter the start and end indices between 0 and 113:" << endl;
                    cin >> lowerBound3;
                    cin >> upperBound3;
                    correctIndex(lowerBound3, upperBound3, correct);
                    main();
                    break;
            }
            break;
        case 4: //binarySearch
            cout << "Enter the word to lookup: ";
            cin >> lookupWord;
            binarySearch(lookupWord, dictionary);
            main();
            break;
        case 5: //wordLength
            cout << "Enter new wordLength: ";
            cin >> wordLength;
            main();
            break;
        case 6: //exit case
            cout << "Exiting program" << endl;
            cout << "Best score was " << bestscore << endl;
            break;
    }
    return 0;
}