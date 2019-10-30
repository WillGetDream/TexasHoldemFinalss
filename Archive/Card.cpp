//
// Created by william shuai xiong on 10/20/19.
//

//assigns the 52 cards to deck
#include "Card.h"

Card::Card(string cardFace, string cardSuit)
{
    face = cardFace;
    suit = cardSuit;
}

Card::Card()
{
}
string Card::print()
{
    return (face + " of " + suit);
}

