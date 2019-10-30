//
// Created by william shuai xiong on 10/20/19.
//

#ifndef TEXASHOLDEM_CARD_H
#define TEXASHOLDEM_CARD_H

#include <string>
using namespace std;

class Card
{

private:
    string face;
    string suit;

public:
    Card();
    string print();
    Card(string cardFace, string cardSuit);
};



#endif //TEXASHOLDEM_CARD_H
