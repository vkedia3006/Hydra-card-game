#include "Controller.h"
#include "Model.h"
#include "player.h"
#include <memory>
#include "deck.h"
#include <iostream>
#include "card.h"
#include "joker.h"
#include "normalCard.h"
#include "playerWinsException.h"

Controller::Controller(std::istream *inp) : source{inp} {
}

int Controller::getTotalPlayers() {
    int playersNum = 0;
    while ( true ) {
        if ( source->eof() ) {
            source = &(std::cin);
        }
        else {
            std::cout << "How many players" << std::endl;
            if ( ! ( *source >> playersNum ) || playersNum < 2 ) {
				if ( source->eof() ) break;
                source->clear();
                source->ignore();
            }
            else break;
        }
    }
    return playersNum;
}

int Controller::getCardsToBeDealt() {
    int cardsToBeDealt = 0;
    while ( true ) {
        if ( source->eof() ) {
            source = &(std::cin);
        }
        else {
            std::cout << "How many cards should each player be given?" << std::endl;
            if ( ! ( *source >> cardsToBeDealt ) && cardsToBeDealt < 1) {
				if ( source->eof() ) break;
                source->clear();
                source->ignore();
            }
            else break;
        }
    }
    return cardsToBeDealt;
}

Suit Controller::getSuit( std::string suit ) {
    if ( (suit.compare("S")) == 0 ) return Suit::Spade;
    else if ( (suit.compare("C")) == 0 ) return Suit::Club;
    else if ( (suit.compare("H")) == 0 ) return Suit::Heart;
    else if ( (suit.compare("D")) == 0 ) return Suit::Diamond;
	else throw std::runtime_error{"Error"};
}

std::shared_ptr<Card> Controller::testCard() {
	while(true) {
		try {
			std::string rank;
			std::string suit;
			if ( source->eof() ) {
            	source = &(std::cin);
        	}
       		else {
            	std::cout << "Card value?" << std::endl;
				if ( ! ( *source >> rank ) ) {  // Remember, operator! === fail()
					if ( source->eof() ) throw PlayerWinsException{};
					source->clear();
					source->ignore();
				} else {
					if ( (rank.compare("Joker")) == 0 ) {
						auto joker = std::make_shared<JokerCard>(-1, Suit::Joker);
						return joker;
					}
					else {
						if ( source->eof() ) {
            				source = &(std::cin);
        				}
       					else {
							std::cout << std::endl << "Card Suit?" << std::endl;
							if ( ! ( *source >> suit ) ) {  // Remember, operator! === fail()
								if ( source->eof() ) throw PlayerWinsException{};
								source->clear();
								source->ignore();
							} else {
								Suit col = getSuit(suit);
								if ( (rank.compare("A")) == 0 ) {
									auto card = std::make_shared<NormalCard>(1, col);
									return card;
								}
								else if ( (rank.compare("K")) == 0 ) {
									auto card = std::make_shared<NormalCard>(13, col);
									return card;
								}
								else if ( (rank.compare("Q")) == 0 ) {
									auto card = std::make_shared<NormalCard>(12, col);
									return card;
								}
								else if ( (rank.compare("J")) == 0 ) {
									auto card = std::make_shared<NormalCard>(11, col);
									return card;
								}
								else {
									int value = stoi(rank);
									if (value >= 2 && value <= 10) { 
										auto card = std::make_shared<NormalCard>(value, col);
										return card;
									}
									else throw std::runtime_error{"Error"};
								}
							}
						}
					}
				}
			}	
		}
		catch(std::runtime_error &e) {
		}
		catch(std::invalid_argument) {
		}
	}
}

int Controller::makeMove(std::shared_ptr<Player> player) {
    int move = player->makeMove(source);
    return move;
}

void Controller::setRankJoker( std::shared_ptr<Card> card, bool newHead ) {
	card->setRankJoker(newHead, source);
}
