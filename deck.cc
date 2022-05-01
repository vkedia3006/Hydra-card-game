#include <vector>
#include "deck.h"
#include "card.h"
#include <memory>
#include <iostream>
#include "normalCard.h"
#include "joker.h"

Deck::Deck( int seed ) : seed{seed} {}

void Deck::init( int playerNum, int random ) {
	for (int j = 0; j < playerNum; j++ ) {
		for (int i = 0; i < 54; i ++ ) {
			if ( i / 13 == 0 ) {
				auto card = std::make_shared<NormalCard>(i + 1, Suit::Heart);
				deckOfCards.push_back(card);
			}
			else if ( i / 13 == 1 ) {
			       	auto card = std::make_shared<NormalCard>(i - 12, Suit::Diamond);
				deckOfCards.emplace_back(card);
			}
			else if ( i / 13 == 2 ) {
				auto card = std::make_shared<NormalCard>(i - 25, Suit::Spade);
				deckOfCards.emplace_back(card);
			}
			else if ( i / 13 == 3 ) { 
				auto card = std::make_shared<NormalCard>(i - 38, Suit::Club);
				deckOfCards.emplace_back(card);
			}
			else {
				auto card = std::make_shared<JokerCard>(-1, Suit::Joker);
				deckOfCards.emplace_back(card);
			}
		}
	}
	seed = random;
	shuffle(54 * playerNum);
}

void Deck::shuffle( int n ) {
	if ( seed == -1 ) {
		srand(time(0));
	}
	else {
		srand(seed);
	}
	for (int i = 0; i < n ; i++) {
		int r = i + (rand() % (n - i));
		swap(deckOfCards[i], deckOfCards[r]);
	}
}

std::shared_ptr<Card> Deck::getCard(int n) {
	return deckOfCards[n];
}

void Deck::addCard(std::shared_ptr<Card> c) {
	deckOfCards.insert(deckOfCards.begin(), c);
}

std::shared_ptr<Card> Deck::top() {
	return deckOfCards.at(0);
}

int Deck::getSize() {
	return deckOfCards.size();
}

void Deck::copy(std::shared_ptr<Deck> d) {
	for ( unsigned int i = 0; i < deckOfCards.size(); i++ ) {
		d->addCard(deckOfCards[i]);
	}
	deckOfCards.clear();
}

void Deck::removeCard() {
	deckOfCards.erase(deckOfCards.begin());
}
