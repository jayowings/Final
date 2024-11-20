bool code::guessChecker(){
    int forcedTRUE = 0;
    for(int i = 0; i < 8; i++){
        if(previousGuesses[i] == TRUE){ //if there is a value that has been proven true
            value = i + 1; //set value to true value //Value == index + 1
            return true;
        }else if(previousGuesses[i] == FALSE){
            forcedTRUE++;
        }
    }
    if (forcedTRUE == 7){
        for(int i = 0; i<8; i++){
            if(previousGuesses[i] != FALSE){
                Result(TRUE, i+1);
                value = i+1;
                return true;
            }
        }
    }
    if(previousGuesses[value - 1] == FALSE){ //if this guess has already been proven wrong
        return false;
    }
    return true; //if value is unknown and no known true value exists, guess is allowed
}

void code::Result(INCODE result, int num = 0){ //set flags
    if(num == 0){ //default value was giving me troubles
        num = value;
    }
    if(previousGuesses[num - 1] < result){ //Will not override TRUE
        previousGuesses[num - 1] = result;
        if(num == value){ //if num is the current value
            correctGuess = result;
        }
    }
}

void code::makeGuess(){
    if(previousGuesses[value - 1] == TRUE){
        exit;
    }
    int preVal = value;
    do{//new value cannot be value previously proven as false
        value = (rand() % 8) + 1;
    }while(value == preVal || !guessChecker()); //TRUE could override preValue check
    correctGuess = previousGuesses[value - 1];
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
        cin >> guessCode[4].inputArray;
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
            cout << "Player wins!\n";
            return true;
        }
    //if win, break, return true, else loop back to //****//
    }
    //if turnsToGo == 0 and code has not been found, return false
    cout << "Computer wins!\nBetter luck next time!\n";
    return false;
};

bool Codebreaker::Cguess(){//**Computer guess array could be formatted easier if each code position was a struct with members int value and enum{UNKNOWN, FALSE, ALMOST, TRUE} or a class with a built in random function**//
    //initial guess created
    for(int i = 0; i < 5; i++){
        computerCode[i].value = 0;
    }
    makeGuess();
    int prevCorrect = 0, prevAlmost = 0;

    for ( ; turnsToGo > 0; turnsToGo--){
    //Computer prints guess
        printGuess();

        while(true){
            cout << "\nHow many are in the correct position? ";
    //user input numCorrect and numAlmost, break for computer win (return false)
            cin >> Correct;
            if(Correct == 5){
                cout << "Computer wins!\nBetter luck next time!\n";
                return false;//Computer wins
            }else if(turnsToGo == 1){
                cout << "Player wins!\n";
                return true;
            }
            cout << "How many are in the wrong position? ";
            cin >> Almost;
            if(Correct + Almost > 5 || (Correct == 4 && Almost == 1)){ //invalid input catch
                cout << "Invalid input. Only 5 elements can be judged. Please try again.";
            }else{
                break;
            }
        }

        int ComparePrev[11];
        ComparePrev[10] = 5;
        for(int i = 0; i < 5; i++){ //Check values in the same position
            ComparePrev[i] = guessCode[i].value;
            ComparePrev[i + 5] = computerCode[i].value;
            if(ComparePrev[i] == ComparePrev[i + 5]){//if values stayed the same, set to a null value
                ComparePrev[10]--;
                ComparePrev[i] = -1;
                ComparePrev[i + 5] = 0;
            }
        }

        //Setting Flags
        //only works if ComparePrev[10] == 1
        if(prevCorrect > Correct && ComparePrev[10] == 1){//previous correct found by replacement
            for(int i = 0; i < 5; i++){ //code index for both changed values is the same
                if(ComparePrev[i] > 0){ //when changed value is found
                    guessCode[i].value = computerCode[i].value; //change value to Correct value
                    guessCode[i].Result(TRUE); //flag value as true
                    Correct++; //for future tests
                }
            }
        }else if(Correct > prevCorrect && ComparePrev[10] == 1){//correct found by luck
            for(int i = 0; i<5; i++){
                if(ComparePrev[i] > 0){
                    guessCode[i].Result(TRUE);
                }
            }
        }else if(ComparePrev[10] == 1 && prevCorrect == Correct){//if no change for correct (both values are false)
            for(int i = 0; i<5; i++){ //automatically sets both values to FALSE
                if(ComparePrev[i] > 0){
                    guessCode[i].Result(FALSE);
                    guessCode[i].Result(FALSE, computerCode[i].value);
                }
            }
            if(Almost == 0){//if no nonCorrect values are in the current code
                for(int i = 0; i<5; i++){
                    if(ComparePrev[i] > 0){ //changed value is false
                        for(int j = 0; j<5; j++){
                            if (guessCode[j].correctGuess != TRUE){ //values stored as TRUE need no more information
                                guessCode[j].Result(FALSE, guessCode[i].value);
                            }
                        }
                    }
                }
            }
            if(prevAlmost == 0){//if no values were in the prevCode
                for(int i = 0; i<5; i++){
                    if(ComparePrev[i]>0){ //changed value was false
                        for(int j = 0; j<5; j++){
                            if (guessCode[j].correctGuess != TRUE){ //values stored as TRUE need no more information
                                guessCode[j].Result(FALSE, computerCode[i].value);
                            }
                        }
                    }
                }
            }
        }


        int unknownCorrect = Correct; //when a value is known to be correct, tests can be skipped
        for(int i = 0; i <5; i++){
            computerCode[i].value = guessCode[i].value; //previous Code is now obsolete, store for next iteration
            if(guessCode[i].correctGuess == TRUE){
                unknownCorrect--;
            }
        }
        prevAlmost = Almost;
        prevCorrect = Correct;

        //Changeing values
        //learn correct values
        if(unknownCorrect > 0){
            int newValIndex = 0;
            int lowerTrues = 0;
            //moving right to left, add a new value to test previous value
            for(int i = 0; i < 5; i++){
                if(guessCode[i].correctGuess == TRUE){
                    lowerTrues++;
                }
                if(ComparePrev[i] > 0){//Find last value that was changed
                    if(i == lowerTrues){//AlmostShuffle or first guess
                        newValIndex = findEndUNKNOWN();
                    }else if(i + 1 == unknownCorrect + lowerTrues){//if the value to be changed is the last necessary value to be changed, all remaining values of lower indexes are TRUE
                        markAutoTRUE(unknownCorrect, i);
                        break;
                    }else{//previous change was "Correct Test" and was not last possible value change
                        newValIndex = i - 1;
                        while(true){
                            if(guessCode[newValIndex].correctGuess == TRUE){//skip true values
                                newValIndex--;
                            }else{
                                break;
                            }
                        }
                    }
                    guessCode[newValIndex].makeGuess();
                    break;
                }
            }
        }

        //"Almost shuffle"
        if(Almost > 0 && unknownCorrect == 0){
            int numShuffled = 0;
            for(int i = 0; i < 5; i++){ //count numShuffled
                if(guessCode[i].correctGuess == TRUE){
                    continue; //skip TRUE values
                }else{
                    guessCode[i].Result(FALSE, guessCode[i].value); //all guesses that are not TRUE are FALSE
                    numShuffled++;
                }
            }
            int prevValues[numShuffled];
            for(int i = 0, j = 0; i < 5 && j < numShuffled; i++){//set values in prevValues
                if(guessCode[i].correctGuess == TRUE){
                    continue; //skip TRUE values
                }else{
                    prevValues[j] = guessCode[i].value;
                    if(j == 0){ //add new value in prevValues[0]
                        guessCode[i].makeGuess();
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
                        if(j == numShuffled){
                            j = 0;
                        }
                        guessCode[i].value = prevValues[j];
                        j++;
                    }
                }
                j++; count++; //in case of next iteration
                if(count == 5){//randomizes values so as not to enter an infinite loop
                    makeGuess();
                    count = 0; //break iteration
                }
                for(int i = 0; i < 5; i ++){ //check need for next iteration
                    if(!guessCode[i].guessChecker()){ //if new value from shuffle is FALSE, shuffle will run again
                        break;
                    }
                    if(i == 4){//if check has passed for all values
                        count = 0; //end iterations
                    }
                }
            }while(count != 0);
        }

        //all known true of false, no almost
        if(Almost == 0 && unknownCorrect == 0){
            for(int i = 0; i < 5; i++){ //flag values and randomize FALSE
                if(guessCode[i].correctGuess == TRUE){
                    continue; //skip TRUE values
                }else{
                    for(int j = 0; j < 5; j++){//all guesses that are not TRUE are FALSE
                        if(guessCode[j].value == guessCode[i].value && guessCode[j].correctGuess == TRUE){ // DO NOT mark know TRUE values as FALSE
                            continue;
                        }else{
                            guessCode[j].Result(FALSE, guessCode[i].value);
                        }
                    }
                }
            }
            makeGuess();
        }
    }
    //if turnsToGo == 0 and code has not been found, return true
    cout << "Player wins!\n";
    return true;
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

void Codebreaker::makeGuess(){
    for(int i = 0; i < 5; i++){
        guessCode[i].makeGuess();
    }
}

void Codebreaker::printGuess(){
    for(int i = 0; i < 5; i++){
        cout << guessCode[i].value;
        if(i != 4){
            cout << ',';
        }
    }
}

void Codebreaker::markAutoTRUE(int& unknownCorrect, int lastChangeIndex){
    while(unknownCorrect > 0){
        lastChangeIndex--;
        if(guessCode[lastChangeIndex].correctGuess != TRUE){//skip true values
            guessCode[lastChangeIndex].Result(TRUE); //
            unknownCorrect--; //correct has been learned, allows next functions to trigger
        }
    }
}

int Codebreaker::findEndUNKNOWN(){
    int endIndex;
    for(int i = 4; i>=0; i--){
        if(guessCode[i].correctGuess != TRUE){
            endIndex = i;
            return endIndex;
        }
    }
    return 0;
}

Codebreaker::Codebreaker(bool PlayerCode, int& gamesWon){
    if(PlayerCode){
        if(Pguess()){
            gamesWon++;
        }
    //if Player is codebreaker, run Pguess, if true, gamesWon++
    }else{
        if(Cguess()){
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
