#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "card.h"
#include "player.h"
#include "table.h"
#include <string>
#include <vector>
#include <memory>

class GameController {

    unsigned seed;
    int overScore;
    std::vector<Card> startDeck;
    int numPlayers;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<Table> t;
    std::vector<Card> playable;
    int turn;
    int round;

    public:
    //ctor
    GameController(unsigned seed, int overScore, std::vector<Card> startDeck);

    //prints the starting deck for command = "deck"
    void printStartDeck();

    // addPlayers to GameController
    void addPlayers(int numPlayers, std::istream &is);

    //shuffle startDeck and deal cards to players
    //distribute startDeck to players
    //distribute startDeck to players
    //find the starter player (the owner of 7S)
    void shuffleDeal();

    //checks if the game still continue
    bool gameContinue();

    //after a card is played, update playable
    //remove the card that is played from playable and
    //add playable cards when card has been played
    void updatePlayable(Card c);

    //run the game
    void runGame(int numPlayers, std::istream &isream);

};

#endif
