//
// Created by william shuai xiong on 10/20/19.
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
    string position;
    Card card[2];

    Player(){};

    Player(string name,int chips){
        this->name=name;
        this->chips=chips;
    }



};


#endif //TEXASHOLDEM_PLAYER_H
