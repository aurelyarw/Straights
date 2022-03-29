#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>
#include <memory>

#include "gamecontroller.h"
#include "card.h"
#include "table.h"
#include "player.h"
#include "human.h"
#include "computer.h"

int main(int argc, char* argv[]) {

    if( argc > 4 ) {
        std::cout << "Too many arguments. Formats:" << std::endl;
        std::cout << "./straights" << std::endl;
        std::cout << "./straights (seed)" << std::endl;
        std::cout << "./straights -f (fileName)" << std::endl;
        std::cout << "./straights (seed) -f (fileName)" << std::endl;
        return 0;
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    bool filefound = false;
    std::ifstream infile;

    int counter{1};
    int last_arg_posn{argc - 1};  
    const std::string f{"-f"};

    while(counter <= last_arg_posn) { // if argument is still available
        if(argv[counter] == f) { //file
            counter++;
            if(counter > last_arg_posn) {
                filefound = false;
                std::cout << "No input file. Input is now using std::cin." << std::endl;
            }
            filefound = true;
            infile.open(argv[counter]);
            if( infile.fail() ) {
                filefound = false;
                std::cout << "Can't open input file. Input is now using std::cin." << std::endl;
            } 
            break;
        } else { //seed
            if(counter != 1) {
                break;
            }
            try {
			    seed = std::stoi( std::string{ argv[counter] } );
		    } catch( std::invalid_argument & e ) {
                seed = std::chrono::system_clock::now().time_since_epoch().count();
			    std::cout << "error: " << e.what() << std::endl;
			    std::cout << "Now using a time-based seed." << std::endl;
		    } catch( std::out_of_range & e ) {
                seed = std::chrono::system_clock::now().time_since_epoch().count();
			    std::cout << "error: " << e.what() << std::endl;
                std::cout << "Now using a time-based seed." << std::endl;
		    } // catch
            counter++;
        }
    }

    //make Deck
    std::vector<Card> startDeck {};
    std::vector<std::string> ranks = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
    std::vector<std::string> suits = {"C", "D", "H", "S"};
    for(auto it_s = suits.begin(); it_s != suits.end(); it_s++) {
        for(auto it_r = ranks.begin(); it_r != ranks.end(); it_r++) {
            startDeck.emplace_back(*it_r, *it_s);
        }
    }
    
    //create the GameController
    int OVERSCORE = 80;
    GameController gc{seed,OVERSCORE,startDeck};
    int NUMPLAYERS = 4;
    std::cin.exceptions( std::ios::failbit|std::ios::eofbit );
    if(filefound) {
        infile.exceptions( std::ios::failbit|std::ios::eofbit );
    }
    try {
        gc.runGame(NUMPLAYERS, filefound? infile : std::cin);
    } catch (std::ios::failure) {}

    if(filefound) {
        infile.close();
    }
    return 0;
}
