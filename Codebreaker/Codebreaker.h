#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

enum INCODE{UNKNOWN, FALSE, TRUE};
//enum COLORVALS{} possible add-on for later in the program

class code{
    private:
        INCODE previousGuesses[8] = {UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};
    public:
        string inputArray;
        int value = 0;
        INCODE correctGuess = UNKNOWN;
        bool guessChecker();
        void Result(INCODE result, int num);
        void makeGuess();
};

class Codebreaker{
    private:
        code computerCode[5];
        code guessCode[5];
        int Correct, Almost;
        int turnsToGo = 12;
        int findEndUNKNOWN();
        bool Pguess();
        bool Cguess();
        bool checkCorrect();
        void markAutoTRUE(int& unknownCorrect, int lastChangeIndex);
        void makeGuess();
        void printGuess();
    public:
        Codebreaker(bool PlayerCode, int& gamesWon);
};

void CodebreakerSetUp(int& gamesWon);
#include "Codebreaker.cpp"