#ifndef _HEAD_H_
#define _HEAD_H_

#include <memory>
#include <vector>
#include "player.h"

class Card;

class Head {
	std::shared_ptr<Deck> head;
	int index;

	public:
		Head( int index );
		std::shared_ptr<Card> getTop();
		void addCardHead(std::shared_ptr<Card> c);
		std::shared_ptr<Deck> getDeck();
		int getSize();
		int getIndex();
};

#endif
