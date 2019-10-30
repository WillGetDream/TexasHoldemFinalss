//
// Created by william shuai xiong on 10/20/19.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>   // for exit(), srand(), rand()
#include "list"
#include "Utils.h"
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include "Colors.h"
#include "Player.h"
#include "Position.h"
#include <vector>
#include <random>
#include <queue>
#include "DeckOfCards.h"

using namespace std;
int myrandom (int i) { return std::rand()%i;}
map<string,int> Utils::getRandomPlayers(int n){

        map<string,int> names;
        int chips;
        string name;

        set<string> setNames=RandomNames(n);
        set<string> :: iterator itr;
        for(itr=setNames.begin();itr!=setNames.end();++itr){
            chips=rand()%200+100;
            name=*itr;
            names[name]=chips;
            cout<<name<<" : $"<<chips<<FYEL( " Join the game! ")<<endl;
        }

        return names;

}
set<string> Utils::RandomNames(int n){

    string name_file="../names.txt";
    vector<string> name_vec;
    set<string> names;

    ifstream infile;
    infile.open(name_file.c_str());
    if (!infile) {
        cerr << "c" <<  name_file << endl;
        exit(1);
    }
    for (string someName; infile >> someName; ) {
        name_vec.push_back(someName);
    }
    infile.close();

    //get until different name
    while(1){
        names.insert(name_vec.at(rand()%200+1));
        if(names.size()>=n-1){
            break;
        }
    }
    return names;
}

//let position to player
map<Player*,string> Utils::getRandomPosition(map<string,int> p) {
    map<Player*,string> players;
    Position position;
    map<string,int>::iterator it;
    map<Player*,string>::iterator itr;

    for (it=p.begin(); it!=p.end(); ++it) {
        Player* player=new Player;
        player->name=it->first;
        player->chips=it->second;
        players[player]=position.BB;
    }

    //set 23456 player position,
    // we can always choose our position when we player real game
    switch(p.size()){
        case 2:
        {
            //shuffle
            vector<string> l;
            l.push_back(position.BB);
            l.push_back(position.SB);
            random_shuffle(l.begin(),l.end(),myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it=l.begin(); it != l.end(); ++it)
                s.push(*it);

            for(itr=players.begin();itr!=players.end();++itr){
                itr->second=s.top();
                s.pop();
            }
            break;
        }
        case 3:
        {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            random_shuffle(l.begin(),l.end(),myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it=l.begin(); it != l.end(); ++it)
                    s.push(*it);

            for(itr=players.begin();itr!=players.end();++itr){
                itr->second=s.top();
                s.pop();
            }
            break;
        }
        case 4:
        {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            l.push_back(position.UTG);
            random_shuffle(l.begin(),l.end(),myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it=l.begin(); it != l.end(); ++it)
                s.push(*it);

            for(itr=players.begin();itr!=players.end();++itr){
                itr->second=s.top();
                s.pop();
            }
            break;
        }
        case 5:
        {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            l.push_back(position.UTG);
            l.push_back(position.CO);
            random_shuffle(l.begin(),l.end(),myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it=l.begin(); it != l.end(); ++it)
                s.push(*it);

            for(itr=players.begin();itr!=players.end();++itr){
                itr->second=s.top();
                s.pop();
            }
            break;
        }

        case 6:
        {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            l.push_back(position.UTG);
            l.push_back(position.CO);
            l.push_back(position.MP);
            random_shuffle(l.begin(),l.end(),myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it=l.begin(); it != l.end(); ++it)
                s.push(*it);

            for(itr=players.begin();itr!=players.end();++itr){
                itr->second=s.top();
                s.pop();
            }
            break;
        }
    }

    cout<<endl;
    cout<<"position is :"<<endl;
    for(itr=players.begin();itr!=players.end();++itr){
        cout<<itr->first->name<<"--->"<<itr->second<<endl;
        itr->first->position=itr->second;
    }
    cout<<endl;
return players;
}


map<string,Player*> Utils::processOrderByPreflop(map<Player*,string> players,DeckOfCards* deck,int blind){
    Position position;
    map<string,Player*> map;
    queue<Player> q;
    int mainPot;

    //sort to queue
    switch(players.size()){
        case 2:{
            for (auto it = players.begin(); it != players.end(); ++it)
                if (it->second == position.SB) {
                    it->first->card[0]=deck->dealCard();
                    it->first->card[1]=deck->dealCard();
                    it->first->chips=it->first->chips-blind;
                    cout<<it->first->name<<" blind: "<<blind<<endl;
                    cout<<it->first->name<<" chips: "<<it->first->chips<<endl;
                    map[it->first->position]=it->first;
                    q.push(*it->first);
                }
            for (auto it = players.begin(); it != players.end(); ++it)
                if (it->second == position.BB) {
                    it->first->card[0] = deck->dealCard();
                    it->first->card[1] = deck->dealCard();
                    it->first->chips=it->first->chips-blind*2;
                    cout<<it->first->name<<" big blind: "<<blind*2<<endl;
                    cout<<it->first->name<<" chips: "<<it->first->chips<<endl;
                    map[it->first->position]=it->first;
                    q.push(*it->first);
                }
            break;
        }
    }
    mainPot=blind*3;
    //if not empty keep call
    list<Player> maplist;
    int raise=0;
    while(q.size()>0){
        int o;
        cout<<q.front().name<<" please choose: "<<endl;
        cout<<"1:Call \n2:Fold  \n3:Raise  \n4:All in\n";
        cin>>o;
        switch(o){
            case 1:{
                if(raise==0){
                    q.front().chips= q.front().chips-blind;
                    mainPot+=blind;
                    maplist.push_back(q.front());
                    q.pop();
                }else{
                    q.front().chips= q.front().chips-raise;
                    mainPot+=raise;
                    maplist.push_back(q.front());
                    q.pop();
                }
                break;
            }
            case 2:{
                cout<< "this turn finish, shuffer and play again. " <<endl;
                break;
            }
            case 3:{
                cout<< " how much you raise"<<endl;
                cin>>raise;
                q.front().chips= q.front().chips-raise;
                mainPot+=raise;
                maplist.push_back(q.front());
                q.pop();
                q.push(maplist.front());
                break;
            }
            case 4:{
             break;
            }


        }
    }

    return map;
}



//calculate bets



