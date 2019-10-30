//
// Created by william shuai xiong on 10/20/19.
//

#ifndef TEXASHOLDEM_UTILS_H
#define TEXASHOLDEM_UTILS_H
#include <iostream>
#include <list>
#include <set>
#include <map>
#include "Player.h"
#include "Position.h"
#include "DeckOfCards.h"
#include <queue>
using namespace std;

class Utils {
public:
    map<string, int> getRandomPlayers(int n);                 //get players and chips
    set<string> RandomNames(int n);                     //read file and get random name
    map<Player*,string> getRandomPosition(map<string,int> );           //get getRandomPosition
    map<string,Player*> processOrderByPreflop(map<Player*,string> players,DeckOfCards* deck,int blind);  //proess orderby pre flop,get cards ,return queue
   // void showMianPots(queue<Player*> pq);                    //calculate bets

};
#endif //TEXASHOLDEM_UTILS_H