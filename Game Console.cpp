#include <iostream>
#include <string>

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
            #include "Yahtzee.h"
            YahtzeeSetUp(gamesWon);
            gamesPlayed++;
        }else if(choice == "Codebreaker"){
            #include "Codebreaker.h"
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
