//
// Created by William   on 10/20/19.
//



#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "Colors.h"
#include "Utils.h"
#include "DeckOfCards.h"
using namespace std;
int main() {
    //seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int blind,name,chips,numPlayers,mainPot;
    string player1;
    Player player;
    Player win;


    bool flag=1;
    while(flag){

            if(player.chips<=0) {
                //Input or initialize values Here
                cout << FBLU("Welcome to play Texas Holdem!（heads-up no-limit） ") << endl;
                cout << FBLU("Please Enter the Blind (10,20,5,2): ") << endl;
                cin>>blind;

                cout << FBLU("Please Enter the name: ") << endl;
                 cin>>player.name;
                //player.name = "William";
                cout << FBLU("How many chips do you need to buy?(600 or more) ") << endl;
                 cin>>player.chips;
               // player.chips = 600;
               // cout << FBLU("How many players do you want to play with?(2-6)") << endl;

                //player cant be n<2 or n>6
                // cin>>numPlayers;
                numPlayers = 2;
                while (numPlayers < 2 || numPlayers > 6) {
                    cout << FRED("Player need to be 2-6!") << endl;
                    cin >> numPlayers;
                }
            }


            cout<<"Hello "<<player.name<<" you will start to play blind "<<blind<<"/"<<blind*2<<" game! please waiting for other player"<<endl;

            //get Random player name and position
            Utils utils;
            map<string,int> Pl=utils.getRandomPlayers(numPlayers);
            Pl[player.name]=player.chips;
            map<Player*,string> Players=utils.getRandomPosition(Pl);
            map<Player*,string>::iterator itr;

            cout<<"game start..."<<endl;
            cout<<"shuffer card..."<<endl;
            DeckOfCards* deck=new DeckOfCards();
            for(int i=0;i<10;i++){
                deck->shuffle();
            }


            cout<<endl;

            //Pre-flop everyone get two cards
            //push to queues

            player=utils.processflop(Players,deck,blind,player.name);

        string sflag;
        cout<<"do you want to continue game?(Y or N)";
        cin>>sflag;

        if(sflag=="Y"){
            flag=1;
        }else{
            flag=0;
        }
    }


    return 0;
}
