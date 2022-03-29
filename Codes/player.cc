#include "player.h"
#include <algorithm>
#include <assert.h> 

//ctor
Player::Player(int id) :
    id{id},
    totalScore{0},
    hand{},
    discard{},
    legalPlays{} {}

//copy ctor
Player::Player(Player &other) {
    id = other.id;
    totalScore = other.totalScore;
    hand = other.hand;
    discard = other.discard;
    legalPlays = other.legalPlays;
}

//get id
int Player::getId() {
    return id;
}

//returns totalScore
int Player::getTotalScore(){
    return totalScore;
}
//print and add total score
//print:
//Player<x>’s score: <old score> + <score gained> = <new score>
void Player::printAddTotalScore() {
    int scoreGained{countDiscard()};
    std::cout << "Player" << id << "\'s score: " << totalScore << " + " << scoreGained << " = ";
    totalScore = totalScore + scoreGained;
    std::cout << totalScore << std::endl;
}

//returns true if Card c is in hand
bool Player::handCardFinder(Card c) {
    std::vector<Card>::iterator it;
    it = find(hand.begin(), hand.end(), c);
    if (it != hand.end()) {
        return true;
    } else {
        return false;
    }
}
//add card to hand
void Player::addHand(Card c) {
    hand.push_back(c);
} 
//removes card from hand
//must be sure that card is there
void Player::removeHand(Card c) {
    std::vector<Card>::iterator it;
    it = find(hand.begin(), hand.end(), c);
    if (it != hand.end()) { //if found do smth, else do nothing
        hand.erase(it);
    } 
}
//remove first card from hand
//Requires:
//hand should not be empty
Card Player::removeFirstHand() {
    assert(!hand.empty());
    Card c {hand[0]};
    hand.erase( hand.begin() );
    return c;
}
//print hand e.g. "Your hand: 4H 5D 2D JC 8H QH 2H 6C 9H 9D 9C 2C"
void Player::printHand() {
    std::cout << "Your hand:";
    for(auto it = hand.begin(); it != hand.end(); it++) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}
bool Player::thereIsHand() {
    int num {0};
    num = static_cast<int>(hand.size());

    if(num != 0) {
        return true;
    } else {
        return false;
    }
}

// add card to discard
void Player::addDiscard(Card c){ 
    discard.push_back(c);
}
//clear discard
void Player::clearDiscard() {
    discard.clear();
}
//print discard e.g. "PlayerX’s discards: 5C JD QH AD 3D KC"
void Player::printDiscard() {
    std::cout << "Player" << id << "\'s discards:";
    for(auto it = discard.begin(); it != discard.end(); it++) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}
//count the total value of in discard
int Player::countDiscard(){
    int totalValue = 0;
    for(auto it = discard.begin(); it != discard.end(); it++) {
        totalValue = totalValue + it->value();
    }
    return totalValue;
}

//add in all the possible legalPlays
void Player::makeLegalPlays(std::vector<Card> & playable) {
    for(auto it = hand.begin(); it!= hand.end(); it++) {
        std::vector<Card>::iterator it2;
        it2 = find(playable.begin(), playable.end(), *it);
        if (it2 != playable.end()) {
            legalPlays.push_back(*it);
        }
    }
}
//returns true if Card c is in legalPlays
bool Player::legalPlaysCardFinder(Card c) {
    std::vector<Card>::iterator it;
    it = find(legalPlays.begin(), legalPlays.end(), c);
    if (it != legalPlays.end()) {
        return true;
    } else {
        return false;
    }
}
//clear legalPlays
void Player::clearLegalPlays() {
    legalPlays.clear();
}
//print legalPlays e.g. "Legal plays: 7H 5S"
void Player::printLegalPlays() {
    std::cout << "Legal plays:";
    for(auto it = legalPlays.begin(); it != legalPlays.end(); it++) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}
//returns the number of cards in legalPlays
bool Player::thereIsLegalPlays() {
    int num {0};
    num = static_cast<int>(legalPlays.size());

    if(num != 0) {
        return true;
    } else {
        return false;
    }
}
