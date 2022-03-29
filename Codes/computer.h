#ifndef COMPUTER_H
#define COMPUTER_H

#include "player.h"
#include "card.h"
#include <string>

class Computer : public Player {

    public:
    //ctor
    Computer(int id);

    //copy ctor
    Computer(Player &other);

    //returns false since computer
    virtual bool isHuman() override;

    //play and returns the card that it played
    virtual Card play(std::string cardStr) override;

    //discard card (i.e. remove card from hand and add to discard)
    virtual void pDiscard(std::string cardStr) override;

};


#endif
