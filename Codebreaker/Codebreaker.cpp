bool Code::Pguess(){
    //Make Computer Code
//****// for loop, ...; turnsToGo--)
    //User input choices, save in guessCode array

    //compare using checkCorrect

    //if win, break, return true, else loop back to //****//

    //if turnsToGo == 0 and code has not been found, return false
};

bool Code::Cguess(){//**Computer guess array could be formatted easier if each code position was a struct with members int value and enum{UNKNOWN, FALSE, ALMOST, TRUE} or a class with a built in random function**//
    //initial guess created
//****// for loop, ...; turnsToGo--)
    //Computer prints guess

    //user input numCorrect and numAlmost

    //logic to manipulate computer guess, break for computer win (return false), loop back to //****//

    //if turnsToGo == 0 and code has not been found, return true
}

bool Code::checkCorrect(){//**Class/struct suggested in Cguess would also be useful here to nullify the need for a temp array**//
    //creates temp array

    //resets Correct and Almost

//****// first for loop (i)
    //compare [i] on guess and computer code, if ==, Correct++

//****// second for loop (i)
    //if [i] on guess is in computer code (use temp or Class/struct to check if value has already been counted in Correct) Almost++;

    //display Correct and Almost, return true if win else return false
}

