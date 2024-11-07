void YahtzeePlayer::Cturn(){    
    cout << "Computer turn!" << endl;
    Dice d1, d2, d3, d4, d5;
    int i = 0, temp;
    for(i; i < 3; i++){
        if(d1.save != true){//if the dice has not been saved, roll it
            d1.roll();
        }
        if(d2.save != true){
            d2.roll();
        }
        if(d3.save != true){
            d3.roll();
        }
        if(d4.save != true){
            d4.roll();
        }
        if(d5.save != true){
            d5.roll();
        }
        while(d1.value > d2.value || d2.value > d3.value || d3.value > d4.value || d4.value > d5.value){ //Sort dice for easier manipulation
            if(d1.value > d2.value){
                temp = d1.value;
                d1.value = d2.value;
                d2.value = temp;
            }
            if(d2.value > d3.value){
                temp = d2.value;
                d2.value = d3.value;
                d3.value = temp;
            }
            if(d3.value > d4.value){
                temp = d3.value;
                d3.value = d4.value;
                d4.value = temp;
            }
            if(d4.value > d5.value){
                temp = d4.value;
                d4.value = d5.value;
                d5.value = temp;
            }
        }
        //Decide which dice to save
        if(d1.value == d5.value){//Yahtzee
            break;
        }else if(d2.value == d5.value && d1.value){//Four of a Kind, hoping for Yahtzee
            d2.save = true;
            d3.save = true;
            d4.save = true;
            d5.save = true;
        }else if(d1.value == d4.value){//Four of a kind, hoping for Yahtzee
            d1.save = true;
            d2.save = true;
            d3.save = true;
            d4.save = true;
        }else if(d1.value == d2.value && d3.value == d5.value){//Full House
            break;
        }else if(d2.value + 1 == d3.value && d3.value + 1 == d4.value && (d1.value + 1 == d2.value || d4.value + 1 == d5.value) && (largeStraight == -1 || smallStraight == -1)){
            if(d1.value + 1 == d2.value && d4.value + 1 == d5.value){
                break;
            }else if(d1.value + 1 != d2.value){//Try for Large Straight regardless
                d2.save = true;
                d3.save = true;
                d4.save = true;
                d5.save = true;
            }else{
                d2.save = true;
                d3.save = true;
                d4.save = true;
                d1.save = true;
            }
        }else if(d1.value == d3.value || d2.value == d4.value || d3.value == d5.value){ //try for full house/three of a kind/four of a kind
            if(d1.value == d3.value && d4.value <5){
                d1.save = true;
                d2.save = true;
                d3.save = true;
                if(d5.value > 4){
                    d5.save = true;
                }
            }else if(d2.value == d4.value){
                d2.save = true;
                d3.save = true;
                d4.save = true;
                if(d5.value > 4){
                    d5.save = true;
                }
            }else if(d3.value == d5.value){
                d3.save = true;
                d4.save = true;
                d5.save = true;
                if(d2.value > 4){
                    d2.save = true;
                }
            }
        }else if(d5.value == 6 || d5.value == 5){ //save high values
            d5.save = true;
            if(d4.value == 6 || d4.value == 5){
                d4.save = true;
                if(d3.value == 5){
                    d3.save == true;
                    if(d2.value == 5){
                        d2.save == true;
                    }
                }
            }
        }
    }
    bool endTurn = false;
    bool TP = false, FP = false;
    cout << d1.value << ' ' << d2.value << ' ' << d3.value << ' ' << d4.value << ' ' << d5.value << endl;
    //Decide which score to take
    temp = 0;
    if(d1.value + 1 == d2.value){
        temp++;
    }
    if(d2.value + 1 == d3.value){
        temp++;
    }
    if(d3.value + 1 == d4.value){
        temp++;
    }
    if(d4.value + 1 == d5.value){
        temp++;
    }
    if(temp >= 3 && (largeStraight == -1 || smallStraight == -1)){
        if(temp == 4 && largeStraight == -1){
            cout << "Large Straight! 40 points!" << endl;
            largeStraight = LGSTRAIGHT; //Large Straight
            endTurn = true;
        }else if(smallStraight == -1){
            cout << "Small Straight! 30 points!" << endl;
            smallStraight = SMSTRAIGHT; //SM Straight
            endTurn = true;
        }
    }
    int total = d1.value + d2.value + d3.value + d4.value + d5.value;
    if(d1.value == d2.value){
        if(d2.value == d3.value){
            if(d3.value == d4.value){
                if(d4.value == d5.value){
                    //if all dice are the same and Yahtzee has not been set to 0 or 50, yahtzee = 50. End turn
                        // if all dice are the same and Yahtzee is 50, add Yahtzee bonus, but don't end turn
                    cout << "YAHTZEE!!";
                    if(yahtzee == -1){
                        cout << "50 points!" << endl;
                        yahtzee = YAHTZEE;
                        endTurn = true;
                    }
                    else if(yahtzee == 50){
                        cout << endl;
                        yahtzeeBonus += BONUS;
                    }
                }
                if(!endTurn){
                    //if four dice are the same, display and offer four of a kind if available (end turn if chosen)
                    if(fourOfAKind == -1){
                        if(total >= 20){
                            cout << "Four of a Kind! " << total << " points!" << endl;
                            fourOfAKind = total;
                            endTurn = true;
                        }else{
                            FP = true;
                        }
                    }
                }
            }
            //if three dice are the same:
            //check full house. (if available, offer and end turn if chosen)
            //offer three of a kind
            if(!endTurn){
                //Full house (d4 == d5)
                if(d4.value == d5.value && fullHouse == -1){
                    cout << "Full House! 25 points!" << endl;
                    fullHouse = FULLHOUSE;
                    endTurn = true;
                }
                //three of a kind
                if(threeOfAKind == -1){
                    if(total >= 18){
                        cout << "Three of a Kind! " << total << " points!" << endl;
                        threeOfAKind = total;
                        endTurn = true;
                    }else{
                        TP = true;
                    }
                }
            }
        }
        if(!endTurn){
            //Full house (d3 == d4 == d5)
            if(d3.value == d4.value && d4.value == d5.value && fullHouse == -1){
                cout << "Full House! 25 points!" << endl;
                fullHouse = FULLHOUSE;
                endTurn = true;
            }
        }
    }else if(d2.value == d3.value){
        if(d3.value == d4.value){
            if(d4.value == d5.value){
                //if four dice are the same, display and offer four of a kind if available (end turn if chosen)
                if(fourOfAKind == -1){
                    if(total >= 20){
                        cout << "Four of a Kind! " << total << " points!" << endl;
                        fourOfAKind = total;
                        endTurn = true;
                    }else{
                        FP = true;
                    }
                }
                if(!endTurn){
                //three of a kind
                    if(threeOfAKind == -1){
                        if(total >= 18){
                            cout << "Three of a Kind! " << total << " points!" << endl;
                            threeOfAKind = total;
                            endTurn = true;
                        }else{
                            TP = true;
                        }
                    }
                }
            }
        }
    }else if(d3.value == d4.value){
        if(d4.value == d5.value){
            //three of a kind
            if(threeOfAKind == -1){
                if(total >= 18){
                    cout << "Three of a Kind! " << total << " points!" << endl;
                    threeOfAKind = total;
                    endTurn = true;
                }else{
                    TP = true;
                }
            }
        }
    }
    int o = 0, t = 0, T = 0, f = 0, F = 0, s = 0;
    if(!endTurn){
        switch (d1.value){
            case 1:{
                o += d1.value;
                break;
            }case 2:{
                t += d1.value;
                break;
            }case 3:{
                T += d1.value;
                break;
            }case 4:{
                f += d1.value;
                break;
            }default:{
                (d1.value == 5) ? (F += d1.value) : (s += d1.value);
            }
        }
        switch (d2.value){
            case 1:{
                o += d2.value;
                break;
            }case 2:{
                t += d2.value;
                break;
            }case 3:{
                T += d2.value;
                break;
            }case 4:{
                f += d2.value;
                break;
            }default:{
                (d2.value == 5) ? (F += d2.value) : (s += d2.value);
            }
        }
        switch (d3.value){
            case 1:{
                o += d3.value;
                break;
            }case 2:{
                t += d3.value;
                break;
            }case 3:{
                T += d3.value;
                break;
            }case 4:{
                f += d3.value;
                break;
            }default:{
                (d3.value == 5) ? (F += d3.value) : (s += d3.value);
            }
        }
        switch (d4.value){
            case 1:{
                o += d4.value;
                break;
            }case 2:{
                t += d4.value;
                break;
            }case 3:{
                T += d4.value;
                break;
            }case 4:{
                f += d4.value;
                break;
            }default:{
                (d4.value == 5) ? (F += d4.value) : (s += d4.value);
            }
        }
        switch (d5.value){
            case 1:{
                o += d5.value;
                break;
            }case 2:{
                t += d5.value;
                break;
            }case 3:{
                T += d5.value;
                break;
            }case 4:{
                f += d5.value;
                break;
            }default:{
                (d5.value == 5) ? (F += d5.value) : (s += d5.value);
            }
        }
        if(s >= 18 && sixes == -1){
            cout << "Sixes! " << s << " points!" << endl;
            sixes = s;
            endTurn = true;
        }else if(F >= 15 && fives == -1){
            cout << "Fives! " << F << " points!" << endl;
            fives = F;
            endTurn = true;
        }else if(f >= 12 && fours == -1){
            cout << "Fours! " << f << "ponts!" << endl;
            fours = f;
            endTurn = true;
        }else if(T >= 9 && threes == -1){
            cout << "Threes! " << T << " points!" << endl;
            threes = T;
            endTurn = true;
        }else if(t >= 8 && twos == -1){
            cout << "Twos! " << t << " points!" << endl;
            twos = t;
            endTurn = true;
        }else if(o >= 4 && ones == -1){
            cout << "Ones! " << o << " points!" << endl;
            ones = o;
            endTurn = true;
        }else if(chance == 0 && total >= 20){
            cout << "Chance! " << total << " points!" << endl;
            chance = total;
            endTurn = true;
        }
    }

    if(!endTurn){
        if(FP){
            cout << "Four of a Kind! " << total << " points!" << endl;
            fourOfAKind = total;
            endTurn = true;
        }else if(TP){
            cout << "Three of a Kind! " << total << " points!" << endl;
            threeOfAKind = total;
            endTurn = true;
        }else if(ones == -1){
            cout << "Ones! " << o << " points!" << endl;
            ones = o;
            endTurn = true;
        }else if(twos == -1){
            cout << "Twos! " << t << " points!" << endl;
            twos = t;
            endTurn = true;
        }else if(threes == -1 && sixes + fives + fours >= 18 + 15 + 12 && T > 3){
            cout << "Threes! " << T << " points!" << endl;
            threes = T;
            endTurn = true;
        }else if(total >= 15 && chance == 0){
            cout << "Chance! " << total << " points!" << endl;
            chance = total;
            endTurn = true;
        }else if(yahtzee == -1){
            cout << "Zero in Yahtzee." << endl;
            yahtzee = FAIL;
            endTurn = true;
        }else if(total >= 10 && chance == 0){
            cout << "Chance! " << total << " points!" << endl;
            chance = total;
            endTurn = true;
        }else if(fours == -1 && sixes + fives >= 33 && f > 4){
            cout << "Fours! " << f << " points!" << endl;
            fours = f;
            endTurn = true;
        }else if(threes == -1){
            cout << "Threes! " << T << " points!" << endl;
            threes = T;
            endTurn = true;
        }else if(largeStraight == -1){
            cout << "Zero in Large Straight." << endl;
            largeStraight = FAIL;
            endTurn = true;
        }else if(smallStraight == -1){
            cout << "Zero in Small Straight." << endl;
            smallStraight = FAIL;
            endTurn = true;
        }else if(fours == -1){
            cout << "Fours! " << f << " points!" << endl;
            fours = f;
            endTurn = true;
        }else if(fullHouse ==-1 ){
            cout << "Zero in Full House." << endl;
            fullHouse = FAIL;
            endTurn = true;
        }else if(chance == -1){
            cout << "Chance! " << total << " points!" << endl;
            chance == total;
            endTurn = true;
        }else if(fives == -1){
            cout << "Fives! " << F << " points!" << endl;
            fives = F;
            endTurn = true;
        }else if(sixes == -1){
            cout << "Sixes! " << s << " points!" << endl;
            sixes = s;
            endTurn = true;
        }else{
            cout << "Houston, we have a problem";
        }
    }
};

void YahtzeePlayer::chooseScore(int d1, int d2, int d3, int d4, int d5){
    //sort dice in ascending order with temp variables. check sm straight or lg straight (if available, set and end turn)
    int temp;
    char takePoints;
    bool TP = false, FP = false, FHP = false, SP = false, LP = false, YP = false;
    int total = (d1 + d2 + d3 + d4 + d5);
    bool endTurn;
    while(d1 > d2 || d2 > d3 || d3 > d4 || d4 > d5){
        if(d1 > d2){
            temp = d1;
            d1 = d2;
            d2 = temp;
        }
        if(d2 > d3){
            temp = d2;
            d2 = d3;
            d3 = temp;
        }
        if(d3 > d4){
            temp = d3;
            d3 = d4;
            d4 = temp;
        }
        if(d4 > d5){
            temp = d4;
            d4 = d5;
            d5 = temp;
        }
    }
    temp = 0;
    if(d1 + 1 == d2){
        temp++;
    }
    if(d2 + 1 == d3){
        temp++;
    }
    if(d3 + 1 == d4){
        temp++;
    }
    if(d4 + 1 == d5){
        temp++;
    }
    if(temp >= 3 && (largeStraight == -1 || smallStraight == -1)){
        if(temp == 4 && largeStraight == -1){
            cout << "Large Straight! 40 points! Y/N ";
            cin >> takePoints;
            if(takePoints != 'N' && takePoints != 'n'){
                largeStraight = LGSTRAIGHT;
                endTurn = true;
            }else{
                LP = true;
                if(smallStraight == -1) {
                    SP = true;
                }
            }
            //LG Straight
        }else if(smallStraight == -1){
            cout << "Small Straight! 30 points! Y/N ";
            cin >> takePoints;
            if(takePoints != 'N' && takePoints != 'n'){
                smallStraight = SMSTRAIGHT;
                endTurn = true;
            }else{
                LP = false;
                SP = true;
            }
            //SM Straight
        }
    }
    //check number of same type dice
    if(d1 == d2){
        if(d2 == d3){
            if(d3 == d4){
                if(d4 == d5){
                    //if all dice are the same and Yahtzee has not been set to 0 or 50, yahtzee = 50. End turn
                        // if all dice are the same and Yahtzee is 50, add Yahtzee bonus, but don't end turn
                    cout << "YAHTZEE!!";
                    if(yahtzee == -1){
                        cout << "50 points! Y/N ";
                        cin >> takePoints;
                        if(takePoints != 'N' && takePoints != 'n'){
                            yahtzee = YAHTZEE;
                            endTurn = true;
                        }else{
                            YP = true;
                        }
                    }
                    else if(yahtzee == 50){
                        yahtzeeBonus += BONUS;
                        cout << "BONUS 100 POINTS!!" << endl;
                    }else if(yahtzee == 0){
                        cout << ":.-( so sad." << endl;
                    }
                }
                if(!endTurn){
                    //if four dice are the same, display and offer four of a kind if available (end turn if chosen)
                    if(fourOfAKind == -1){
                        cout << "Four of a kind! " << total << " points! Y/N ";
                        cin >> takePoints;
                        if(takePoints != 'N' && takePoints != 'n'){
                            fourOfAKind = total;
                            endTurn = true;
                        }else{
                            FP = true;
                        }
                    }
                }
            }
            //if three dice are the same:
            //check full house. (if available, offer and end turn if chosen)
            //offer three of a kind
            if(!endTurn){
                //Full house (d4 == d5)
                if(d4 == d5 && fullHouse == -1){
                    cout << "Full House! 25 points! Y/N ";
                    cin >> takePoints;
                    if(takePoints != 'N' && takePoints != 'n'){
                        fullHouse = FULLHOUSE;
                        endTurn = true;
                    }else{
                        FHP = true;
                    }
                }
                //three of a kind
                if(!endTurn){
                    if(threeOfAKind == -1){
                       cout << "Three of a kind! " << total << " points! Y/N ";
                        cin >> takePoints;
                        if(takePoints != 'N' && takePoints != 'n'){
                           threeOfAKind = total;
                            endTurn = true;
                        }else {
                            TP = true;
                       }
                    }
                }
            }
        }
        if(!endTurn){
            //Full house (d3 == d4 == d5)
            if(d3 == d4 && d4 == d5 && fullHouse == -1){
                cout << "Full House! 25 points! Y/N ";
                cin >> takePoints;
                if(takePoints != 'N' && takePoints != 'n'){
                    fullHouse = FULLHOUSE;
                    endTurn = true;
                }else{
                    FHP = true;
                }
            }
        }
    }else if(d2 == d3){
        if(d3 == d4){
            if(d4 == d5){
                //if four dice are the same, display and offer four of a kind if available (end turn if chosen)
                if(fourOfAKind == -1){
                    cout << "Four of a kind! " << total << " points! Y/N ";
                    cin >> takePoints;
                    if(takePoints != 'N' && takePoints != 'n'){
                        fourOfAKind = total;
                        endTurn = true;
                    }else{
                        FP = true;
                    }
                }
            }
        }
        if(!endTurn){
            //three of a kind
                if(threeOfAKind == -1){
                    cout << "Three of a kind! " << total << " points! Y/N ";
                    cin >> takePoints;
                    if(takePoints != 'N' && takePoints != 'n'){
                        threeOfAKind = total;
                        endTurn = true;
                    }else{
                        TP = true;
                    }
                }
            }
    }else if(d3 == d4){
        if(d4 == d5){
            //three of a kind
            if(threeOfAKind == -1){
                cout << "Three of a kind! " << total << " points! Y/N ";
                cin >> takePoints;
                if(takePoints != 'N' && takePoints != 'n'){
                    threeOfAKind = total;
                    endTurn = true;
                }else{
                    TP = true;
                }
            }
        }
    }
    if(!endTurn){//display dice again and offer availble from this list "(C)hance:(value) (O)nes:(value) (t)wos:(value) (T)hrees:(value) (f)ours:(value) (F)ives:(value) (S)ixes:(value) or (Z)ero"
            //if none above available or (Z)ero chosen, display all other available options and choose where to take a zero. Run logic again for zero taken to avoid unnecessarry zeros
        int o = 0, t = 0, T = 0, f = 0, F = 0, s = 0;
        switch (d1){
            case 1:{
                o += d1;
                break;
            }case 2:{
                t += d1;
                break;
            }case 3:{
                T += d1;
                break;
            }case 4:{
                f += d1;
                break;
            }default:{
                (d1 == 5) ? (F += d1) : (s += d1);
            }
        }
        switch (d2){
            case 1:{
                o += d2;
                break;
            }case 2:{
                t += d2;
                break;
            }case 3:{
                T += d2;
                break;
            }case 4:{
                f += d2;
                break;
            }default:{
                (d2 == 5) ? (F += d2) : (s += d2);
            }
        }
        switch (d3){
            case 1:{
                o += d3;
                break;
            }case 2:{
                t += d3;
                break;
            }case 3:{
                T += d3;
                break;
            }case 4:{
                f += d3;
                break;
            }default:{
                (d3 == 5) ? (F += d3) : (s += d3);
            }
        }
        switch (d4){
            case 1:{
                o += d4;
                break;
            }case 2:{
                t += d4;
                break;
            }case 3:{
                T += d4;
                break;
            }case 4:{
                f += d4;
                break;
            }default:{
                (d4 == 5) ? (F += d4) : (s += d4);
            }
        }
        switch (d5){
            case 1:{
                o += d5;
                break;
            }case 2:{
                t += d5;
                break;
            }case 3:{
                T += d5;
                break;
            }case 4:{
                f += d5;
                break;
            }default:{
                (d5 == 5) ? (F += d5) : (s += d5);
            }
        }
        cout << d1 << ' ' << d2 << ' ' << d3 << ' ' << d4 << ' ' << d5 << endl;
        bool available;
        if(chance == 0){
            cout << "(C)hance: " << total << ' ';
            available = true;
        }
        if(ones == -1 && o != 0){
            cout << "(o)nes: " << o << ' ';
            available = true;
        }
        if(twos == -1 && t != 0){
            cout << "(t)wos: " << t << ' ';
            available = true;
        }
        if(threes == -1 && T != 0){
            cout << "(T)hrees: " << T << ' ';
            available = true;
        }
        if(fours == -1 && f != 0){
            cout << "(f)ours: " << f << ' ';
            available = true;
        }
        if(fives == -1 && F != 0){
            cout << "(F)ives: " << F << ' ';
            available = true;
        }
        if(sixes == -1 && s != 0){
            cout << "(s)ixes: " << s << ' ';
            available = true;
        }
        if(available == true){
            cout << "or (Z)ero\n";
            cin >> takePoints;
        }else {
            takePoints = 'Z';
        };
        while(!endTurn){
            switch (takePoints){
                case 'C':{
                    if(chance == 0){
                        cout << "Chance: " << total << " points!" << endl;
                        chance = total;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'o':{
                    if(ones == -1){
                        cout << "Ones: " << o << " points!" << endl;
                        ones = o;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 't':{
                    if(twos == -1){
                        cout << "Twos: " << t << " points!" << endl;
                        twos = t;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'T':{
                    if(threes == -1){
                        cout << "Threes: " << T << " points!" << endl;
                        threes = T;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'f':{
                    if(fours == -1){
                        cout << "Fours: " << f << " points!" << endl;
                        fours = f;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'F':{
                    if(fives == -1){
                        cout << "Fives: " << F << " points!" << endl;
                        fives = F;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 's':{
                    if(sixes == -1){
                        cout << "Sixes: " << s << " points!" << endl;
                        sixes = s;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case '3':{
                    if(TP){
                        cout << "3 of a kind: " << total << endl;
                        threeOfAKind = total;
                        endTurn = true;
                    }else if(threeOfAKind == -1){
                        cout << "3 of a kind: " << FAIL << endl;
                        threeOfAKind = FAIL;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case '4':{
                    if(FP){
                        cout << "4 of a kind: " << total << endl;
                        fourOfAKind = total;
                        endTurn = true;
                    }else if(fourOfAKind == -1){
                        cout << "4 of a kind: " << FAIL << endl;
                        fourOfAKind = FAIL;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'H':{
                    if(FHP){
                        cout << "Full House: " << FULLHOUSE << endl;
                        fullHouse = FULLHOUSE;
                        endTurn = true;
                    }else if(fullHouse == -1){
                        cout << "Full House: " << FAIL << endl;
                        fullHouse = FAIL;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'S':{
                    if(SP){
                        cout << "Small Straight: " << SMSTRAIGHT << endl;
                        smallStraight = SMSTRAIGHT;
                        endTurn = true;
                    }else if(smallStraight == -1){
                        cout << "Small Straight: " << FAIL << endl;
                        smallStraight = FAIL;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'L':{
                    if(LP){
                        cout << "Large Straight: " << LGSTRAIGHT << endl;
                        largeStraight = LGSTRAIGHT;
                        endTurn = true;
                    }else if(largeStraight == -1){
                        cout << "Large Straight: " << FAIL << endl;
                        largeStraight = FAIL;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }case 'Y':{
                    if(YP){
                        cout << "Yahtzee: " << YAHTZEE << endl;
                        yahtzee = YAHTZEE;
                        endTurn = true;
                    }else if(yahtzee == -1){
                        cout << "Yahtzee: " << FAIL << endl;
                        yahtzee = FAIL;
                        endTurn = true;
                    }else{
                        takePoints = 'Z';
                    }
                    break;
                }default:{
                    cout << "Here are all your options again:\n";
                    if(ones == -1){
                        cout << "(o): " << o << ' ';
                    }
                    if(twos == -1){
                        cout << "(t): " << t << ' ';
                    }
                    if(threes == -1){
                        cout << "(T): " << T << ' ';
                    }
                    if(fours == -1){
                        cout << "(f): " << f << ' ';
                    }
                    if(fives == -1){
                        cout << "(F): " << F << ' ';
                    }
                    if(sixes == -1){
                        cout << "(s): " << s << ' ';
                    }
                    cout << endl;
                    if(TP){
                        cout << "(3) of a kind: " << total << ' ';
                    }else if(threeOfAKind == -1){
                        cout << "(3) of a kind: " << FAIL << ' ';
                    }
                    if(FP){
                        cout << "(4) of a kind: " << total << ' ';
                    }else if(fourOfAKind == -1){
                        cout << "(4) of a kind: " << FAIL << ' ';
                    }
                    if(FHP){
                        cout << "Full (H)ouse: " << FULLHOUSE << ' ';
                    }else if(fullHouse == -1){
                        cout << "Full (H)ouse: " << FAIL << ' ';
                    }
                    cout << endl;
                    if(SP){
                        cout << "(S)mall Straight: " << SMSTRAIGHT << ' ';
                    }else if(smallStraight == -1){
                        cout << "(S)mall Straight: " << FAIL << ' ';
                    }
                    if(LP){
                        cout << "(L)arge Straight: " << LGSTRAIGHT << ' ';
                    }else if(largeStraight == -1){
                        cout << "(L)arge Straight: " << FAIL << ' ';
                    }
                    cout << endl;
                    if(YP){
                        cout << "(Y)ahtzee: " << YAHTZEE << endl;
                    }else if(yahtzee == -1){
                        cout << "(Y)ahtzee: " << FAIL << endl;
                    }
                    if(chance == 0){
                        cout << "(C)hance: " << total << endl;
                    }
                    cin >> takePoints;
                }
            }
        }
    }
};

void YahtzeePlayer::Pturn(){ //roll logic and save dice logic, call other functions
    cout << name << ", your turn!" << endl;
    Dice d1, d2, d3, d4, d5;
    int i = 0;
    for(i; i < 3; i++){//three tries per dice
        if(d1.save != true){//if the dice has not been saved, roll it
            d1.roll();
        }
        if(d2.save != true){
            d2.roll();
        }
        if(d3.save != true){
            d3.roll();
        }
        if(d4.save != true){
            d4.roll();
        }
        if(d5.save != true){
            d5.roll();
        }
        char s1, s2, s3, s4, s5;
        cout << d1.value << " " << d2.value << " " << d3.value << " " << d4.value << " " << d5.value << endl;
        if(i == 2){ //There is no reason to save dice the third time
            break;
        }else{
            cout << "Push Y/N for each dice to save it (No spaces, e.g. YNYYN)" << endl;//Dice must be saved every time
            cin >> s1 >> s2 >> s3 >> s4 >> s5;
            if((char) toupper(s1) == 'Y'){
                d1.save = true;
            }else{
                d1.save = false;
            }if((char) toupper(s2) == 'Y'){
                d2.save = true;
            }else{
                d2.save = false;
            }if((char) toupper(s3) == 'Y'){
                d3.save = true;
            }else{
                d3.save = false;
            }if((char) toupper(s4) == 'Y'){
                d4.save = true;
            }else{
                d4.save = false;
            }if((char) toupper(s5) == 'Y'){
                d5.save = true;
            }else{
                d5.save = false;
            }
            if((char) toupper(s1) == 'Y' && (char) toupper(s2) == 'Y' && (char) toupper(s3) == 'Y' && (char) toupper(s4) == 'Y' && (char) toupper(s5) == 'Y'){
                break; //if all dice are saved, take these dice to decide score
            }
        }
    }
    chooseScore(d1.value, d2.value, d3.value, d4.value, d5.value);
     if(!endPlayer){
        if(turnorder->computer){//Computer turn will have its own logic
            turnorder->Cturn();
        }else{
            turnorder->Pturn();//each player will take their turn in order, 
        }
     }
};

void YahtzeePlayer::endGame(){
    char done;
    upperTotal = notNull(ones) + notNull(twos) + notNull(threes) + notNull(fours) + notNull(fives) + notNull(sixes);
    if(upperTotal >= 63){
        upperTotal += UPPERBONUS;
    }
    lowerTotal = notNull(threeOfAKind) + notNull(fourOfAKind) + notNull(fullHouse) + notNull(smallStraight) + notNull(largeStraight) + notNull(yahtzee) + yahtzeeBonus + chance;
    total = upperTotal + lowerTotal;
    cout <<  name << endl;
    cout << "Ones:____________" << setw(2) << right << setfill('_') << notNull(ones) << endl;
    cout << "Twos:____________" << setw(2) << right << setfill('_') << notNull(twos) << endl;
    cout << "Threes:__________" << setw(2) << right << setfill('_') << notNull(threes) << endl;
    cout << "Fours:___________" << setw(2) << right << setfill('_') << notNull(fours) << endl;
    cout << "Fives:___________" << setw(2) << right << setfill('_') << notNull(fives) << endl;
    cout << "Sixes:___________" << setw(2) << right << setfill('_') << notNull(sixes) << endl;
    if(upperTotal > 63){
        cout << "BONUS!!" << endl;
    }
    cout << "Upper Total:____" << setw(3) << right << setfill('_') << upperTotal << endl;
    cout << "Three of a Kind:_" << setw(2) << right << setfill('_') << notNull(threeOfAKind) << endl;
    cout << "Four of a Kind:__" << setw(2) << right << setfill('_') << notNull(fourOfAKind) << endl;
    cout << "Full House:______" << setw(2) << right << setfill('_') << notNull(fullHouse) << endl;
    cout << "SM Straight:_____" << setw(2) << right << setfill('_') << notNull(smallStraight) << endl;
    cout << "LG Straight:_____" << setw(2) << right << setfill('_') << notNull(largeStraight) << endl;
    cout << "Yahtzee:_________" << setw(2) << right << setfill('_') << notNull(yahtzee) << endl;
    if(yahtzee != 0){
        cout << "Yahtzee Bonus:__" << setw(3) << right << setfill('_') << yahtzeeBonus << endl;
    }
    cout << "Chance:__________" << setw(2) << right << setfill('_') << chance << endl;
    cout << "Lower Total:____" << setw(3) << right << setfill('_') << lowerTotal << endl;
    cout << "Total:_________" << setw(4) << right << setfill('_') << total << endl;
    cin >> done;
    if(!endPlayer && !computer){
        turnorder->endGame();
    }
}; //calculating totals

string YahtzeePlayer:: winner(){
    YahtzeePlayer * max = this;
    YahtzeePlayer * runner = this->turnorder;
    while(!runner->endPlayer){
        if(max->total < runner->total){
            max = runner;
        }
        runner = runner->turnorder;
    }
    if(max->total < runner->total){
        max = runner;
    }
    return max->name;
}

YahtzeePlayer::YahtzeePlayer(int  numPlayers, bool &computerPlayer){
    if (numPlayers > 1){
        cout << "Player name: "; //Get player name
        cin >> name;
        turnorder = new YahtzeePlayer((numPlayers - 1), computerPlayer); //Recursion to create last player first and set player order
        computer = false;
        endPlayer = false;
    }else{
        computer = computerPlayer;
        if(computer != true){ //If the last player is a computer, skip
            cout << "Player name: ";
            cin >> name;
            endPlayer = true; //Announce this is the last player
        }else{
            name = "Computer";
        }
        computerPlayer = false;
    }
};

void playYahtzee(int numPlayers, bool computerPlayer, int& gamesWon){
    bool cpu = computerPlayer; 
    YahtzeePlayer Game1(numPlayers, cpu);
    for(Game1.turnsToGo; Game1.turnsToGo != 0; Game1.turnsToGo--){
        Game1.Pturn();
        Game1.endGame();
    };
    string winner = Game1.winner();
    if(winner != "Computer"){
        gamesWon++;
    }
};

void YahtzeeSetUp(int& gamesWon){
    cout << "Welcome to Yahtzee!\n";
    cout << "How many players? ";
    cin >> numPlayers;
    cout << "Computer player? Y/N ";
    cin >> cpu;
    if (cpu == 'N' || cpu == 'n'){
        computer = false;
    }else{
        computer = true;
    }
    playYahtzee(numPlayers, computer, gamesWon);
}

int notNull(int score){
    if(score == -1){
        return 0;
    }else{
        return score;
    }
}