#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>
#include "card.h"
#include <iostream>
#include <memory>
#include "deck.h"
#include "head.h"
#include <string>

class Head;

class Player{
	private:
		std::shared_ptr<Deck> draw;
		std::shared_ptr<Deck> discard;
		std::shared_ptr<Card> reserve;
		std::shared_ptr<Card> inHand;
		bool current;
		int remaining;
		std::shared_ptr<Card> getCard();

	public:
		Player( int seed );

		int makeMove(std::istream *source);
		void startTurn( int n, int r);
		void swapReserve();
		
		void addCard(std::shared_ptr<Card> card, std::string str);
		void setInHand(std::shared_ptr<Card> card);
		void setCurrent(bool b);
		void print( std::ostream & out ) const;
		void playerWins();
		std::shared_ptr<Card> getInHand();
};

std::ostream & operator<<( std::ostream & out, std::shared_ptr<Player> p);

#endif
