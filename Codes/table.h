#ifndef TABLE_H
#define TABLE_H

#include "card.h"
#include <deque>
#include <string>

class Table {

    std::deque<std::string> club;
    std::deque<std::string> diamond;
    std::deque<std::string> heart;
    std::deque<std::string> spade;

    public:
    //ctor
    Table();

    //clear all the deques in the table
    void clear();

    //add card to one of the deques
    void addToTable(Card c);

    //print the table
    void printTable();

};

#endif
