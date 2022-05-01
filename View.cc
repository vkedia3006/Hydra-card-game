#include "View.h"
#include "player.h"
#include "invalidCommandException.h"
#include <iostream>
#include "card.h"
#include <iomanip>

View::View( std::shared_ptr<Model> m) : model{m} {
	model->attach(this);
	
	model->initializeGame();
}

View::~View() {
	model->detach(this);
}

void View::printPlayers() {
	std::cout << "Players: " << std::endl;
	for ( int i = 0; i < model->getTotalPlayers(); i++ ) {
		std::cout << "Player " << i+1 << ": " << model->getPlayer(i) << std::endl;
	}
	std::cout << std::endl;
}

void View::printHeads() {
	std::cout << std::endl << "Heads:" << std::endl << std::endl;
	for ( int i = 0; i < model->getTotalHeads(); i++ ) {
		std::cout << model->getHead(i)->getIndex() + 1 << ": " 
				  << model->getHead(i)->getTop() << " (" << model->getHead(i)->getSize() << ")" << std::endl;
	}
	std::cout << std::endl;
}

void View::printHeadsandPlayers() {
	printHeads();
	printPlayers();
}

void View::playersTurn( int currentPlayer ) {
	std::cout << "Player " << currentPlayer << ", it is your turn" << std::endl << std::endl;
}

void View::inHandCard( int i, std::shared_ptr<Card> card ) {
	std::cout << "Player " << i << ", you are holding a ";
	std::cout << card << ". Your move?" << std::endl;
}

void View::playerWins( int i ) {
	std::cout << "Player " << i << " wins!" << std::endl;
}
