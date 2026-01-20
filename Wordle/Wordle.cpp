#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib> 

using namespace std;

string wordInput(string word, string inputA){
    cin >> inputA;
    if (inputA.size() < word.size() or inputA.size() > word.size()){
        cout << "Enter a " << word.size() << " letter word" << endl;
        return wordInput(word, inputA);
    }
    return inputA;
}

void checkGuess(string guess, string answer){
    string result = "     ";
    for (int i = 0; i < answer.length(); i++)
    {
        if (guess[i] == answer[i])
        {
            result[i] = '^';
            answer[i] = '.';
            guess[i] = '+';
        }
    }
    for (int i = 0; i < answer.length(); i++)
    {
        for (int j = 0; j < answer.length(); j++)
        {
            if (guess[i] == answer[j])
            {
                result[i] = '?';
                answer[j] = '.';
                break;
            }
        }
    }
    cout << result << endl;
}

void checkResults( vector<string> &guessesOne, vector<string> &guessesTwo, vector<string> &guessesThree, int &resultInt){
    resultInt = min(guessesOne.size(), min(guessesTwo.size(), guessesThree.size()));
    if (resultInt == guessesOne.size()){
        cout << "You did best on your first try." << endl;
    }
    else if (resultInt == guessesTwo.size())
    {
        cout << "You did best on your second try." << endl;
    }
    else if (resultInt == guessesThree.size())
    {
        cout << "You did best on your third try." << endl;
    }
}

void removeWord(vector<string>&vec, string word){
    for (int i = 0; i < vec.size(); i++)
    {
        if (word == vec[i])
        {
            vec.erase(vec.begin()+i);
            return;
        }
    }
}

int main(){
    int randomIndex, resultInt, i;
    string selectedWord, enteredWord, line;

    vector<string> guessesOne = {};
    vector<string> guessesTwo = {};
    vector<string> guessesThree = {};
    vector<string> words = {};

    ifstream file("words.txt");

    cout << "Welcome to Wordle!" << endl;

    for (int k = 0; k < 3; k++)
    {
        srand ( time(NULL) );
        randomIndex = 1+ (rand() % 59);

        while (getline(file, line)) words.push_back(line);

        selectedWord = words[randomIndex];
        removeWord(words, selectedWord);

        cout << "\nTry to guess the 4, 5, or 6 Letter Word. \n'^' means you have the right letter in the right spot \n'?' means you have the letter but not the positon. \nA blank result just means all the letters are incorrect." << endl;

        i = 0;
        while (i < 6){
            if (selectedWord == enteredWord){
                cout << "Congrats! You got it in less than 6 tries." << endl;
                break;
            }
            else{
                enteredWord = wordInput(selectedWord, enteredWord);
                if (k == 0){
                    guessesOne.push_back(enteredWord);
                }
                else if (k == 1){
                    guessesTwo.push_back(enteredWord);
                }
                else if (k == 2){
                    guessesThree.push_back(enteredWord);
                }
                //cout << enteredWord << endl;
                checkGuess(enteredWord, selectedWord);
                i += 1;
            }
        }
        
        if (selectedWord == enteredWord){
            cout << "You got it!" << endl;
        }
        else{
            cout << "The word was " << selectedWord << endl;
        }

        if (k != 2){
            cout << "\nTime for next round. Get ready!" << endl;
        }
    }
    checkResults(guessesOne, guessesTwo, guessesThree, resultInt);
}