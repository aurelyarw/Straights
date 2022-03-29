#include "table.h"
#include <iostream>

//ctor
Table::Table() :
    club{},
    diamond{},
    heart{},
    spade{} {}

//clear all the deques in table
void Table::clear() {
    club.clear();
    diamond.clear();
    heart.clear();
    spade.clear();
}

//add card to the table
void Table::addToTable(Card c) {
    
    std::string rank {c.getRank()};
    std::string suit {c.getSuit()};

    if(suit == "C") {
        if((rank == "A") || (rank <= "7")) {
            club.emplace_front(rank);
        } else { // "8", "9", "T", "J", "Q", "K"
            club.emplace_back(rank);
        }
    } else if(suit == "D") {
        if((rank == "A") || (rank <= "7")) {
            diamond.emplace_front(rank);
        } else { // "8", "9", "T", "J", "Q", "K"
            diamond.emplace_back(rank);
        }
    } else if(suit == "H") {
        if((rank == "A") || (rank <= "7")) {
            heart.emplace_front(rank);
        } else { // "8", "9", "T", "J", "Q", "K"
            heart.emplace_back(rank);
        }
    } else { //suite == "S"
        if((rank == "A") || (rank <= "7")) {
            spade.emplace_front(rank);
        } else { // "8", "9", "T", "J", "Q", "K"
            spade.emplace_back(rank);
        }
    }

}

//print the Table
void Table::printTable(){
    std::cout << "Cards on the table:" << std::endl;
    std::cout << "Clubs:";
    for (auto it = club.begin(); it != club.end(); it++) {
        std::cout << " " << *it ;
    }
    std::cout << std::endl << "Diamonds:";
    for (auto it = diamond.begin(); it != diamond.end(); it++) {
        std::cout << " " << *it ;
    }
    std::cout << std::endl << "Hearts:";
    for (auto it = heart.begin(); it != heart.end(); it++) {
        std::cout << " " << *it ;
    }
    std::cout << std::endl << "Spades:";
    for (auto it = spade.begin(); it != spade.end(); it++) {
        std::cout << " " << *it ;
    }    
    std::cout << std::endl;
}

