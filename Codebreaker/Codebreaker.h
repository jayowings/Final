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
        void Pguess();
        void Cguess();
        void checkCorrect();
        Code(bool PlayerCode);
};

#include "Codebreaker.cpp"