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
    int getFace(){
        if(!face.compare("Ace")){
            return 14;
        }else if(!face.compare("J")){
            return 11;
        }else if(!face.compare("Q")){
            return 12;
        }else if(!face.compare("K")){
            return 13;
        }else{
            return atoi(face.c_str() );
        }

      };
    string getSuit(){return suit;};
};



#endif //TEXASHOLDEM_CARD_H
