//
// Created by william shuai xiong on 10/20/19.
//

#ifndef TEXASHOLDEM_DECKOFCARDS_H
#define TEXASHOLDEM_DECKOFCARDS_H

#include "Card.h"
#include <stack>

class DeckOfCards {

private:
    Card deck[52]; // an array of cards of size SIZR
    stack<Card> deckList;
    int currentCard;

public:
    DeckOfCards();
    stack<Card> shuffle();
    Card dealCard();

};


#endif //TEXASHOLDEM_DECKOFCARDS_H
