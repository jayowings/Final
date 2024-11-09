#include "Codebreaker.h"
using namespace std;

bool code::guessChecker(){
    for(int i = 0; i < 8; i++){
        if(this->previousGuesses[i] == TRUE){ //if there is a value that has been proven true
            this->value = i + 1; //set value to true value
            return true;
        }
    }
    if(this->previousGuesses[this->value - 1] == FALSE){ //if this guess has already been proven wrong
        return false;
    }
    return true; //if unknown and no known true value exists, guess is allowed
}

void code::guessResult(INCODE result){ //if more information received, change data
    if(this->previousGuesses[this->value - 1] < result){ //Will not override TRUE
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
        ComparePrev[10] = 5;
        //ComparePrev[11] = 5;
        for(int i = 0; i < 5; i++){ //Check values in the same position
            ComparePrev[i] = guessCode[i].value;
            ComparePrev[i + 5] = computerCode[i].value;
            if(ComparePrev[i] == ComparePrev[i + 5]){
                ComparePrev[10]--; //num of values that changed
                //ComparePrev[11]--; //Changed position same number
                ComparePrev[i] = -1;
                ComparePrev[i + 5] = 0;
            }
        }
/*        for(int i=0; i<5; i++){ //Check values in different positions
            for (int j = 5; j<10; j++){
                if(ComparePrev[i] == ComparePrev[j]){
                    ComparePrev[i] = -1;
                    ComparePrev[j] = 0;
                    ComparePrev[11]--;
                }
            }
        }*/
        
        //Setting Flags
        //only works if ComparePrev == 1
        if(prevCorrect > Correct && ComparePrev[10] == 1){//previous correct found by replacement
            for(int i = 5; i < 10; i++){
                if(ComparePrev[i] > 0){
                    guessCode[i - 5].previousGuesses[ComparePrev[i] - 1] = TRUE; //flage previous value as true
                    guessCode[i-5].value = ComparePrev[i]; //change value to Correct value for functions below
                    guessCode[i-5].correctGuess = TRUE;
                    Correct++;
                }
            }
        }else if(Correct > prevCorrect && ComparePrev[10] == 1){//correct found by luck
            for(int i = 0; i<5; i++){
                if(ComparePrev[i] > 0){
                    guessCode[i].previousGuesses[ComparePrev[i] - 1] = TRUE;
                    guessCode[i].correctGuess = TRUE;
                }
            }
        }
        if(ComparePrev[10] == 1 && prevCorrect == Correct){//if no change for correct (both values are false)
            if(Almost == 0){//if no values are in the code
                for(int i = 0; i<5; i++){
                    if(ComparePrev[i] > 0 && guessCode[i].correctGuess != TRUE){ //changed value is false
                        for(int j = 0; j<5; j++){
                            if (guessCode[j].previousGuesses[guessCode[i].value] != TRUE){ //don't change repeated values proven false
                                guessCode[j].previousGuesses[guessCode[i].value] = FALSE;
                            }
                        }
                    }
                }
            }
            if(prevAlmost == 0){//if no values were in the prevCode
                for(int i = 0; i<5; i++){
                    if(ComparePrev[i+5]>0 && guessCode[i].correctGuess != TRUE){ //changed value was false
                        for(int j = 0; j<5; j++){
                            if (guessCode[j].previousGuesses[ComparePrev[i+5]] != TRUE){ //don't change repeated values proven false
                                guessCode[j].previousGuesses[ComparePrev[i+5]] = FALSE;
                            }
                        }
                    }
                }
            }
            for(int i = 0; i<5; i++){
                if(ComparePrev[i] > 0){ //if value was changed and Almost and prevAlmost != 0
                    guessCode[i].guessResult(FALSE);
                    guessCode[i].previousGuesses[ComparePrev[i+5] - 1] = FALSE;
                }
            }
        }

        int unkownCorrect = Correct; //when a value is known to be correct, tests can be skipped
        for(int i = 0; i <5; i++){
            computerCode[i].value = guessCode[i].value; //previous Code is now obsolete, store for next iteration
            if(guessCode[i].correctGuess == TRUE){
                unkownCorrect--;
            }
        }
        //Changeing values
        //learn correct values
        if(unkownCorrect > 0){
            int newValIndex = 0;
            int prevVal;
            int lowerTrues = 0;
            //moving right to left, add a new value to test previous value
            for(int i = 0; i < 5; i++){
                if(guessCode[i].correctGuess == TRUE){
                    lowerTrues++;
                }
                if(ComparePrev[i] > 0){//Find last value that was changed
                    if(i == lowerTrues){//if the first nonTRUE value was changed ("Almost" shuffle)
                        newValIndex = 4;
                        if(guessCode[4].correctGuess == TRUE){//check all last values until UNKNOWN is found
                            newValIndex = 3;
                            if(guessCode[3].correctGuess == TRUE){
                                newValIndex = 2;
                                if(guessCode[2].correctGuess == TRUE){//
                                    newValIndex = 1;
                                }
                            }
                        }
                    }else if(i == unkownCorrect + lowerTrues){//if the value to be changed is the last possible value to be changed, all remaining values of lower indexes are true
                        while(unkownCorrect > 0){
                            if(guessCode[i - 1].correctGuess != TRUE){//skip true values
                                guessCode[i - 1].correctGuess = guessCode[i-1].previousGuesses[guessCode[i-1].value] = TRUE;
                                unkownCorrect--; //correct has been learned, allows next functions to trigger
                            }else{
                                i--;
                            }
                        }
                        break;
                    }else{//previous shift was "Correct Shift" and was not last possible value change
                        newValIndex = i - 1;
                        while(true){
                            if(guessCode[newValIndex].correctGuess == TRUE){//skip true values
                                newValIndex--;
                            }else{
                                break;
                            }
                        }
                    }
                    prevVal = guessCode[newValIndex].value;
                    do{//new value cannot be old value or value previously proven as false
                        guessCode[newValIndex].value = (rand() % 8) + 1;
                    }while(!guessCode[newValIndex].guessChecker() || guessCode[newValIndex].value == prevVal);
                }
            }
        }

        //"Almost shuffle"
        if(Almost > 0 && unkownCorrect == 0){
            int numShuffled = 0;
            for(int i = 0; i < 5; i++){ //count numShuffled
                if(guessCode[i].correctGuess == TRUE){
                    continue; //skip TRUE values
                }else{
                    guessCode[i].previousGuesses[guessCode[i].value] = FALSE; //all guesses that are not TRUE are FALSE
                    numShuffled++;
                }
            }
            int prevValues[numShuffled];
            for(int i = 0, j = 0; i < 5 && j < numShuffled; i++){//set values in prevValues
                if(guessCode[i].correctGuess == TRUE){
                    continue; //skip TRUE values
                }else{
                    prevValues[j] = guessCode[i].value;
                    if(j = 0){ //add new value in prevValues[0]
                        do{//new value cannot be value previously proven as false
                            guessCode[i].value = (rand() % 8) + 1;
                        }while(!guessCode[i].guessChecker());
                        int temp = prevValues[j];
                        prevValues[j] = guessCode[i].value;
                        guessCode[i].value = temp;
                    }
                    j++;
                }
            }
            int j = 1, count = 0; //rotate in iterations, only iterate so many times
            do{
                for(int i = 0; i < 5; i++){ //shuffle
                    if(guessCode[i].correctGuess == TRUE){
                        continue;
                    }
                    else{
                        if(j < numShuffled){
                            j-=numShuffled;
                        }
                        guessCode[i].value = prevValues[j];
                    }
                }
                j++; count++; //in case of next iteration
                for(int i = 0; i < 5; i ++){ //check need for next iteration
                    if(!guessCode[i].guessChecker()){ //if new value from shuffle is FALSE, shuffle will run again
                        break;
                    }
                    if(i == 4){//if check has passed for all values
                        count = 0; //end iterations
                    }
                }
                if(count == 5){//reset values for randAll
                    for(int i = 0; i<5; i++){
                        guessCode[i].value = computerCode[i].value;
                    }
                    count = Almost = 0; //break iteration, queue up randAll
                }
            }while(count != 0);
        }


        for(int i = 0; i < 5; i++){ //When element(s) is known to be false
            if(!guessCode[i].guessChecker()){
                do{
                    guessCode[i].value = (rand() % 8) + 1;
                }while(!guessCode[i].guessChecker());
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
                if(computerCode[j].correctGuess < FALSE/*if value has not already been marked as correct(2) or Almost(used as FALSE)(1)*/ && computerCode[j].value == guessCode[i].value){
                    computerCode[j].correctGuess = guessCode[i].correctGuess = FALSE;
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