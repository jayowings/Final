#include <iostream>
#include <iomanip>

using namespace std;

class Code{
    private:
        int computerCode[5];
        int Correct, Almost;
        int turnsToGo = 12;
        bool PlayerWin = false;
    public:
        int guessCode[5];
        bool Pguess();
        bool Cguess();
        bool checkCorrect();
        Code(bool PlayerCode, int& gamesWon);
};

#include "Codebreaker.cpp"