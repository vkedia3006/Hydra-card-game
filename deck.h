#ifndef _DECK_H_
#define _DECK_H_

#include <vector>
#include "card.h"
#include <memory>

class Deck {
	std::vector<std::shared_ptr<Card>> deckOfCards;
	int seed;

	public:
		Deck( int seed );

		void init( int playerNum, int random );

		void shuffle( int n );

		std::shared_ptr<Card> getCard( int i );

		void addCard(std::shared_ptr<Card> c);

		int getSize();

		void copy(std::shared_ptr<Deck> d);

		std::shared_ptr<Card> top();

		void removeCard();
};
#endif
