#include "computer.h"
#include <iostream>
#include <assert.h> 

//ctor
Computer::Computer(int id) :
    Player{id} {}

//copy ctor
Computer::Computer(Player &other) :
    Player{other} {};


//returns false since computer
bool Computer::isHuman() {
    return false;
}

//play the first legalPlays, remove from hand and
//returns the card that it played
//Prints:
//Player2 plays 7S.
//Requires:
//legalPlays should not be empty
//cardStr should be ""
Card Computer::play(std::string cardStr) {
    assert(!legalPlays.empty());
    assert(cardStr == "");
    Card c {legalPlays[0]};
    removeHand(c);
    std::cout << "Player" << id << " plays " << c << "." << std::endl;
    // std::cout << "******************************************************************" << std::endl; //
    return c;
}

//discard card (i.e. remove first card from hand and add to discard)
//Prints:
//print: "Player<x> discards <card>."
//Requires:
//hand should not be empty
//legalPlays should be empty
//cardStr should be ""
void Computer::pDiscard(std::string cardStr) {
    assert(!hand.empty());
    assert(legalPlays.empty());
    assert(cardStr == "");
    Card c {removeFirstHand()};
    addDiscard(c);
    std::cout << "Player" << id << " discards " << c << "." << std::endl;
    //std::cout << "******************************************************************" << std::endl;
}
