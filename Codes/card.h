#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

class Card {
    std::string rank;
    std::string suit;

    public:
    //ctor
    Card(std::string r, std::string s);

    //returns the rank of the card
    std::string getRank();

    //returns the suit of the card
    std::string getSuit();

    //returns the value of the card
    int value();

    bool operator==(const Card &other) const;

    friend std::ostream & operator<<( std::ostream & out, const Card & c );
};

#endif
