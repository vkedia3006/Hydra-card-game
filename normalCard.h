#ifndef _NORMALCARD_H
#define _NORMALCARD_H
#include "card.h"
#include <memory>

class NormalCard : public Card {
    public:
        NormalCard(int rank, Suit suit);
        virtual void setRankJoker( bool newHead, std::istream *source ) override;
        virtual void clearVal() override;
        virtual bool play( std::shared_ptr<Card>, bool isItJoker ) override;
};

#endif
