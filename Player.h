//
// Created by William   on 10/20/19.
//

#ifndef TEXASHOLDEM_PLAYER_H
#define TEXASHOLDEM_PLAYER_H


#include <iostream>
#include "Card.h"
using namespace std;

class Player {
public:
    string name;
    int chips;
    int chipsOnTable;
    string position;
    Card card[2];
    string status; //fold, active, allin
    int sidePot;
    int valueInHand;

    Player(){};

    Player(string name,int chips){
        this->name=name;
        this->chips=chips;
    }



};


#endif //TEXASHOLDEM_PLAYER_H
