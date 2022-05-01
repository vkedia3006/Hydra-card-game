#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include <memory>

class Card;

class Observer {
public:
    virtual void printHeadsandPlayers() = 0;
    virtual void playersTurn(int currentPlayer) = 0;
    virtual void inHandCard(int i, std::shared_ptr<Card> card) = 0;
    virtual void playerWins(int i) = 0;
    virtual ~Observer();
};

#endif
