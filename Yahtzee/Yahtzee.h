#include <iostream>
#include <cctype>
#include <string>
#include <iomanip>

using namespace std;

#include "Dice.h"

enum LOWER{FULLHOUSE = 25, SMSTRAIGHT = 30, LGSTRAIGHT = 40, YAHTZEE = 50, BONUS = 100, FAIL = 0, UPPERBONUS = 35};

class YahtzeePlayer{
    private:
        bool endPlayer;
        bool cpuPlayer;
        int ones = -1, twos = -1, threes = -1, fours = -1, fives = -1, sixes = -1;
        int threeOfAKind = -1, fourOfAKind = -1, fullHouse = -1, smallStraight = -1, largeStraight = -1, yahtzee = -1, yahtzeeBonus = 0, chance = 0;
        int upperTotal = 0, lowerTotal = 0, total = 0;
        string name;
        YahtzeePlayer * turnorder;
        void Cturn();
        void chooseScore(int d1, int d2, int d3, int d4, int d5);
    public:
        int turnsToGo = 13;
        void Pturn();
        void endGame();
        string winner();
        YahtzeePlayer(int numPlayers, bool &computerPlayer);
};

bool computer;
int numPlayers;
char cpu;

void playYahtzee(int numPlayers, bool computerPlayer, int& gamesWon);

void YahtzeeSetUp(int& gamesWon);

int notNull(int score);

#include "Yahtzee.cpp"