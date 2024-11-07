#include <iostream>
#include <iomanip>

using namespace std;

class Code{
    private:
        int computerCode[5];
        int guessCode[5];
        int Correct, Almost;
        int turnsToGo = 12;
        bool PlayerWin = false;
        bool Pguess();
        bool Cguess();
        bool checkCorrect();
    public:
        Code(bool PlayerCode, int& gamesWon);
};

#include "Codebreaker.cpp"