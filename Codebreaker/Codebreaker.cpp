#include "Codebreaker.h"
using namespace std;

bool code::guessChecker(){
    for(int i = 0; i < 8; i++){
        if(this->previousGuesses[i] == TRUE){ //if there is a value that has been proven true
            this->value = i + 1; //set value to true value
            return true;
        }
    }
    if(this->previousGuesses[this->value - 1] == FALSE || this->previousGuesses[this->value - 1] == ALMOST){ //if this guess has already been proven wrong
        return false;
    }
    return true; //if unknown and no known true value exists, guess is allowed
}

void code::guessResult(INCODE result){ //if more information received, change data
    if(this->previousGuesses[this->value - 1] < result){ //Almost and false are treated (almost) the same, no (pressing) need for differentiation
        this->previousGuesses[this->value - 1] = result;
    }
}

bool Codebreaker::Pguess(){
    //Make Computer Code
    for(int i = 0; i < 5; i++){
        computerCode[i].value = (rand() % 8) + 1;
    }

//****// for loop, ...; turnsToGo--)
    for ( ; turnsToGo > 0; turnsToGo--){
        cout << "Take a guess! (1,2,3,4,5)\n";
    //User input choices, save in guessCode array
        getline(cin, guessCode[0].inputArray, ',');
        getline(cin, guessCode[1].inputArray, ',');
        getline(cin, guessCode[2].inputArray, ',');
        getline(cin, guessCode[3].inputArray, ',');
        getline(cin, guessCode[4].inputArray, ',');
        for(int i = 0; i < 5; i++){
            if(guessCode[i].inputArray == "1"){
                guessCode[i].value = 1;
            }else if(guessCode[i].inputArray == "2"){
                guessCode[i].value = 2;
            }else if(guessCode[i].inputArray == "3"){
                guessCode[i].value = 3;
            }else if(guessCode[i].inputArray == "4"){
                guessCode[i].value = 4;
            }else if(guessCode[i].inputArray == "5"){
                guessCode[i].value = 5;
            }else if(guessCode[i].inputArray == "6"){
                guessCode[i].value = 6;
            }else if(guessCode[i].inputArray == "7"){
                guessCode[i].value = 7;
            }else{
                guessCode[i].value = 8; //default value
            }
        }
    //compare using checkCorrect
        if(checkCorrect()){
            return true;
        }
    //if win, break, return true, else loop back to //****//
    }
    //if turnsToGo == 0 and code has not been found, return false
    return false;
};

bool Codebreaker::Cguess(){//**Computer guess array could be formatted easier if each code position was a struct with members int value and enum{UNKNOWN, FALSE, ALMOST, TRUE} or a class with a built in random function**//
    //initial guess created
    for(int i = 0; i < 5; i++){
        computerCode[i].value = guessCode[i].value = (rand() % 8) + 1;
    }
    int prevCorrect = 0, prevAlmost = 0;

    for ( ; turnsToGo > 0; turnsToGo--){
    //Computer prints guess
        for(int i = 0; i < 5; i++){
            cout << guessCode[i].value;
            if(i != 4){
                cout << ',';
            }
        }

        cout << "How many are in the correct position? ";
    //user input numCorrect and numAlmost, break for computer win (return false)
        cin >> Correct;
        if(Correct == 5){
            return false;
        }
        cout << "How many are in the wrong position? ";
        cin >> Almost;
        if(Correct + Almost > 5 || (Correct == 4 && Almost == 1)){ //invalid input restarts the game
            cout << "Invalid input. Please review game rules and try again.";
            int i = 0;
            CodebreakerSetUp(i);
            if(i == 0) return false;
            else return true;
        }
        int ComparePrev[12];
        ComparePrev[10] = 0;
        ComparePrev[11] = 0;
        for(int i = 0; i < 5; i++){ //Check values in the same position
            ComparePrev[i] = guessCode[i].value;
            ComparePrev[i + 5] = computerCode[i].value;
            if(ComparePrev[i] == ComparePrev[i + 5]){
                ComparePrev[10]++; //Same position
                ComparePrev[11]++; //Differect position same number
                ComparePrev[i] = -1;
                ComparePrev[i + 5] = 0;
            }
        }
        for(int i=0; i<5; i++){ //Check values in different positions
            for (int j = 5; j<10; j++){
                if(ComparePrev[i] == ComparePrev[j]){
                    ComparePrev[i] = -1;
                    ComparePrev[j] = 0;
                    ComparePrev[11]++;
                }
            }
        }
        if(prevAlmost + prevCorrect != Almost + Correct){
            if(prevAlmost + prevCorrect > Almost + Correct && ComparePrev[11] == (5 - (prevAlmost + prevCorrect) + Almost + Correct)){
                
            }
        }
        for(int i = 0; i < 5; i++){ //Save previous code
            computerCode[i].value = guessCode[i].value;
        }

        //Changeing values
        for(int i = 0; i < 5; i++){ //When element(s) is known to be false
            if(!guessCode[i].guessChecker()){
                do{
                    guessCode[i].value = (rand() % 8) + 1;
                }while(!guessCode[i].guessChecker())
            }
        }
        //if no elements are known to be FALSE
        if(guessCode[0].value == computerCode[0].value && guessCode[1].value == computerCode[1].value && guessCode[2].value == computerCode[2].value && guessCode[3].value == computerCode[3].value && guessCode[4].value == computerCode[4].value){
            //Swap Almost values
        }

    }
    //if turnsToGo == 0 and code has not been found, return true
}

bool Codebreaker::checkCorrect(){ //Player guess, Computer Code
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

Codebreaker::Codebreaker(bool PlayerCdoe, int& gamesWon){
    if(PlayerCdoe){
        if(Pguess()){
            gamesWon++;
        }
    //if Player is codebreaker, run Pguess, if true, gamesWon++
    }else{
        if(!Cguess()){
            gamesWon++;
        }
    }
    //if Player is codemaker, run Cguess, if false, gamesWon++
}

void CodebreakerSetUp(int& gamesWon){
    //Welcome message
    cout << "Welcome to Codebreaker!\n";

    //Outline rules

    int TF;
    while(true){
        cout << "(1)Codemaker or (2)Codebreaker? ";
    //input T/F for Codemaker/Codebreaker
        cin >> TF;
        if(TF == 1){
            Codebreaker Game1(false, gamesWon);
            break;
        }else if(TF == 2){
            Codebreaker Game1(true, gamesWon);
            break;
        }
        cout << "Invalid response!\n";
    }
    //create Codebreaker object
}