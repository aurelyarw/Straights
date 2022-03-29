#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"
#include "card.h"
#include <string>

class Human : public Player {

    public:
    //ctor
    Human(int id);

    //returns true if human
    virtual bool isHuman() override;

    //play and returns the card that it played
    virtual Card play(std::string cardStr) override;

    //discard card (i.e. remove card from hand and add to discard)
    virtual void pDiscard(std::string cardStr) override;

};


#endif
