//
// Created by william  on 12/8/19.
//

#ifndef TEXASHOLDEM_HASH_H
#define TEXASHOLDEM_HASH_H
#include<iostream>
#include <list>
using namespace std;
class Hash
{
    int BUCKET;    // No. of buckets

    // Pointer to an array containing buckets
    list<string> *table;
public:


    // hash function to map values to key
    unsigned int hashFunction(const std::string& str)
    {
        unsigned int b    = 378551;
        unsigned int a    = 63689;
        unsigned int hash = 0;
        for(std::size_t i = 0; i < str.length(); i++)
        {
            hash = hash * a + str[i];
            hash%=BUCKET;
            a    = a * b;
        }

        return hash;
    }

    Hash(int b)
{
    this->BUCKET = b;
    table = new list<string>[BUCKET];
}

void insertItem(string key)
{
    int index = hashFunction(key);
    table[index].push_back(key);
}

void deleteItem(string key)
{
    // get the hash index of key
    int index = hashFunction(key);

    // find the key in (inex)th list
    list <string> :: iterator i;
    for (i = table[index].begin();
         i != table[index].end(); i++) {
        if (*i == key)
            break;
    }

    // if key is found in hash table, remove it
    if (i != table[index].end())
        table[index].erase(i);
}

// function to display hash table
void displayHash() {
    for (int i = 0; i < BUCKET; i++) {
        cout << i;
        for (auto x : table[i])
            cout << " --> " << x;
        cout << endl;
    }
}

int search(string key) {
    int index = hashFunction(key);
    list<string>::iterator it;
    it=find(table[index].begin(),table[index].end(),key);
    if(it!=table[index].end())return 1;
    return -1;
}
};


#endif //TEXASHOLDEM_HASH_H
