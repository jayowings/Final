#include "Codebreaker.h"
using namespace std;

bool Code::Pguess(){
    //Make Computer Code
    for(int i = 0; i < 5; i++){
        computerCode[i].value = (rand() % 8) + 1;
    }

//****// for loop, ...; turnsToGo--)
    for ( ; turnsToGo > 0; turnsToGo--){
        cout << "Take a guess! (1,2,3,4,5)\n";
    //User input choices, save in guessCode array
        getline(cin, guessCode[0].value, ','); //TODO change value to type char || create function that changes char to int, change struct code to class
        getline(cin, guessCode[1].value, ',');
        getline(cin, guessCode[2].value, ',');
        getline(cin, guessCode[3].value, ',');
        getline(cin, guessCode[4].value, ',');

    //compare using checkCorrect
        if(checkCorrect()){
            return true;
        }
    //if win, break, return true, else loop back to //****//
    }
    //if turnsToGo == 0 and code has not been found, return false
    return false;
};

bool Code::Cguess(){//**Computer guess array could be formatted easier if each code position was a struct with members int value and enum{UNKNOWN, FALSE, ALMOST, TRUE} or a class with a built in random function**//
    //initial guess created
//****// for loop, ...; turnsToGo--)
    //Computer prints guess

    //user input numCorrect and numAlmost

    //logic to manipulate computer guess, break for computer win (return false), loop back to //****//

    //if turnsToGo == 0 and code has not been found, return true
}

bool Code::checkCorrect(){ //Player guess, Computer Code
    //resets Correct and Almost
    Correct = Almost = 0;

//****// first for loop (i) check for Correct values
    for(int i = 0; i < 5; i++){
        if(computerCode[i].value == guessCode[i].value){
            guessCode[i].correctGuess = computerCode[i].correctGuess = TRUE; //set flag
            Correct++;
        }else{
            guessCode[i].correctGuess = computerCode[i].correctGuess = UNKNOWN; //Resets flags automatically
        }
    }
    //compare [i] on guess and computer code, if ==, Correct++

//****// second for loop (i)
    for(int i = 0; i < 5; i++){
        if(guessCode[i].correctGuess != TRUE){ //if value has not already been marked as correct
            for(int j = 0; j < 5; j++){
                if(computerCode[j].correctGuess < ALMOST/*if value has not already been marked as correct(3) or Almost(2)*/ && computerCode[j].value == guessCode[i].value){
                    computerCode[j].correctGuess = guessCode[i].correctGuess = ALMOST;
                    Almost++;
                    break; //exits computercode loop, next iteration of guesscode loop
                }
            }
        }
    }
    //if [i] on guess is in computer code (use temp or Class/struct to check if value has already been counted in Correct) Almost++;

    //display Correct and Almost, return true if win else return false
    cout << "\nCorrect guesses: " << Correct << "\tRight color, wrong position: " << Almost << endl;
    if(Correct == 5){
        return true;
    }else{
        return false;
    }
}

Code::Code(bool PlayerCdoe, int& gamesWon){
    //if Player is codebreaker, run Pguess, if true, gamesWon++

    //if Player is codemaker, run Cguess, if false, gamesWon++
}