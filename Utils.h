//
// Created by William   on 10/20/19.
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
#include "maze.h"
#include <string>
#include "hash.h"
using namespace std;

class Utils {


public:
     int STRAIGHT_FLUSH = 8000000;
        // + valueHighCard()
    int FOUR_OF_A_KIND = 7000000;
        // + Quads Card Rank
    int FULL_HOUSE     = 6000000;
        // + SET card rank
    int FLUSH          = 5000000;
        // + valueHighCard()
     int STRAIGHT       = 4000000;
        // + valueHighCard()
     int SET            = 3000000;
        // + Set card value
    int TWO_PAIRS      = 2000000;
        // + High2*14^4+ Low2*14^2 + card
     int ONE_PAIR       = 1000000;
    vector<vector<Card>> vv;

    map<string, int> getRandomPlayers(int );                 //get players and chips
    set<string> RandomNames(int );                     //read file and get random name
    map<Player*,string> getRandomPosition(map<string,int> );           //get getRandomPosition
    Player processflop(map<Player*,string> players,DeckOfCards* deck,int blind,string playername);  //proess orderby pre flop,get cards ,return queue
    Player calculateWins(vector<Player> p,Card* cardtab,int size);// calculate wins
    bool isFlush( Card h[],int size );
    void sortBySuit( Card h[],int size );
    bool isStraight( Card h[] ,int size);
    bool isStraightFlush(Card h[],int size);
    void sortByFace( Card h[],int size );
    bool isRoyalFlush(Card h[],int size);
    bool is4s( Card h[],int size );
    bool isFullHouse( Card h[],int size);
    bool is3s( Card h[],int size );
    bool is2s( Card h[],int size );
    bool is22s( Card h[],int size );
    int valueHighCard( Card h[] ,int size );
    int valueOnePair( Card h[] ,int size );
    int valueTwoPairs( Card h[] ,int size );
    int valueSet( Card h[] ,int size );
    int valueFullHouse( Card h[] ,int size );
    int valueFourOfAKind( Card h[] ,int size );
    int valueStraight( Card h[] ,int size );
    int valueFlush( Card h[] ,int size );
    int valueStraightFlush( Card h[],int size );
    int valueHand( Card h[],int size );
    void dfs(int , int , int , int , Card a[],bool visited[]);
    vector<int> mergeSort(vector<int> arr);
    vector<int> merge(vector<int> left,vector<int> right);
    // void showMianPots(queue<Player*> pq);                    //calculate bets

};
#endif //TEXASHOLDEM_UTILS_H