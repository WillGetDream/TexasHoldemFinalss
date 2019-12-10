//
// Created by William   on 10/20/19.
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
#include <algorithm>
#include "DeckOfCards.h"
#define fold "fold"
#define active "active"
#define allin "allin"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int myrandom(int i) { return std::rand() % i; }

map<string, int> Utils::getRandomPlayers(int n) {

    map<string, int> names;
    int chips;
    string name;

    set<string> setNames = RandomNames(n);
    set<string>::iterator itr;
    for (itr = setNames.begin(); itr != setNames.end(); ++itr) {
        chips = rand() % 200 + 100;
        name = *itr;
        names[name] = chips;
        cout << name << " : $" << chips << FYEL(" Join the game! ") << endl;
    }

    return names;

}

set<string> Utils::RandomNames(int n) {

    string name_file = "../names.txt";
    vector<string> name_vec;
    set<string> names;

    ifstream infile;
    infile.open(name_file.c_str());
    if (!infile) {
        cerr << "c" << name_file << endl;
        exit(1);
    }
    for (string someName; infile >> someName;) {
        name_vec.push_back(someName);
    }
    infile.close();

    //get until different name
    while (1) {
        names.insert(name_vec.at(rand() % 200 + 1));
        if (names.size() >= n - 1) {
            break;
        }
    }
    return names;
}

//let position to player
map<Player *, string> Utils::getRandomPosition(map<string, int> p) {
    map<Player *, string> players;
    Position position;
    map<string, int>::iterator it;
    map<Player *, string>::iterator itr;

    for (it = p.begin(); it != p.end(); ++it) {
        Player *player = new Player;
        player->name = it->first;
        player->chips = it->second;
        players[player] = position.BB;
    }

    //set 23456 player position,
    // we can always choose our position when we player real game
    switch (p.size()) {
        case 2: {
            //shuffle
            vector<string> l;
            l.push_back(position.BB);
            l.push_back(position.SB);
            random_shuffle(l.begin(), l.end(), myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it = l.begin(); it != l.end(); ++it)
                s.push(*it);

            for (itr = players.begin(); itr != players.end(); ++itr) {
                itr->second = s.top();
                s.pop();
            }
            break;
        }
        case 3: {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            random_shuffle(l.begin(), l.end(), myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it = l.begin(); it != l.end(); ++it)
                s.push(*it);

            for (itr = players.begin(); itr != players.end(); ++itr) {
                itr->second = s.top();
                s.pop();
            }
            break;
        }
        case 4: {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            l.push_back(position.UTG);
            random_shuffle(l.begin(), l.end(), myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it = l.begin(); it != l.end(); ++it)
                s.push(*it);

            for (itr = players.begin(); itr != players.end(); ++itr) {
                itr->second = s.top();
                s.pop();
            }
            break;
        }
        case 5: {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            l.push_back(position.UTG);
            l.push_back(position.CO);
            random_shuffle(l.begin(), l.end(), myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it = l.begin(); it != l.end(); ++it)
                s.push(*it);

            for (itr = players.begin(); itr != players.end(); ++itr) {
                itr->second = s.top();
                s.pop();
            }
            break;
        }

        case 6: {
            //shuffle
            vector<string> l;
            l.push_back(position.BTN);
            l.push_back(position.BB);
            l.push_back(position.SB);
            l.push_back(position.UTG);
            l.push_back(position.CO);
            l.push_back(position.MP);
            random_shuffle(l.begin(), l.end(), myrandom);
            vector<string>::iterator it;
            stack<string> s;
            for (it = l.begin(); it != l.end(); ++it)
                s.push(*it);

            for (itr = players.begin(); itr != players.end(); ++itr) {
                itr->second = s.top();
                s.pop();
            }
            break;
        }
    }

    cout << endl;
    cout << "position is :" << endl;
    for (itr = players.begin(); itr != players.end(); ++itr) {
        cout << itr->first->name << "--->" << itr->second << endl;
        itr->first->position = itr->second;
    }
    cout << endl;
    return players;
}


Player Utils::processflop(map<Player *, string> players, DeckOfCards *deck, int blind,string playername) {
    Position position;
    map<string, Player *> map;
    queue<Player> q;
    vector<Player> vp;

    int mainPot;

    //sort to queue
    switch (players.size()) {
        case 2: {

            //sort for order by sb-bb to a vector,count main pot
            //find sb and bb
            for (auto it = players.begin(); it != players.end(); ++it) {
                if (it->second == position.SB) {
                    it->first->chipsOnTable = blind;
                    it->first->chips = it->first->chips - it->first->chipsOnTable;
                    cout << it->first->name << " blind: " << it->first->chipsOnTable << endl;
                    cout << it->first->name << " chips: " << it->first->chips << endl;
                    vp.push_back(*it->first);
                }
            }
            for (auto it = players.begin(); it != players.end(); ++it) {
                if (it->second == position.BB) {
                    it->first->chipsOnTable = blind * 2;
                    it->first->chips = it->first->chips - it->first->chipsOnTable;
                    cout << it->first->name << " blind: " << it->first->chipsOnTable << endl;
                    cout << it->first->name << " chips: " << it->first->chips << endl;
                    vp.push_back(*it->first);
                }
            }

            cout << endl;
            //deal card in order, everyone get two cards
            deck->shuffle();
            for (int i = 0; i < vp.size(); i++) {
                vp.at(i).card[0] = deck->dealCard();
                vp.at(i).card[1] = deck->dealCard();
                if (!playername.compare(vp.at(i).name)) {
                    cout << "you card is :" << endl << vp.at(i).card[0].print() << endl << vp.at(i).card[1].print()
                         << endl;
                }
            }
            //count mainpot
            mainPot = blind * 3;

            //define a value for turning to next step
            int flopflag = 0; // 1 go to next step

            //Pre-flop refers to the action that occurs before the flop is dealt

            /* put other player to queue
             * while(q!=0){
             *  player option,
             *      if call
             *          check if exist all in,and more than largest bet ,then you can call , if less, only can all in.
             *          check how much and count chips and mainpot,sidepot and show the info  go to next player in queue,if  queue=0 thus go to flop
             *      if player fold, go to next player in queue,if queue=0 thus BB game done, count mainpot and chips add to player, show info.
             *      if all in, push other player into queue, count the all in money for other player.
             *          if first all
             *              check if it is smallest,  if yes  go to mainpot. update status and sidepot,
             *              else if second all in(check the bet chips per person more than least), update mianpot and  sidepot
             *          if second all in go to side pot. least
             *          if other player not enough money, he still can all in, but has side pot.
             *      if check, go to next player
             *       if raise ,cout player base chips and raise chips,and mainpot
             *          pop out this player
             *            push other player to queue
             *        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ below code flow
             *  player option,
            *      if call
            *          check if exist all in,if chips more than largest of all in ,then you can call , if less, only can all in.
            *          check how much and count chips and mainpot,sidepot and show the info  go to next player in queue,if  queue=0 thus go to flop
            *             if raise

            *if player fold, go to next player in queue,if queue=0 thus BB game done, count mainpot and chips add to player, show info.
            *      if all in, push other player into queue, count the all in money for other player.
            *          if first all
            *              check if it is smallest,  if yes  go to mainpot. update status and sidepot,
            *              else if second all in(check the bet chips per person more than least), update mianpot and  sidepot
            *          if second all in go to side pot. least
            *          if other player not enough money, he still can all in, but has side pot.
            *      if check, go to next player
            *       if raise ,cout player base chips and raise chips,and mainpot
            *          pop out this player
            *            push other player to queue
            *
            */


            // put other player to queue
            for (int i = 0; i < vp.size(); i++) {
                q.push(vp.at(i));
            }

            //large bet
            int largeBet = blind * 2;
            vector<int> allInList;
            int largeAllIn = 0;
            vector<Player> tmp;
            vector<Player> allInTmp;
            vector<Player> tmpNext;

            //pro flop
            while (!q.empty()) {
                int o;
                cout << endl;
                cout << q.front().name << " please choose: " << endl;

                //check if you can call, if chips more than largest of all in ,then you can call , if less, only can all in.
                for (int i = 0; i < vp.size(); i++) {
                    if (vp.at(i).status == allin) {
                        allInList.push_back(vp.at(0).chipsOnTable);
                    }
                }
                if (allInList.size() > 0) {
                    sort(allInList.begin(), allInList.end());
                    largeAllIn = allInList.back();
                }

                // if player call has option, else choose call or all in only
                if (q.front().chips > largeAllIn && (q.front().chips + q.front().chipsOnTable) > largeBet) {

                    if (!q.front().name.compare(playername)) {
                        cout << "1:Call \n2:Fold  \n3:Raise  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 1;
                        cout << q.front().name << " choose : call" << endl;
                    }
                } else {
                    if (!q.front().name.compare(playername)) {
                        cout << "2:Fold  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 4;
                        cout << q.front().name << " choose ALL in" << endl;
                    }
                }


                switch (o) {
                    case 1: {
                        //call will let player not in the queue you can only call once
                        //bet=chips-largeBet
                        mainPot += largeBet - q.front().chipsOnTable; //add to mainpot
                        q.front().chips = q.front().chips - (largeBet - q.front().chipsOnTable); //remove chips
                        q.front().chipsOnTable = largeBet; // largeBet in the table

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        // pop from queue after action
                        q.pop();
                        break;
                    }
                    case 2: {
                        q.front().status = fold;
                        q.front().chipsOnTable = 0;
                        q.front().sidePot = 0;

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        Player rePy;
                        rePy=q.front();
                        q.pop();
                        //find the winner
                        for (int i = 0; i < tmp.size(); i++) {
                            if (tmp.at(i).name.compare(playername)) {
                                cout << tmp.at(i).name << " Win the game" << endl;
                            }
                        }
                        for (int i = 0; i < q.size(); i++) {
                            if (q.front().name.compare(playername)) {
                                cout << q.front().name << " Win the game" << endl;
                            }
                        }
                        cout << "game over! please restart the game!" << endl;
                        return rePy;
                        break;
                    }
                    case 3: {
                        int raiseData = 0;

                        cout << "how much you want to raise?" << endl;
                        cin >> raiseData;
                        if ((raiseData + q.front().chipsOnTable) < largeBet) {
                            cout << "you need raise more than " << (largeBet - q.front().chipsOnTable) << endl;
                            cout << "how much you want to raise?" << endl;
                            cin >> raiseData;
                        }
                        mainPot += raiseData;
                        q.front().chipsOnTable = q.front().chipsOnTable + raiseData;
                        q.front().chips = q.front().chips - raiseData;
                        largeBet = q.front().chipsOnTable;
                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;
                        // when raise other person need to go to queue

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        q.pop();
                        for (int i = 0; i < tmp.size(); i++) {
                            q.push(tmp.at(i));
                        }
                        break;
                    }
                    case 4: {
//                        cout<<"qsize-----"<<q.size();
//                        cout<<"qname"<<q.front().name<<q.front().status;
                        cout<<" pro loop before q compare---->"<<q.front().status<<endl;

                        if (!q.front().status.compare(allin)) {
                            q.pop();
                            break;
                        }

                        int smallAllin;
                        //side pot if all in > largebet,then other player in queue
                        if ((q.front().chipsOnTable + q.front().chips) > largeBet) {
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;
                            cout << "status----" << q.front().status;
                            largeBet = q.front().chipsOnTable + q.front().chips;
                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());
                            //not call at all
                            q.pop();
                            //push other to queue
                            for (int i = 0; i < tmp.size(); i++) {
                                cout<<"----tmp----->"<<tmp.at(i).name<<endl;

                                if (tmp.at(i).status.compare(allin)) {
                                    q.push(tmp.at(i));

                                }

                            }
                        } else {
                            //else all in < largebet

                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;


                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());

                            //updated status for tmp
                            for (int i = 0; i < tmp.size(); i++) {
                                if(q.front().name==tmp.at(i).name){
                                    tmp.at(i).status=allin;
                                }

                            }

                            //not call at all
                            q.pop();

                        }
                        break;
                    }

                }
            }

            cout << endl;
            cout << "flop show three cards on the table" << endl;
            //flop show three cards on the table
            Card cardTab[5];
            cardTab[0] = deck->dealCard();
            cardTab[1] = deck->dealCard();
            cardTab[2] = deck->dealCard();

            for (int i = 0; i < 3; i++) {
                cout << cardTab[i].print() << endl;
            }
            //process order sb-bb and put them to the queue
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp.at(i).position == position.SB) {
                    //cout<<"----tmp----middle-status-->"<<tmp.at(i).status<<endl;
                    if(tmp.at(i).status!=allin){
                        q.push(tmp.at(i));
                    }
                }
            }
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp.at(i).position == position.BB) {

                    if(tmp.at(i).status!=allin) {
                        q.push(tmp.at(i));
                    }
                }
            }
            tmp.clear();


            //Flop-round
            while (!q.empty()) {
                int o;
                cout << endl;
                cout << q.front().name << " please choose: " << endl;

                //check if you can call, if chips more than largest of all in ,then you can call , if less, only can all in.
                for (int i = 0; i < vp.size(); i++) {
                    if (vp.at(i).status == allin) {
                        allInList.push_back(vp.at(0).chipsOnTable);
                    }
                }
                if (allInList.size() > 0) {
                    sort(allInList.begin(), allInList.end());
                    largeAllIn = allInList.back();
                }

                // if player call has option, else choose call or all in only
                if (q.front().chips > largeAllIn && (q.front().chips + q.front().chipsOnTable) > largeBet) {

                    if (!q.front().name.compare(playername)) {
                        cout << "1:Call \n2:Fold  \n3:Raise  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 1;
                        cout << q.front().name << " choose : call" << endl;
                    }
                } else {
                    if (!q.front().name.compare(playername)) {
                        cout << "2:Fold  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 4;
                        cout << q.front().name << " choose ALL in" << endl;
                    }
                }


                switch (o) {
                    case 1: {
                        //call will let player not in the queue you can only call once
                        //bet=chips-largeBet
                        mainPot += largeBet - q.front().chipsOnTable; //add to mainpot
                        q.front().chips = q.front().chips - (largeBet - q.front().chipsOnTable); //remove chips
                        q.front().chipsOnTable = largeBet; // largeBet in the table

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        // pop from queue after action
                        q.pop();
                        break;
                    }
                    case 2: {
                        q.front().status = fold;
                        q.front().chipsOnTable = 0;
                        q.front().sidePot = 0;

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        Player rePy;
                        rePy=q.front();
                        q.pop();
                        //find the winner
                        for (int i = 0; i < tmp.size(); i++) {
                            if (tmp.at(i).name.compare(playername)) {
                                cout << tmp.at(i).name << " Win the game" << endl;
                            }
                        }
                        for (int i = 0; i < q.size(); i++) {
                            if (q.front().name.compare(playername)) {
                                cout << q.front().name << " Win the game" << endl;
                            }
                        }
                        cout << "game over! please restart the game!" << endl;
                        return rePy;
                        break;


                        break;
                    }
                    case 3: {
                        int raiseData = 0;

                        cout << "how much you want to raise?" << endl;
                        cin >> raiseData;
                        if ((raiseData + q.front().chipsOnTable) < largeBet) {
                            cout << "you need raise more than " << (largeBet - q.front().chipsOnTable) << endl;
                            cout << "how much you want to raise?" << endl;
                            cin >> raiseData;
                        }
                        mainPot += raiseData;
                        q.front().chipsOnTable = q.front().chipsOnTable + raiseData;
                        q.front().chips = q.front().chips - raiseData;
                        largeBet = q.front().chipsOnTable;
                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;
                        // when raise other person need to go to queue

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        q.pop();
                        for (int i = 0; i < tmp.size(); i++) {
                            q.push(tmp.at(i));
                        }
                        break;
                    }
                    case 4: {
//                        cout<<q.size();
//                        cout<<q.front().name<<q.front().status;
//                        cout<<"compare---->"<<q.front().status.compare(allin);
                        if (!q.front().status.compare(allin)) {
                            q.pop();
                            break;
                        }

                        int smallAllin;
                        //side pot if all in > largebet,then other player in queue
                        if ((q.front().chipsOnTable + q.front().chips) > largeBet) {
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;
                            //cout << "status----" << q.front().status;

                            largeBet = q.front().chipsOnTable + q.front().chips;
                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());
                            //not call at all
                            q.pop();
                            //push other to queue
                            for (int i = 0; i < tmp.size(); i++) {
                                if (tmp.at(i).status.compare(allin)) {
                                    q.push(tmp.at(i));
                                }
                            }
                        } else {
                            //else all in < largebet
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;


                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());

                            //updated status for tmp
                            for (int i = 0; i < tmp.size(); i++) {
                                if(q.front().name==tmp.at(i).name){
                                    tmp.at(i).status=allin;
                                }

                            }

                            //not call at all
                            q.pop();
                        }
                        break;
                    }

                }
            }

            /*
             *
             * ******* Turn ***************
             *
             *
             */

            cout << endl;
            cout << "Turn show fourth card on the table" << endl;
            //flop show three cards on the table
            cardTab[3] = deck->dealCard();


            cout << cardTab[3].print() << endl;

            //process order sb-bb and put them to the queue
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp.at(i).position == position.SB) {
                    if(tmp.at(i).status!=allin) {

                        q.push(tmp.at(i));
                    }
                }
            }
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp.at(i).position == position.BB) {
                    if(tmp.at(i).status!=allin) {

                        q.push(tmp.at(i));
                    }
                }
            }
            tmp.clear();

            /*
             *
             * ******* Turn-round ***************
             *
             *
             */

            while (!q.empty()) {
                int o;
                cout << endl;
                cout << q.front().name << " please choose: " << endl;

                //check if you can call, if chips more than largest of all in ,then you can call , if less, only can all in.
                for (int i = 0; i < vp.size(); i++) {
                    if (vp.at(i).status == allin) {
                        allInList.push_back(vp.at(0).chipsOnTable);
                    }
                }
                if (allInList.size() > 0) {
                    sort(allInList.begin(), allInList.end());
                    largeAllIn = allInList.back();
                }

                // if player call has option, else choose call or all in only
                if (q.front().chips > largeAllIn && (q.front().chips + q.front().chipsOnTable) > largeBet) {

                    if (!q.front().name.compare(playername)) {
                        cout << "1:Call \n2:Fold  \n3:Raise  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 1;
                        cout << q.front().name << " choose : call" << endl;
                    }
                } else {
                    if (!q.front().name.compare(playername)) {
                        cout << "2:Fold  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 4;
                        cout << q.front().name << " choose ALL in" << endl;
                    }
                }


                switch (o) {
                    case 1: {
                        //call will let player not in the queue you can only call once
                        //bet=chips-largeBet
                        mainPot += largeBet - q.front().chipsOnTable; //add to mainpot
                        q.front().chips = q.front().chips - (largeBet - q.front().chipsOnTable); //remove chips
                        q.front().chipsOnTable = largeBet; // largeBet in the table

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        // pop from queue after action
                        q.pop();
                        break;
                    }
                    case 2: {
                        q.front().status = fold;
                        q.front().chipsOnTable = 0;
                        q.front().sidePot = 0;

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        Player rePy;
                        rePy=q.front();
                        q.pop();
                        //find the winner
                        for (int i = 0; i < tmp.size(); i++) {
                            if (tmp.at(i).name.compare(playername)) {
                                cout << tmp.at(i).name << " Win the game" << endl;
                            }
                        }
                        for (int i = 0; i < q.size(); i++) {
                            if (q.front().name.compare(playername)) {
                                cout << q.front().name << " Win the game" << endl;
                            }
                        }
                        cout << "game over! please restart the game!" << endl;
                        return rePy;
                        break;


                        break;
                    }
                    case 3: {
                        int raiseData = 0;

                        cout << "how much you want to raise?" << endl;
                        cin >> raiseData;
                        if ((raiseData + q.front().chipsOnTable) < largeBet) {
                            cout << "you need raise more than " << (largeBet - q.front().chipsOnTable) << endl;
                            cout << "how much you want to raise?" << endl;
                            cin >> raiseData;
                        }
                        mainPot += raiseData;
                        q.front().chipsOnTable = q.front().chipsOnTable + raiseData;
                        q.front().chips = q.front().chips - raiseData;
                        largeBet = q.front().chipsOnTable;
                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;
                        // when raise other person need to go to queue

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        q.pop();
                        for (int i = 0; i < tmp.size(); i++) {
                            q.push(tmp.at(i));
                        }
                        break;
                    }
                    case 4: {

                        if (!q.front().status.compare(allin)) {
                            q.pop();
                            break;
                        }

                        int smallAllin;
                        //side pot if all in > largebet,then other player in queue
                        if ((q.front().chipsOnTable + q.front().chips) > largeBet) {
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;
                            largeBet = q.front().chipsOnTable + q.front().chips;
                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());
                            //not call at all
                            q.pop();
                            //push other to queue
                            for (int i = 0; i < tmp.size(); i++) {
                                if (tmp.at(i).status.compare(allin)) {
                                    q.push(tmp.at(i));
                                }
                            }
                        } else {
                            //else all in < largebet
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;


                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());

                            //updated status for tmp
                            for (int i = 0; i < tmp.size(); i++) {
                                if(q.front().name==tmp.at(i).name){
                                    tmp.at(i).status=allin;
                                }

                            }

                            //not call at all
                            q.pop();
                        }
                        break;
                    }

                }
            }



            /*
             *
             * ******* River ***************
             *
             *
             */

            cout << endl;
            cout << "Turn show fifth card on the table" << endl;
            //flop show three cards on the table
            cardTab[4] = deck->dealCard();

            cout << cardTab[4].print() << endl;

            //process order sb-bb and put them to the queue
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp.at(i).position == position.SB) {
                    if(tmp.at(i).status!=allin) {

                        q.push(tmp.at(i));
                    }
                }
            }
            for (int i = 0; i < tmp.size(); i++) {
                if (tmp.at(i).position == position.BB) {
                    if(tmp.at(i).status!=allin) {

                        q.push(tmp.at(i));
                    }
                }
            }
            tmp.clear();

            /*
             *
             * ******* River-round ***************
             *
             *
             */

            while (!q.empty()) {
                int o;
                cout << endl;
                cout << q.front().name << " please choose: " << endl;

                //check if you can call, if chips more than largest of all in ,then you can call , if less, only can all in.
                for (int i = 0; i < vp.size(); i++) {
                    if (vp.at(i).status == allin) {
                        allInList.push_back(vp.at(0).chipsOnTable);
                    }
                }
                if (allInList.size() > 0) {
                    sort(allInList.begin(), allInList.end());
                    largeAllIn = allInList.back();
                }

                // if player call has option, else choose call or all in only
                if (q.front().chips > largeAllIn && (q.front().chips + q.front().chipsOnTable) > largeBet) {

                    if (!q.front().name.compare(playername)) {
                        cout << "1:Call \n2:Fold  \n3:Raise  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 1;
                        cout << q.front().name << " choose : call" << endl;
                    }
                } else {
                    if (!q.front().name.compare(playername)) {
                        cout << "2:Fold  \n4:All in\n";
                        cin >> o;
                    } else {
                        o = 4;
                        cout << q.front().name << " choose ALL in" << endl;
                    }
                }


                switch (o) {
                    case 1: {
                        //call will let player not in the queue you can only call once
                        //bet=chips-largeBet
                        mainPot += largeBet - q.front().chipsOnTable; //add to mainpot
                        q.front().chips = q.front().chips - (largeBet - q.front().chipsOnTable); //remove chips
                        q.front().chipsOnTable = largeBet; // largeBet in the table

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        // pop from queue after action
                        q.pop();
                        break;
                    }
                    case 2: {
                        q.front().status = fold;
                        q.front().chipsOnTable = 0;
                        q.front().sidePot = 0;

                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        Player rePy;
                        rePy=q.front();
                        q.pop();
                        //find the winner
                        for (int i = 0; i < tmp.size(); i++) {
                            if (tmp.at(i).name.compare(playername)) {
                                cout << tmp.at(i).name << " Win the game" << endl;
                            }
                        }
                        for (int i = 0; i < q.size(); i++) {
                            if (q.front().name.compare(playername)) {
                                cout << q.front().name << " Win the game" << endl;
                            }
                        }
                        cout << "game over! please restart the game!" << endl;
                        return rePy;
                        break;


                        break;
                    }
                    case 3: {
                        int raiseData = 0;

                        cout << "how much you want to raise?" << endl;
                        cin >> raiseData;
                        if ((raiseData + q.front().chipsOnTable) < largeBet) {
                            cout << "you need raise more than " << (largeBet - q.front().chipsOnTable) << endl;
                            cout << "how much you want to raise?" << endl;
                            cin >> raiseData;
                        }
                        mainPot += raiseData;
                        q.front().chipsOnTable = q.front().chipsOnTable + raiseData;
                        q.front().chips = q.front().chips - raiseData;
                        largeBet = q.front().chipsOnTable;
                        //show info
                        cout << "mainPot: " << mainPot << endl;
                        cout << "chips: " << q.front().chips << endl;
                        cout << "chipsOnTable: " << q.front().chipsOnTable << endl;
                        // when raise other person need to go to queue

                        //add to tmp if exist not add ,tmp for next loop
                        int b = 0;
                        for (int i = 0; i < tmp.size(); i++) {
                            if (!q.front().name.compare(tmp.at(i).name)) {
                                b++;
                            }
                        }
                        if (b < 1) {
                            tmp.push_back(q.front());
                        }

                        q.pop();
                        for (int i = 0; i < tmp.size(); i++) {
                            q.push(tmp.at(i));
                        }
                        break;
                    }
                    case 4: {

                        if (!q.front().status.compare(allin)) {
                            q.pop();
                            break;
                        }

                        int smallAllin;
                        //side pot if all in > largebet,then other player in queue
                        if ((q.front().chipsOnTable + q.front().chips) > largeBet) {
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;
                            largeBet = q.front().chipsOnTable + q.front().chips;
                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());
                            //not call at all
                            q.pop();
                            //push other to queue
                            for (int i = 0; i < tmp.size(); i++) {
                                if (tmp.at(i).status.compare(allin)) {
                                    q.push(tmp.at(i));
                                }
                            }
                        } else {
                            //else all in < largebet
                            mainPot += q.front().chips;
                            q.front().chipsOnTable = q.front().chipsOnTable + q.front().chips;
                            q.front().chips = 0;
                            q.front().status = allin;


                            // show info
                            cout << "mainPot: " << mainPot << endl;
                            cout << "chips: " << q.front().chips << endl;
                            cout << "chipsOnTable: " << q.front().chipsOnTable << endl;

                            //push to all in vector
                            allInTmp.push_back(q.front());

                            //updated status for tmp
                            for (int i = 0; i < tmp.size(); i++) {
                                if(q.front().name==tmp.at(i).name){
                                    tmp.at(i).status=allin;
                                }

                            }

                            //not call at all
                            q.pop();
                        }
                        break;
                    }

                }
            }

            cout << endl;
            cout << "Show Player card on the table" << endl;
            cout << endl;

            if (allInTmp.size() > 0) {
                for (int i = 0; i < allInTmp.size(); i++) {
                    tmp.push_back(allInTmp.at(i));
                }
            }

            for (int i = 0; i < tmp.size(); i++) {
                cout << endl;
                cout << "Player:" << tmp.at(i).name << endl;
                cout << tmp.at(i).card[0].print() << endl;
                cout << tmp.at(i).card[1].print() << endl;
                cout << endl;
            }

            cout << endl;
            cout << "Show five Cards on the table" << endl;
            cout << endl;

            for (int i = 0; i < 5; i++) {
                cout << cardTab[i].print() << endl;

            }
            cout << endl;
            Player winner;
            winner = calculateWins(tmp, cardTab, 5);
            if (winner.name.empty()) {
                cout << "no one winner!" << endl;
            }
            cout << "winner is:  " << winner.name << endl;

            Player win, loser;
            for (int i = 0; i < tmp.size(); i++) {
                if (!winner.name.compare(tmp.at(i).name)) {
                    if (tmp.at(i).chipsOnTable < (mainPot / 2)) {
                        tmp.at(i).chips = tmp.at(i).chipsOnTable * 2;
                    } else {
                        tmp.at(i).chips = tmp.at(i).chips + mainPot;
                    }
                    cout << "winner " << tmp.at(i).name << " chips is :" << tmp.at(i).chips << endl;
                    win.name = tmp.at(i).name;
                    win.chips = tmp.at(i).chips;

                }
                //loser
                if (winner.name.compare(tmp.at(i).name)) {
                    tmp.at(i).chips = tmp.at(i).chips;
                    //cout<<"loser "<<tmp.at(i).name<<" chips is :"<<tmp.at(i).chips<<endl;
                    loser.name = tmp.at(i).name;
                    loser.chips = tmp.at(i).chips;
                }
            }

            if ((winner.name.compare(playername)) == 0) {
                string chall;
                cout
                        << FBLU("Congratulation! You earn maze challenge. Earn 100 dollar when you win. Lose 1 dollar when you lost. Would you like to challenge?(Y or N) ")
                        << endl;
                cin >> chall;
                while (chall.compare("Y") != 0 && chall.compare("N") != 0) {
                    cout
                            << FBLU("You enter wrong. Please enter Y or N! Congratulation! You earn maze challenge. Double coins when you win. Half coins when you lost. Would you like to challenge?(Y or N) ")
                            << endl;
                    cin >> chall;
                }
                if (chall == "Y") {

                    int m = 9, n = 9;
                    int a[10][10];
                    vector<vector<int>> ms;
                    Maze maze;
                    ms = maze.generateMaze();

                    for (int i = 0; i < m; i++) {
                        // printf("%d:\t",i);
                        for (int j = 0; j < n; j++) {
                            a[i][j] = ms.at(i).at(j);
                            //printf("%d ", a[i][j]);
                        }
                        // printf("\n");
                    }
                    a[4][4] = rand() % 2;
                    a[4][5] = rand() % 2;
                    for (int i = 0; i < m; i++) {
                        printf("%d:\t", i);
                        for (int j = 0; j < n; j++) {
                            printf("%d  ", a[i][j]);
                        }
                        printf("\n");
                    }


                    vector<pii> res;
                    vector<vector<int>> visited(m, vector<int>(n, false));
                    vector<vector<pii>> ret;
                    int min_t = 101;
                    //random set last one
                    maze.dfs(min_t, a, m, n, 0, 0, res, visited, ret);
                    cout << FBLU("Challenge Question: Is there a path way from (0,0) to (8,8)? (Y or N)");
                    string flag;
                    cin >> flag;
                    if ((ret.size() > 0 && flag == "Y") || (ret.size() <= 0 && flag == "N")) {
                        cout << "you won 100 dollar!";
                        win.chips += 100;
                        cout << "winner " << win.name << " chips is :" << win.chips << endl;
                    } else {
                        cout << "you lost 1 dollar";
                        cout << win.name << " chips is :" << win.chips << endl;

                    }
                    if (ret.size() > 0) {
                        cout << "There is a path!" << endl;
                        for (int i = 0; i < ret.size(); i++) {
                            if (min_t == ret[i].size()) {
                                for (int k = 0; k < min_t; k++) {
                                    cout << '(' << ret[i][k].first << ',' << ret[i][k].second << ')' << endl;
                                }
                            }
                        }
                    }
                    return win;
                } else {
                    return win;
                }
            } else {
                return loser;
            }




//Flop-round
//SB can raise and call, Fold, all in.
// if call will go to Turn.
// if SB raise
            // if BB call, will go to Turn.
            // if BB raise
            // if SB call, will go to Turn.
            // if SB raise
//if SB fold, BB game done, count mainpot and chips add to BB.
//if SB all in
            // if BB call, game done, count mainpot and chips.
            // if BB fold, game done, count mainpot and chips.


//Turn show card four on the table
//turn-round
//SB can raise and call, Fold, all in.
// if call will go to river.
// if SB raise
            // if BB call, will go to river.
            // if BB raise
            // if SB call, will go to river.
            // if SB raise
//if SB fold, BB game done, count mainpot and chips add to BB.
//if SB all in
            // if BB call, game done, count mainpot and chips.
            // if BB fold, game done, count mainpot and chips.

//river show card five on the table
//River-round
//SB can raise and call, Fold, all in.
// if call will game done, count mainpot and chips.
// if SB raise
            // if BB call, will game done, count mainpot and chips.
            // if BB raise
            // if SB call, will game done, count mainpot and chips.
            // if SB raise
//if SB fold, BB game done, count mainpot and chips add to BB.
//if SB all in
            // if BB call, game done, count mainpot and chips.
            // if BB fold, game done, count mainpot and chips.

        }//end while pre-flop
    }
}


/* ---------------------------------------------------
Sort the cards in the Poker hand by the suit;

if ( lowest suit == highest suit )
Hand contain a flush (only 1 suit of cards in thehand !);
else
Hand does not contain a flush;
    --------------------------------------------------- */
bool Utils::isFlush( Card h[],int size ){
   if ( size != 5 )
       return(false);
   sortBySuit(h,size);
   return( h[0].getSuit() == h[4].getSuit() );

}

void Utils::sortBySuit( Card h[],int size ){
   int i, j, min_j;

   /* ---------------------------------------------------
      The selection sort algorithm
      --------------------------------------------------- */
    for ( i = 0 ; i < size ; i ++ )
    {
        /* ---------------------------------------------------
           Find array element with min. value among
           h[i], h[i+1], ..., h[n-1]
           --------------------------------------------------- */
        min_j = i;   // Assume elem i (h[i]) is the minimum

        for ( j = i+1 ; j < size ; j++ )
        {
            if ( h[j].getSuit()< h[min_j].getSuit() )
            {
                min_j = j;
            }
        }

        /* ---------------------------------------------------
           Swap a[i] and a[min_j]
           --------------------------------------------------- */
        Card tmp = h[i];
        h[i] = h[min_j];
        h[min_j] = tmp;
    }
}


/* ---------------------------------------------------
Sort the cards in the Poker hand by the rank;

   if ( highest rank card == ACE )
      Check if other 4 cards are
            K, Q, J, 10
        or  2, 3, 4, 5
   else
      Check if 5 cards are continuous in rank
    --------------------------------------------------- */

bool Utils::isStraight( Card h[] ,int size)
{
    int i, testRank;

    if ( size != 5 )
        return(false);

    sortByFace(h,size);      // Sort the poker hand by the rank of each card, small to large

    /* ===========================
       Check if hand has an Ace
       =========================== */
    if ( h[4].getFace() == 14 )
    {
        /* =================================
           Check straight using an Ace
           ================================= */
        bool a = h[0].getFace() == 2 && h[1].getFace() == 3 &&
                    h[2].getFace() == 4 && h[3].getFace() == 5 ;
        bool b = h[0].getFace() == 10 && h[1].getFace() == 11 &&
                    h[2].getFace() == 12 && h[3].getFace()== 13 ;

        return ( a || b );
    }
    else
    {
        /* ===========================================
           General case: check for increasing values
           =========================================== */
        testRank = h[0].getFace() + 1;

        for ( i = 1; i < 5; i++ )
        {
            if ( h[i].getFace() != testRank )
                return(false);        // Straight failed...

            testRank++;   // Next card in hand
        }

        return(true);        // Straight found !
    }
}

void Utils::sortByFace( Card h[],int size )
{
    int i, j, min_j;

    /* ---------------------------------------------------
       The selection sort algorithm
       --------------------------------------------------- */
    for ( i = 0 ; i < size ; i ++ )
    {
        /* ---------------------------------------------------
           Find array element with min. value among
           h[i], h[i+1], ..., h[n-1]
           --------------------------------------------------- */
        min_j = i;   // Assume elem i (h[i]) is the minimum

        for ( j = i+1 ; j < size ; j++ )
        {
            if ( h[j].getFace() < h[min_j].getFace() )
            {
                min_j = j;    // We found a smaller rank value, update min_j
            }
        }

        /* ---------------------------------------------------
           Swap a[i] and a[min_j]
           --------------------------------------------------- */
        Card tmp = h[i];
        h[i] = h[min_j];
        h[min_j] = tmp;
    }
}

bool Utils::isStraightFlush(Card h[],int size)
{
    return isStraight(h,size) && isFlush( h,size );

};

bool Utils::isRoyalFlush(Card h[],int size)
{

    return isStraight(h,size) && isFlush( h,size )&&h[size-1].getFace()==14;

};

bool Utils::is4s( Card h[],int size )
{
    bool a1, a2;

    if ( size != 5 )
        return(false);

    sortByFace(h,size);         // Sort by rank first

    /* ------------------------------------------------------
       Check for: 4 cards of the same rank
              + higher ranked unmatched card
   ------------------------------------------------------- */
    a1 = h[0].getFace() == h[1].getFace() &&
         h[1].getFace()== h[2].getFace() &&
         h[2].getFace()== h[3].getFace();


    /* ------------------------------------------------------
       Check for: lower ranked unmatched card
              + 4 cards of the same rank
   ------------------------------------------------------- */
    a2 = h[1].getFace()== h[2].getFace() &&
         h[2].getFace() == h[3].getFace()&&
         h[3].getFace()== h[4].getFace();

    return ( a1 || a2 );
}

bool Utils::isFullHouse( Card h[],int size)
{
    bool a1, a2;

    if ( size != 5 )
        return(false);

    sortByFace(h,size);      // Sort by rank first

    /* ------------------------------------------------------
       Check for: x x x y y
   ------------------------------------------------------- */
    a1 = h[0].getFace() == h[1].getFace()&&
         h[1].getFace() == h[2].getFace() &&
         h[3].getFace()== h[4].getFace();

    /* ------------------------------------------------------
       Check for: x x y y y
   ------------------------------------------------------- */
    a2 = h[0].getFace() == h[1].getFace()&&
         h[2].getFace()== h[3].getFace()&&
         h[3].getFace() == h[4].getFace();

    return( a1 || a2 );
}


bool Utils::is3s( Card h[],int size )
{
    bool a1, a2, a3;

    if ( size != 5 )
        return(false);

    sortByFace(h,size);         // Sort by rank first

    /* ------------------------------------------------------
       Check for: x x x a b
   ------------------------------------------------------- */
    a1 = h[0].getFace() == h[1].getFace() &&
         h[1].getFace() == h[2].getFace() &&
         h[3].getFace()!= h[0].getFace() &&
         h[4].getFace() != h[0].getFace() &&
         h[3].getFace() != h[4].getFace() ;

    /* ------------------------------------------------------
       Check for: a x x x b
   ------------------------------------------------------- */
    a2 = h[1].getFace() == h[2].getFace()&&
         h[2].getFace()== h[3].getFace() &&
         h[0].getFace()!= h[1].getFace() &&
         h[4].getFace()!= h[1].getFace() &&
         h[0].getFace() != h[4].getFace();

    /* ------------------------------------------------------
       Check for: a b x x x
   ------------------------------------------------------- */
    a3 = h[2].getFace()== h[3].getFace()&&
         h[3].getFace() == h[4].getFace() &&
         h[0].getFace() != h[2].getFace()&&
         h[1].getFace() != h[2].getFace()&&
         h[0].getFace()!= h[1].getFace() ;

    return( a1 || a2 || a3 );

}

bool Utils::is22s( Card h[],int size )
{
    bool a1, a2, a3;

    if ( size != 5 )
        return(false);

    if ( is4s(h,size) || isFullHouse(h,size) || is3s(h,size) )
        return(false);        // The hand is not 2 pairs (but better)

    sortByFace(h,size);

    /* --------------------------------
       Checking: a a  b b x
   -------------------------------- */
    a1 = h[0].getFace() == h[1].getFace()  &&
         h[2].getFace()  == h[3].getFace()  ;

    /* ------------------------------
       Checking: a a x  b b
   ------------------------------ */
    a2 = h[0].getFace() == h[1].getFace()&&
         h[3].getFace() == h[4].getFace();

    /* ------------------------------
       Checking: x a a  b b
   ------------------------------ */
    a3 = h[1].getFace() == h[2].getFace()&&
         h[3].getFace() == h[4].getFace();

    return( a1 || a2 || a3 );
}


bool Utils::is2s( Card h[],int size )
{
    bool a1, a2, a3, a4;

    if ( size != 5 )
        return(false);

    if ( is4s(h,size) || isFullHouse(h,size) || is3s(h,size) || is22s(h,size) )
        return(false);        // The hand is not one pair (but better)

    sortByFace(h,size);

    /* --------------------------------
       Checking: a a x y z
   -------------------------------- */
    a1 = h[0].getFace()== h[1].getFace();

    /* --------------------------------
       Checking: x a a y z
   -------------------------------- */
    a2 = h[1].getFace()== h[2].getFace();

    /* --------------------------------
       Checking: x y a a z
   -------------------------------- */
    a3 = h[2].getFace()== h[3].getFace();

    /* --------------------------------
       Checking: x y z a a
   -------------------------------- */
    a4 = h[3].getFace()== h[4].getFace();

    return( a1 || a2 || a3 || a4 );
}


int Utils::valueHand( Card h[],int size )
{
    if ( isFlush(h,size) && isStraight(h,size) )
        return valueStraightFlush(h,size);
    else if ( is4s(h,size) )
        return valueFourOfAKind(h,size);
    else if ( isFullHouse(h,size) )
        return valueFullHouse(h,size);
    else if ( isFlush(h,size) )
        return valueFlush(h,size);
    else if ( isStraight(h,size) )
        return valueStraight(h,size);
    else if ( is3s(h,size) )
        return valueSet(h,size);
    else if ( is22s(h,size) )
        return valueTwoPairs(h,size);
    else if ( is2s(h,size) )
        return valueOnePair(h,size);
    else
        return valueHighCard(h,size);
}

/* -----------------------------------------------------
      valueFlush(): return value of a Flush hand

            value = FLUSH + valueHighCard()
      ----------------------------------------------------- */
int Utils::valueStraightFlush( Card h[],int size )
{
   // cout<<" StraightFlush "<<endl;
    return STRAIGHT_FLUSH + valueHighCard(h,size);
}

/* -----------------------------------------------------
   valueFlush(): return value of a Flush hand

         value = FLUSH + valueHighCard()
   ----------------------------------------------------- */
int Utils::valueFlush( Card h[] ,int size )
{
    //cout<<" valueFlush "<<endl;
    return FLUSH + valueHighCard(h,size);
}

/* -----------------------------------------------------
   valueStraight(): return value of a Straight hand

         value = STRAIGHT + valueHighCard()
   ----------------------------------------------------- */
int Utils::valueStraight( Card h[] ,int size )
{
   // cout<<" valueStraight "<<endl;

    return STRAIGHT + valueHighCard(h,size);
}

/* ---------------------------------------------------------
   valueFourOfAKind(): return value of a 4 of a kind hand

         value = FOUR_OF_A_KIND + 4sCardRank

   Trick: card h[2] is always a card that is part of
          the 4-of-a-kind hand
      There is ONLY ONE hand with a quads of a given rank.
   --------------------------------------------------------- */
int Utils::valueFourOfAKind( Card h[] ,int size )
{

    sortByFace(h,size);

   // cout<<" valueFourOfAKind "<<endl;

    return FOUR_OF_A_KIND + h[2].getFace();
}

/* -----------------------------------------------------------
   valueFullHouse(): return value of a Full House hand

         value = FULL_HOUSE + SetCardRank

   Trick: card h[2] is always a card that is part of
          the 3-of-a-kind in the full house hand
      There is ONLY ONE hand with a FH of a given set.
   ----------------------------------------------------------- */
int Utils::valueFullHouse( Card h[] ,int size )
{
    sortByFace(h,size);
   // cout<<" valueFullHouse "<<endl;

    return FULL_HOUSE + h[2].getFace();
}

/* ---------------------------------------------------------------
   valueSet(): return value of a Set hand

         value = SET + SetCardRank

   Trick: card h[2] is always a card that is part of the set hand
      There is ONLY ONE hand with a set of a given rank.
   --------------------------------------------------------------- */
int Utils::valueSet( Card h[] ,int size )
{
    sortByFace(h,size);
  //  cout<<" valueSet "<<endl;

    return SET + h[2].getFace();
}

/* -----------------------------------------------------
   valueTwoPairs(): return value of a Two-Pairs hand

         value = TWO_PAIRS
                + 14*14*HighPairCard
                + 14*LowPairCard
                + UnmatchedCard
   ----------------------------------------------------- */
int Utils::valueTwoPairs( Card h[] ,int size )
{
    int val = 0;

    sortByFace(h,size);

    if ( h[0].getFace() == h[1].getFace() &&
         h[2].getFace() == h[3].getFace() )
        val = 14*14*h[2].getFace() + 14*h[0].getFace() + h[4].getFace();
    else if ( h[0].getFace() == h[1].getFace() &&
              h[3].getFace() == h[4].getFace() )
        val = 14*14*h[3].getFace() + 14*h[0].getFace() + h[2].getFace();
    else
        val = 14*14*h[3].getFace() + 14*h[1].getFace() + h[0].getFace();

   // cout<<" valueTwoPairs "<<endl;

    return TWO_PAIRS + val;
}

/* -----------------------------------------------------
   valueOnePair(): return value of a One-Pair hand

         value = ONE_PAIR
                + 14^3*PairCard
                + 14^2*HighestCard
                + 14*MiddleCard
                + LowestCard
   ----------------------------------------------------- */
int Utils::valueOnePair( Card h[] ,int size )
{
    int val = 0;

    sortByFace(h,size);

    if ( h[0].getFace() == h[1].getFace() )
        val = 14*14*14*h[0].getFace() +
              + h[2].getFace() + 14*h[3].getFace() + 14*14*h[4].getFace();
    else if ( h[1].getFace() == h[2].getFace() )
        val = 14*14*14*h[1].getFace() +
              + h[0].getFace() + 14*h[3].getFace() + 14*14*h[4].getFace();
    else if ( h[2].getFace() == h[3].getFace() )
        val = 14*14*14*h[2].getFace() +
              + h[0].getFace() + 14*h[1].getFace() + 14*14*h[4].getFace();
    else
        val = 14*14*14*h[3].getFace() +
              + h[0].getFace() + 14*h[1].getFace() + 14*14*h[2].getFace();

    //cout<<" ONE_PAIR "<<endl;

    return ONE_PAIR + val;
}

/* -----------------------------------------------------
   valueHighCard(): return value of a high card hand

         value =  14^4*highestCard
                + 14^3*2ndHighestCard
                + 14^2*3rdHighestCard
                + 14^1*4thHighestCard
                + LowestCard
   ----------------------------------------------------- */
int Utils::valueHighCard( Card h[] ,int size )
{
    int val;

    sortByFace(h,size);

    val = h[0].getFace() + 14* h[1].getFace() + 14*14* h[2].getFace()
          + 14*14*14* h[3].getFace() + 14*14*14*14* h[4].getFace();

   // cout<<" valueHighCard "<<endl;

    return val;
}
// dfs(0, 0, n=7, k=5,cards[7] , visited);
//recursions
void Utils::dfs(int pos, int cnt, int n, int k, Card a[],bool visited[]) {

    if (cnt == k) {
        vector<Card> v;

        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                cout << a[i].print() << ' ';
                v.push_back(a[i]);
            }
        }
        cout << endl;
        vv.push_back(v);
        return;
    }

    if (pos == n) return;

    if (!visited[pos]) {
        visited[pos] = true;
        dfs(pos + 1, cnt + 1, n, k, a,visited);
        visited[pos] = false;
    }
    dfs(pos + 1, cnt, n, k, a, visited);
}


Player Utils::calculateWins(vector<Player> p,Card* cardtab,int size){

    int p1,p2;
    for(int i=0;i<2;i++){
        cout<<endl;
        Card cards[7];
        //5，6 index belong to people, 0-4 belong to table
        cards[5]=p.at(i).card[0];
        cards[6]=p.at(i).card[1];

        for(int i=0;i<5;i++){
            cards[i]=cardtab[i];
        }
        for(int i=0;i<7;i++){
            cout<<cards[i].print()<<endl;
        }
        int n=7;
        int k=5;

        Card a[n];
        vector<int> values;

        bool *visited = new bool[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = cards[i];
            visited[i] = false;
        }
        cout<<endl;
        cout<<"player "<<p.at(i).name<<endl;
        cout<<"combination 5 of 7 cards: "<<endl;
        //save combination to vector vv
        dfs(0, 0, n, k,a , visited);

        //deckswith values
        map<Card*,int> decksnValues;
        //get combination
        Hash hash(15);
        for(int i=0;i<vv.size();i++){
            Card cardsary[5];
            for(int j=0;j<5;j++){
                cardsary[j]=vv.at(i).at(j);
                cout<<cardsary[j].print()<<"---->";
            }

            int s=valueHand(cardsary,5);
            hash.insertItem(to_string(s));
            decksnValues.insert(make_pair(cardsary,s));
            cout<<"-->index "<<i<<"--->"<<s<<endl;
            values.push_back(s);
        }
        cout<<"Hashing values of hand"<<endl;
        hash.displayHash();
        //recursive sorts
        cout<<"merge Sorting values in hand......"<<endl;
        vector<int> vars= mergeSort(values);
        if(vars.size()>0){
            cout<<endl;
            cout<<"best value of hands: "<<vars.back()<<endl;
            p.at(i).valueInHand=vars.back();
        }
        vars.clear();
        vv.clear();
        delete[] visited;
    }
    if(p.at(0).valueInHand>p.at(1).valueInHand){
        return p.at(0);
    }else if(p.at(0).valueInHand<p.at(1).valueInHand){
        return p.at(1);
    }else{
        Player p;
        return p;
    }

}

// merge function
vector<int> Utils::merge(vector<int> left,vector<int> right){
    int leftCount = 0;
    int rightCount = 0;

    vector<int> results;

    bool useLeft;
    for (int i=0; i<left.size()+right.size();i++){
        if(leftCount<left.size()){
            if(rightCount<right.size()){
                useLeft = (left[leftCount] < right[rightCount]);
            }
            else{
                useLeft = true;
            }
        }
        else{
            useLeft = false;
        }

        if (useLeft){
            results.push_back(left[leftCount]);
            if (leftCount < left.size()){
                leftCount++;
            }
        }
        else{
            results.push_back(right[rightCount]);
            if (rightCount<right.size()){
                rightCount++;
            }
        }
    }
    return results;
}

// merge sort function
vector<int> Utils::mergeSort(vector<int> arr){
    if (arr.size() <= 1){
        return arr;
    }
    int len = floor(arr.size()/2);
    vector<int> left(arr.begin(), arr.begin()+len);
    vector<int> right(arr.begin()+len, arr.end());

    return merge(mergeSort(left),mergeSort(right));
}
