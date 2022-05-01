#include "joker.h"
#include <iostream>
#include "invalidCommandException.h"
#include <string>

JokerCard::JokerCard(int n, Suit suit) {
	setRank(n);
	setSuit(suit);
}

void JokerCard::setRankJoker( bool newHead, std::istream *source ) {
    if ( newHead ) {
        setRank(2);
    }
    else {
        while(true) {
            try {
                std::cout << "Joker value?" << std::endl;
                std::string rank;
                if ( source->eof() ) source = &(std::cin);
		        if ( ! ( *source >> rank ) ) {  // Remember, operator! === fail()
			        source->clear();
			        source->ignore();
                } else {
                    if ( (rank.compare("A")) == 0 ) {
                        setRank(1);
                        break;
                    }
                    else if ( (rank.compare("K")) == 0 ) {
                        setRank(13);
                        break;
                    }
                    else if ( (rank.compare("Q")) == 0 ) {
                        setRank(12);
                        break;
                    }
                    else if ( (rank.compare("J")) == 0 ) {
                        setRank(11);
                        break;
                    }
                    else {
                        int value = stoi(rank);
                        if (value >= 2 && value <= 10) { 
						    setRank(value);
							return;
						}
						else throw std::runtime_error{"Error"};
                    }
                }
            }
            catch(std::runtime_error &e) {
		    }
		    catch(std::invalid_argument) {
		    }
	    }
    }
}


void JokerCard::clearVal() {
    setRank(-1);
}

bool JokerCard::play( std::shared_ptr<Card> card, bool isItJoker) {
    if ( isItJoker ) {
        if ( card->getRank() > getRank() ) {
            return true;
        }
        else if ( card->getRank() == getRank() ) {
            return false;
        }
        else {
            clearVal();
            throw InvalidCommandException{};
        }
    }
    else {
        return card->getRank() < getRank();
    }
}
