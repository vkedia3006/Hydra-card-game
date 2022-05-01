#include "normalCard.h"

NormalCard::NormalCard(int n, Suit suit) {
	setRank(n);
	setSuit(suit);
}

void NormalCard::setRankJoker( bool newHead, std::istream *source ) {}
void NormalCard::clearVal() {}

bool NormalCard::play( std::shared_ptr<Card> card, bool isItJoker ) {
    return card->getRank() < getRank();
}
