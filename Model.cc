#include <vector>
#include <memory>
#include "Model.h"
#include "Controller.h"
#include "deck.h"
#include "player.h"
#include "card.h"
#include "head.h"
#include "invalidCommandException.h"
#include "endTurnException.h"
#include "playerWinsException.h"

Model::Model(std::shared_ptr<Deck> deck, std::shared_ptr<Controller> controller, bool testing, int seed) 
	: deck{deck}, controller{controller}, testingMode{testing}, seed{seed} {
}

Model::~Model() {}

void Model::initializeGame() {
	totalPlayer = controller->getTotalPlayers();
	for (int i = 0; i < totalPlayer; i++ ) {
		std::shared_ptr<Player> player = std::make_shared<Player>(seed);
		players.push_back(player);
	}
	deck->init(totalPlayer, seed);
	if ( testingMode ) {
		int cardsToBeDealt = controller->getCardsToBeDealt();
		dealCards(cardsToBeDealt);

	}
	else {
		dealCards(54);
	}
	PlayGame();
}

int Model::getTotalPlayers() {
	return totalPlayer;
}

int Model::getTotalHeads() {
	return heads.size();
}

std::shared_ptr<Player> Model::getPlayer( int i ) {
	return players.at(i);
}


std::shared_ptr<Head> Model::getHead( int i ) {
	return heads.at(i);
}

void Model::dealCards( int k ) {
    int n = 0;
	for ( int i = 0; i < totalPlayer; i++ ) {
		for ( int j = n * k; j < k * (n + 1); j++ ) {
			players[i]->addCard(deck->getCard(j), "draw");
		}
		n++;
	}
}

void Model::addDiscard( std::shared_ptr<Deck> d, int player ) {
	for ( int i = 0; i < d->getSize(); i++ ) {
		players[player]->addCard(d->getCard(i), "discard");
	}
}

void Model::addHead ( int player, int index ) {
    auto head = std::make_shared<Head>(index);
	players[player]->startTurn( 0, 0 );
	if ( testingMode) {
		players[player]->setInHand(controller->testCard());
	}
	auto card = players[player]->getInHand();
	//card->setRankJoker(true);
	controller->setRankJoker( card, true );
	head->addCardHead( card );
	heads.push_back( head );
}

std::shared_ptr<Head> Model::findHead( int headNo ) {
	for ( unsigned int i = 0; i < heads.size(); i++ ) {
		if ( heads[i]->getIndex() == headNo ) {
			return heads[i];
		}
	}
	throw InvalidCommandException{};
}

bool Model::hasToCutHead( std::shared_ptr<Card> inHand ) {
	for ( unsigned int i = 0; i < heads.size(); i ++ ) {
		if ( heads[i]->getTop()->play(inHand, false) 
		|| heads[i]->getTop()->getRank() == 1 
		|| heads[i]->getTop()->getRank() == inHand->getRank() ) {
			return true;
		}
	}
	return false;
}

void Model::makeMove(int headNo, int player, std::shared_ptr<Card> inHand) {
	// Start of the game make a head simply at pos 0
    if ( headNo == -1 ) {
        addHead(player, 0);
    }
    else {
		std::shared_ptr<Head> head = findHead( headNo );
        std::shared_ptr<Card> card = head->getTop();		// Store the card value that is on top of head the player moves
		bool cutHead = hasToCutHead(inHand);
		// Special case to check if the move is on the oldest head

		if ( heads.at(0)->getIndex() == headNo ) {						// Place the inHand card of the player on the head
			// Checks if value of head top card is strictly greater than the played card or if it is an Ace
			if ( card->play( inHand, false ) || card->getRank() == 1 ) {
				card->clearVal();
				head->addCardHead(inHand);
				//Do nothing as the move is valid and the played card is placed on top of the head
			}
			// Checks if value of head top card is strictly less than the played card
			else if ( inHand->play( card, true ) ) { 
				if ( cutHead ) {
					throw InvalidCommandException{};
				}
				card->clearVal();
				head->addCardHead(inHand);
				addDiscard(heads[0]->getDeck(), player);				// Add the cards of the head to the players discard pile
				heads.erase(heads.begin());								// Remove the head from the list of heads
       			int oldSize = heads.size();
 		        addHead(player, (2 * oldSize) + 1);						// Make two new heads
 		        addHead(player, (2 * oldSize) + 2);
				throw EndTurnException{};								// Exception is thrown to signal the end of the turn
			}
			// The card played has the same value as the top card of the head
			else {
				card->clearVal();
				head->addCardHead(inHand);
				throw EndTurnException{};							
			}
		}
		else {
			// Checks if value of head top card is strictly greater than the played card or if it is an Ace
			if ( card->play( inHand, false ) || card->getRank() == 1 ) {
				card->clearVal();
				head->addCardHead(inHand);
			}
			// Checks if value of head top card is strictly less than the played card
			else if ( inHand->play( card, true ) ) {
				throw InvalidCommandException{};						// Throw invalid command the head is not the oldest and hence
																		// Cannot be cut off
			}
			else {
				card->clearVal();
				head->addCardHead(inHand); 
				throw EndTurnException{};
			}
		}
    }
    players[player]->playerWins();
}

//High cohesion. Low coupling. I should explain this

void Model::PlayGame() {
	int i = 0;
	try {
		makeMove(-1, 0, nullptr);
		i++;
		notifyToPrintHeadsandPlayers();
		while(true) {
			try {
				if ( (i+1) > totalPlayer ) {
					i = 0;
				}
				notifyPlayersTurn(i+1);
				players[i]->setCurrent(true);
				int numHeads = heads.size();
				for ( int n = 0; n < numHeads; n++ ) {
					players[i]->startTurn( n + 1, numHeads );
					notifyToPrintHeadsandPlayers();
					while(true) {
						try {
							notifyInHandCard( i + 1, players[i]->getInHand());
							if ( testingMode) {
								players[i]->setInHand(controller->testCard());
								notifyInHandCard( i + 1, players[i]->getInHand());
							}
							auto inHandCard = players[i]->getInHand();
							int move = controller->makeMove( players[i] );
							if ( move == -1 ) {
								if ( numHeads > 1 ) {
									players[i]->swapReserve();
								}
								else { throw InvalidCommandException{}; }
							}
							else {
									controller->setRankJoker( inHandCard, false );
									makeMove(move, i, inHandCard);
									//players[i]->playerWins();
									break;
							}
						}
						catch (InvalidCommandException &e) {
							// Invalid Command! the prompt is shown again
						}
						catch (EndTurnException &e) {
							throw EndTurnException{};
						}
					}
				}
				players[i]->setCurrent(false);
				notifyToPrintHeadsandPlayers();
				i++;
			}
			catch ( EndTurnException &e ) {
				players[i]->playerWins();
				players[i]->setCurrent(false);
				notifyToPrintHeadsandPlayers();
				i++;
			}
		}
	}
	catch( PlayerWinsException &e ) {
		notifyPlayerWins(i+1);
	}
}
