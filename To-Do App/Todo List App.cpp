#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include "todoheader.hpp"

using namespace std;

int main(){
    //Variables and Vectors
    char initial;
    int entryAmount, inputNum, inputNum2, gamestate=1;
    string input;
    vector<string> entries = {};
    
    //Program Loop
    while (gamestate!=0){
        inputOperations(initial, entryAmount, input, entries);
        menuOperations(initial, inputNum, input, entries, gamestate, inputNum2);
    }
}