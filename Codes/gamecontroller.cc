#include "gamecontroller.h"
#include "human.h"
#include "computer.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <sstream>
#include <assert.h> 

GameController::GameController(unsigned seed, int overScore, std::vector<Card> startDeck) :
    seed{seed},
    overScore{overScore},
    startDeck{startDeck},
    numPlayers{0},
    players{},
    playable{},
    turn{0},
    round{0} {
        t = std::make_unique<Table>();
    }

void GameController::printStartDeck() {
    for(int i = 0; i <= 51; i++) {
        std::cout << startDeck[i];

        if(((i + 1)% 13) == 0) {
            std::cout << std::endl;
        } else {
            std::cout << " ";
        }
    }
}

void GameController::addPlayers(int numPlayers, std::istream &is) {
    this->numPlayers = numPlayers;
    for(int p = 1; p <= numPlayers; p++) {
        std::string playerType{};
        while((playerType != "h") && (playerType != "c")) {
            //ask
            std::cout << "Is Player<" << p << "> a human (h) or a computer (c)?" << std::endl;
            std::cout << ">";
            //answer
            std::string line{};
            std::getline(is, line);
            std::stringstream ss {line};
            ss >> playerType;
        }
        if(playerType == "h") {
            players.push_back( std::make_unique<Human>(p) );
        } else { //if playerType == "c"
            players.push_back( std::make_unique<Computer>(p) );
        }
    }
}

void GameController::shuffleDeal() {
    //shuffle startDeck
    std::default_random_engine rng{seed};
    std::shuffle( startDeck.begin(), startDeck.end(), rng );
    bool p;
    int sd = 0;
    //distribute startDeck to players
    //find the starter player (the owner of 7S)
    //add 7S to playable
    for(auto it = players.begin(); it != players.end(); it++) {
        p = true;
        while(p){
            (*it)->addHand( startDeck[sd] );
            if( (startDeck[sd].getRank() == "7") && (startDeck[sd].getSuit() == "S") ) {
                playable.push_back( startDeck[sd] );
                    turn = (*it)->getId() - 1;
            }
            sd++;
            if(sd % 13 == 0){
                p = false;
            }
        }
    }
}

bool GameController::gameContinue() {
    //if there's still player with card in his hand, continue playing
    for(auto it = players.begin(); it != players.end(); it++) {
        if((*it)->thereIsHand()) { 
            return true;
        }
    }
    int minTotalScore{0};
    int maxTotalScore{0};
    //if all hands are empty
    //and not the beginning round
    if(round != 0) {
        t->printTable(); //
        //Print:
        //Player<x>’s discards:<list of discards>
        //Player<x>’s score: <old score> + <score gained> = <new score>
        //empty discard
        //find the min score of the players (i.e. the winners' score)
        for(auto it = players.begin(); it != players.end(); it++) {
            (*it)->printDiscard();
            (*it)->printAddTotalScore();
            maxTotalScore = std::max(maxTotalScore, (*it)->getTotalScore());
            (*it)->clearDiscard();
        }
        minTotalScore = players[0]->getTotalScore();
        for(auto it = players.begin() + 1; it != players.end(); it++) {
            minTotalScore = std::min(minTotalScore, (*it)->getTotalScore());
        }        
    }
    bool nextRound = false;
    //check if there will be next round (i.e. no player score is more than overScores)
    if(maxTotalScore < overScore) {
        nextRound = true;
        round++;
    }
    //if there is next round, clear table, clear playable, shuffleDeal & return true
    if(nextRound) {
        t->clear();
        playable.clear();
        //std::cout << "round = " << round << std::endl; //
        shuffleDeal();
        std::cout << "A new round begins. It’s Player" << turn + 1 << "’s turn to play." << std::endl;
        return true;
    } else { //else print the winner(s) and return false
        for(auto it = players.begin(); it != players.end(); it++) {
            if((*it)->getTotalScore() == minTotalScore) {
                std::cout << "Player" << (*it)->getId() << " wins!" << std::endl;
            }
        }
        //std::cout << "total round # = " << round << std::endl; //
        return false;
    }
}

//after a card is played, update playable
//remove the card that is played from playable and
//add playable cards when card has been played
void GameController::updatePlayable(Card c) {
    std::vector<Card>::iterator it;
    it = find(playable.begin(), playable.end(), c);
    assert(it != playable.end()); //Card c is supposed to be in playable alr
    playable.erase(it);
    std::string rank{c.getRank()};
    std::string suit{c.getSuit()};
    if((rank == "A") || (rank == "K")) {
        //do nothing
    } else if(rank == "2") {
        playable.emplace_back("A", suit);
    } else if(rank == "3") {
        playable.emplace_back("2", suit);
    } else if(rank == "4") {
        playable.emplace_back("3", suit);
    } else if(rank == "5") {
        playable.emplace_back("4", suit);
    } else if(rank == "6") {
        playable.emplace_back("5", suit);
    } else if(rank == "7") {
        if(suit == "S") {
            playable.emplace_back("7", "C");
            playable.emplace_back("7", "D");
            playable.emplace_back("7", "H");
        }
        playable.emplace_back("6", suit);
        playable.emplace_back("8", suit);
    } else if(rank == "8") {
        playable.emplace_back("9", suit);
    } else if(rank == "9") {
        playable.emplace_back("T", suit);
    } else if(rank == "T") {
        playable.emplace_back("J", suit);
    } else if(rank == "J") {
        playable.emplace_back("Q", suit);
    } else { // rank == "Q"
        playable.emplace_back("K", suit);
    }
}

void GameController::runGame(int numPlayers, std::istream &is){
    addPlayers(numPlayers, is);
    bool nextTurn = true;
    while( gameContinue() ){
        try{
            /*
            std::cout << "playable:"; //
            for(auto it = playable.begin(); it != playable.end(); it++) { //
                std::cout << " " << *it;

            std::cout << std::endl; //
            */
            if(nextTurn) {
                players[turn]->makeLegalPlays(playable);
            }
            if(players[turn]->isHuman()) {
                if(nextTurn) {
                    // std::cout << "HUMAN//////////////////////////////////////////////////////////////////" << std::endl; //
                    t->printTable();
                    players[turn]->printHand();
                    players[turn]->printLegalPlays();
                    //players[turn]->printDiscard(); //
                    std::cout << ">";
                }
                nextTurn = true;
                std::string line{};
                std::getline(is, line);
                std::stringstream ss {line};
                std::string cmd{};
                ss >> cmd;
                if(cmd == "play") {
                    if(!(players[turn]->thereIsLegalPlays())) {
                        throw(2);
                    }
                    std::string cardStr{};
                    ss >> cardStr;
                    Card c{players[turn]->play(cardStr)}; //throws if card played is not right
                    t->addToTable(c);
                    updatePlayable(c);
                } else if(cmd == "discard") {
                    if(players[turn]->thereIsLegalPlays()) {
                        throw(3);
                    }
                    std::string cardStr{};
                    ss >> cardStr;
                    players[turn]->pDiscard(cardStr); //throws if card played is not right
                } else if(cmd == "deck") {
                    nextTurn = false;
                    printStartDeck();
                    std::cout << ">";
                } else if(cmd == "quit") {
                    break;
                } else if(cmd == "ragequit") {
                    nextTurn = false;
                    players[turn] = std::make_unique<Computer>(*players[turn]);
                    std::cout << "Player " << players[turn]->getId() << " ragequits. A computer will now take over." << std::endl;
                } else {
                    throw(1);
                }
            } else {
                nextTurn = true;
                /*
                std::cout << "COMPUTER/////////////////////////////////////////////////////////////////////" << std::endl; //
                t->printTable(); //
                players[turn]->printHand(); //
                players[turn]->printLegalPlays(); //
                players[turn]->printDiscard(); //
                */
                if(players[turn]->thereIsLegalPlays()) {
                    Card c{players[turn]->play("")};
                    t->addToTable(c);
                    updatePlayable(c);
                } else {
                    players[turn]->pDiscard("");
                }
            } //if
        } catch (int errnum) {
            switch(errnum){
                case 1: std::cout << "Invalid command" << std::endl << ">"; break;
                case 2: std::cout << "This is not a legal play." << std::endl << ">"; break;
                case 3: std::cout << "You have a legal play. You may not discard." << std::endl << ">"; break;
                case 4: std::cout << "No such card." << std::endl << ">"; break;
                case 5: std::cout << "This is not a legal play." << std::endl << ">"; break;
                case 6: std::cout << "Can't discard card. Card is not in hand" << std::endl << ">"; break;
            }
            nextTurn = false;
        } //catch
        if(nextTurn) {
            players[turn]->clearLegalPlays(); //clear the legalPlays after player's turn ends
            //std::cout << "change to next player" << std::endl; //
            turn++;
            turn = turn % numPlayers;
        }
    } //while
}
