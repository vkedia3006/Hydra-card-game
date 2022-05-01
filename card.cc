#include "card.h"
#include <iostream>
#include <memory>

Card::~Card() {}

int Card::getRank() {
	return rank;
}

Suit Card::getSuit() {
	return suit;
}

void Card::setRank( int rank ) {
	this->rank = rank;
}

void Card::setSuit( Suit suit ) {
	this->suit = suit;
}

void Card::printRank( std::ostream & out ) {
	if ( rank == 1 ) {
		out << 'A';
	}
	else if ( rank == 13 ) {
		out << "K";
	}
	else if ( rank == 12 ) {
		out << "Q";
	}
	else if ( rank == 11 ) {
		out << "J";
	}
	else {
		out << rank;
	}
}

std::ostream & operator<<( std::ostream & out, std::shared_ptr<Card> c ) {
	if ( c->getSuit() == Suit::Heart ) {
		c->printRank(out);
		out << "H";
	}
	else if ( c->getSuit() == Suit::Diamond ) {
		c->printRank(out);
		out << "D";
	}
	else if (  c->getSuit() == Suit::Spade ) {
		c->printRank(out);
		out << "S";
	}
	else if (  c->getSuit() == Suit::Club ) {
		c->printRank(out);
		out << "C";
	}
	else if ( c->getSuit() == Suit::Joker && c->getRank() == -1 ) {
		out << "Joker";
	}
	else if ( c->getSuit() == Suit::Joker && c->getRank() != -1) {
		c->printRank(out);
		out << "J";
	}
	return out;
}
