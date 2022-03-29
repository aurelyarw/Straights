#include "card.h"
#include <vector>

Card::Card(std::string r, std::string s) :
    rank{r},
    suit{s} {}

std::string Card::getRank() {
    return rank;
}

std::string Card::getSuit(){
    return suit;
}

int Card::value() {
    int value = 0;
    if(("2" <= rank) && (rank <= "9")) {
        value = std::stoi(rank);
    } else if(rank == "A") {
        value = 1;
    } else if(rank == "T") {
        value = 10;
    } else if(rank == "J") {
        value = 11;
    } else if(rank == "Q") {
        value = 12;
    } else { // rank == "K"
        value = 13;
    }
    return value;
}

bool Card::operator==(const Card &other) const {
    return ((rank == other.rank) && (suit == other.suit));
}

std::ostream & operator<<( std::ostream & out, const Card & c ) {
    std::cout << c.rank << c.suit;
    return out;
}
