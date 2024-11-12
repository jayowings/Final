#include <iostream>
#include <string>
#include "Codebreaker.h"
#include "Yahtzee.h"

using namespace std;

string choice;
int gamesWon = 0;
int gamesPlayed = 0;

int main(){
    cout << "Welcome Player! Select a Game!\n";
    while(true){
        cout << "Yahtzee, Codebreaker"/*add more as game progresses*/ << ", or Quit" << endl; 
        //using string instead of char to allow for a greater library of games
        cin >>choice;
        if(choice == "Quit"){
            break;
        }else if(choice == "Yahtzee"){
            YahtzeeSetUp(gamesWon);
            gamesPlayed++;
        }else if(choice == "Codebreaker"){
            CodebreakerSetUp(gamesWon);
            gamesPlayed++;
        };
    }
    cout << "Thanks for playing!\n";
    if (gamesPlayed > 0){
        cout << "You played " << gamesPlayed << " games!" << endl;
        cout << "You won " << gamesWon << " games!";
    };
}
