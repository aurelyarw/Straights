#include "human.h"
#include <assert.h> 

//HELPER FUNCTION
void cardChecker(std::string cardStr) {
    if(cardStr.length() != 2){ 
        throw(4);
    }
    std::string r{"A23456789TJQK"};
    std::string s{"CDHS"};
    std::string rank{cardStr.substr(0,1)};
    std::string suit{cardStr.substr(1,1)};
    if((r.find(rank) == std::string::npos) || (s.find(suit) == std::string::npos)) {
        throw(4);
    }
}

//ctor
Human::Human(int id) :
    Player{id} {}

//returns true if human
bool Human::isHuman() {
    return true;
}

//play the inputted card, remove card from legalPlays & hand and
//returns the card
//Prints:
//e.g. "Player2 plays 7S."
//Requires:
//legalPlays should not be empty
Card Human::play(std::string cardStr) {
    assert(!legalPlays.empty());
    cardChecker(cardStr); //throws if no such card
    std::string rank{cardStr.substr(0,1)};
    std::string suit{cardStr.substr(1,1)};
    Card c{rank, suit};
    //if card is not a legalPlay, throw
    if(!legalPlaysCardFinder(c)) {
        throw(5);
    }
    removeHand(c);
    std::cout << "Player" << id << " plays " << c << "." << std::endl;
    return c;
}

//discard card (i.e. remove card from hand and add to discard)
//Prints:
//print: "Player<x> discards <card>."
//Requires:
//hand should not be empty
//legalPlays should be empty
void Human::pDiscard(std::string cardStr) {
    assert(!hand.empty());
    assert(legalPlays.empty());
    cardChecker(cardStr); //throws if no such card
    std::string rank{cardStr.substr(0,1)};
    std::string suit{cardStr.substr(1,1)};
    Card c{rank, suit};
    //if card is not in hand, throw
    if(!handCardFinder(c)) {
        throw(6);
    }
    removeHand(c);
    addDiscard(c);
    std::cout << "Player" << id << " discards " << c << "." << std::endl;
}
