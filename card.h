#ifndef _CARD_H
#define _CARD_H

#include <iostream>
#include <memory>
// suit of the card
enum class Suit { Heart, Diamond, Spade, Club, Joker };

// Information for the card to return i.e. its suit and the rank.
class Card {
    Suit suit;
    int rank;

	public:
	~Card();
	int getRank();
	Suit getSuit();
	
	// Called from joker once it gets the value that its supposed to be
	void setRank( int rank );
	void setSuit( Suit suit );

	void printRank( std::ostream & out );

	virtual void setRankJoker( bool newHead, std::istream *source ) = 0;
	// Clears the info of the joker
	virtual void clearVal() = 0;

	virtual bool play( std::shared_ptr<Card>, bool isItJoker ) = 0;
};

std::ostream & operator<<( std::ostream & out, std::shared_ptr<Card> c );

#endif
