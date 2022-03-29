#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <string>
#include <vector>

class Player {

    protected:
    int id;
    int totalScore;
    std::vector<Card> hand;
    std::vector<Card> discard;
    std::vector<Card> legalPlays;

    //ctor
    Player(int id);

    //copy ctor
    Player(Player &other);

    public:
    //dtor
    virtual ~Player() = default; /////////////////////////////////////////////////////////////////

    // get id
    int getId();

    //returns totalScore
    int getTotalScore();
    //print and add total score
    void printAddTotalScore();

    //returns true if Card c is in hand
    bool handCardFinder(Card c);
    //add card to hand
    void addHand(Card c);
    //remove card from hand
    void removeHand(Card c);
    //remove first card from hand and returns that card
    Card removeFirstHand();
    //print hand e.g. "Your hand: 4H 5D 2D JC 8H QH 2H 6C 9H 9D 9C 2C"
    void printHand();
    //returns true if there is a card in Hand
    bool thereIsHand();

    // add card to discard
    void addDiscard(Card c);
    //clear discard
    void clearDiscard();
    //print discard e.g. "PlayerX’s discards: 5C JD QH AD 3D KC"
    void printDiscard();
    //count the total value of in discard
    int countDiscard();

    //add in all the possible legalPlays
    void makeLegalPlays(std::vector<Card> & playable);
    //returns true if Card c is in legalPlays
    bool legalPlaysCardFinder(Card c);
    //clear legalPlays
    void clearLegalPlays();
    //print legalPlays e.g. "Legal plays: 7H 5S"
    void printLegalPlays();
    //returns true if there is a card in legalPlays
    bool thereIsLegalPlays();

    virtual bool isHuman() = 0;
    virtual Card play(std::string cardStr) = 0;
    virtual void pDiscard(std::string cardStr) = 0;

};

#endif



