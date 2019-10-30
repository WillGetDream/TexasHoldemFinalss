//
// Created by william shuai xiong on 10/20/19.
//




#include "DeckOfCards.h"
#include <list>
#include <iostream>
using namespace std;
DeckOfCards::DeckOfCards()
{
//put all the face values in an array as strings
    string faces[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    string suits[] = {"Heart", "Diamond", "Club", "Spade"};

    for(int count = 0; count < 52; count++)
    {
        deck[count] = Card(faces[count % 13], suits[count / 13]);
    }
    for(int i=0;i<52;i++){
        deckList.push(deck[i]);

    }
}


stack<Card> DeckOfCards::shuffle()
{
    currentCard = 0;
    stack<Card> l;
    for(int first = 0; first < 52; first++)
    {
        int second = rand()% 52;
        Card tmp = deck[first];
        deck[first] = deck[second];
        deck[second] = tmp;
    }

    for(int i=0;i<52;i++){
        deckList.push(deck[i]);
        return deckList;
    }
    return l;

}


Card DeckOfCards::dealCard()
{
    Card card=deckList.top();
    deckList.pop();
    return card;
}