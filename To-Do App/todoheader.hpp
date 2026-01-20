#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;

//Menu Text and Selection Instructions
void menuText(){
    printf("----------------------------------");
    printf("\n|--------------Menu--------------|");
    printf("\n|Press 1 to Add an item----------|");
    printf("\n|Press 2 to Read the list--------|");
    printf("\n|Press 3 to Remove an item-------|");
    printf("\n|Press 4 to Sort Alphabetically--|");
    printf("\n|Press 5 to Reset the list-------|");
    printf("\n|Press 6 to Exit the program-----|");
    printf("\n----------------------------------\n");
    cout << "Enter a number:";
}

//Bubble sort function
void vectorSort(vector<string> &entries, int inputA){
    string tempvar;
    cout << "Press 1 to sort A-Z. Press 2 to sort Z-A" << endl;
    cin >> inputA;
    
    //Sorts A-Z
    if (inputA == 1){ 
        for (int i = 0; i < entries.size(); i++){
            for (int j = i+1; j < entries.size(); j++){
                if (entries[j] < entries[i]){
                    tempvar = entries[i];
                    entries[i] = entries[j];
                    entries[j] = tempvar;
                }
            }
        }
    }

    //Sorts Z-A
    else if (inputA == 2){ 
        for (int i = 0; i < entries.size(); i++){
            for (int j = i+1; j < entries.size(); j++){
                if (entries[j] > entries[i]){
                    tempvar = entries[i];
                    entries[i] = entries[j];
                    entries[j] = tempvar;
                }
            }
        }
    }

    //Failsafe
    else{
        vectorSort(entries, inputA);
    }
    
}

//App Initialization and Inputs
void inputOperations(char initialInputA, int entryAmountA, string inputA, vector<string> &entries){
    cout << "Welcome to the TODO Today App. We help you stay on track with your life." << endl;
    cout << "Would you like to import a txt file? (Enter 'Y' to import/Enter 'N' to continue as usual)" << endl;
    cin >> initialInputA;

    //If list in imported
    if (initialInputA == 'Y' || initialInputA =='y'){
        string myText;
        ifstream MyReadFile("input.txt"); //File name can be changed here
        while (getline (MyReadFile, myText)){
            entries.push_back(myText);
        }
        MyReadFile.close();
    }

    //If list is not imported
    else if (initialInputA == 'N' || initialInputA =='n'){
        cout << "How many entries do you want to add today? : ";
        cin >> entryAmountA;
        cin.ignore();
        cout << "Enter your entries." << endl;
        for (int i = 0; i < entryAmountA; i++){
            cout << "Entry #" << i+1 << ": ";
            getline(cin, inputA);
            entries.push_back(inputA);
        }
    }

    //Failsafe
    else{
        inputOperations( initialInputA, entryAmountA, inputA, entries);
    }
}

//Menu Functions
void menuOperations(char initialInputA, int inputNumA, string inputA, vector<string> &entries, int &gamestateA, int inputNumB){
    time_t currentTime;
    gamestateA = 1;
    ofstream MyFile("output.txt"); 
    
    while (gamestateA != 0){
        menuText();
        cin >> inputNumA;
        cin.ignore();
        
        //Add
        if (inputNumA == 1){
            cout << "\nEnter new item:";
            getline(cin, inputA);
            entries.push_back(inputA);
        }

        //Read
        else if (inputNumA == 2){
            time(&currentTime);
            ofstream MyFile("output.txt"); 
            MyFile << ctime(&currentTime);
            MyFile << "List:" << endl;
            for (int j = 0; j < entries.size(); j++){
                MyFile << j+1 << "." << entries[j] << endl;
            }
            MyFile.close();
            cout << "The output file has been updated." << endl;
        }

        //Remove
        else if (inputNumA == 3){
            cout << "\nEnter item # you want removed:" << endl;
            cin >> inputNumA;
            entries.erase(entries.begin() + (inputNumA-1));
            time(&currentTime);
            ofstream MyFile("output.txt");
            MyFile << ctime(&currentTime);
            MyFile << "List:" << endl;
            for (int l = 0; l < entries.size(); l++){
                MyFile << l+1 << "." << entries[l] << endl;
            }
            MyFile.close();
            cout << "The output file has been updated." << endl;
        }

        //Sort alphabetically
        else if (inputNumA == 4){
            vectorSort(entries, inputNumB);
            time(&currentTime);
            ofstream MyFile("output.txt");
            MyFile << ctime(&currentTime);
            MyFile << "List:" << endl;
            for (int k = 0; k < entries.size(); k++){
                MyFile << k+1 << "." << entries[k] << endl;
            }
            MyFile.close();
            cout << "The output file has been updated." << endl;
        }

        //Reset list 
        else if (inputNumA == 5){
            entries.clear();
            inputOperations(initialInputA, inputNumA, inputA, entries);
        }

        //Exit the program
        else if (inputNumA == 6){
            gamestateA = 0;
        }

        //Failsafe
        else{
            menuOperations(initialInputA, inputNumA, inputA, entries, gamestateA, inputNumB);
        }
    }
}