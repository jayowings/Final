#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum INCODE{UNKNOWN, FALSE, ALMOST, TRUE};
//enum COLORVALS{} possible add-on for later in the program

struct code{
    string inputArray;
    int value = 0;
    INCODE correctGuess = UNKNOWN;
};


class Code{
    private:
        code computerCode[5];
        code guessCode[5];
        int Correct, Almost;
        int turnsToGo = 12;
        bool PlayerWin = false;
        bool Pguess();
        bool Cguess();
        bool checkCorrect();
    public:
        Code(bool PlayerCode, int& gamesWon);
};

//#include "Codebreaker.cpp"