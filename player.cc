#include "player.h"
#include <vector>
#include "card.h"
#include <memory>
#include <iostream>
#include "card.h"
#include "endTurnException.h"
#include "playerWinsException.h"
#include "invalidCommandException.h"
#include <stdexcept>
#include <string>

Player::Player( int seed ) : current{false} {
	draw = std::make_shared<Deck>(seed);
	discard = std::make_shared<Deck>(seed);
}

std::shared_ptr<Card> Player::getCard() {
	if ( draw->getSize() == 0 ) {
		if ( discard->getSize() == 0 ) {
			throw EndTurnException{};
		}
		else {
			discard->shuffle(discard->getSize());
			discard->copy(draw);
		}
	}
	std::shared_ptr<Card> card = draw->top();
	draw->removeCard();
	return card;
}

void Player::playerWins() {
	if ( draw->getSize() == 0 && discard->getSize() == 0 && (!reserve) ) {
		throw PlayerWinsException{};
	}
}

std::shared_ptr<Card> Player::getInHand() {
	return inHand;
}

void Player::setInHand(std::shared_ptr<Card> card) {
	inHand = card;
}

void Player::startTurn( int n, int r ) {
	remaining = r - n;
	inHand = getCard();
}

int Player::makeMove(std::istream *source) {
	int m;
	while ( true ) {
		if ( source->eof() ) source = &(std::cin);
		if ( ! ( *source >> m ) ) {  // Remember, operator! === fail()
			if ( source->eof() ) throw PlayerWinsException{};
			source->clear();
			source->ignore();
		//throw InvalidCommandException{};
		}
		else break;
	}
	return m - 1;
}

void Player::addCard(std::shared_ptr<Card> card, std::string str) {
	if ( str.compare("draw") == 0 ) {
		draw->addCard(card);
	} else if ( str.compare("discard") == 0 ) {
		discard->addCard(card);
	}
}

void Player::setCurrent(bool b) {
	if ( ! b ) {
		if ( reserve ) {
			draw->addCard(reserve);
			reserve = nullptr;
		}
		inHand = nullptr;
	}
	current = b;
}

void Player::swapReserve() {
	if ( reserve ) {
		std::shared_ptr<Card> temp = inHand;
		inHand = reserve;
		reserve = temp;
	}
	else {
		reserve = inHand;
		inHand = getCard();
	}
}

void Player::print( std::ostream & out ) const {
	out << draw->getSize() + discard->getSize() << " (" << draw->getSize() << " draw, " << discard->getSize() << " discard)";
	if ( current ) {
		out << " + 1 in hand, " << remaining << " remaining, " << (reserve ? "1 " : "0 ") << "in reserve";
	}
}

std::ostream & operator<<( std::ostream & out, std::shared_ptr<Player> p ) {
	p->print(out);
	return out;
}
