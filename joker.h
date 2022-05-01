#ifndef _JOKER_H
#define _JOKER_H
#include "card.h"

class JokerCard : public Card {
    public:
        JokerCard(int rank, Suit suit);
        virtual void setRankJoker( bool newHead, std::istream *source ) override;
        virtual void clearVal() override;
        virtual bool play( std::shared_ptr<Card>, bool isItJoker ) override;
};

#endif
