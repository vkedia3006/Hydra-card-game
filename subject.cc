#include "subject.h"
#include <memory>
#include "card.h"
Subject::Subject() {}

Subject::~Subject() {}

void Subject::attach( Observer *o ) {
    observers.emplace_back(o);
}

void Subject::detach( Observer *o ) {
    for ( auto it = observers.begin(); it != observers.end(); ++it ) {
        if ( *it == o ) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyToPrintHeadsandPlayers() {
    for (auto ob : observers) ob->printHeadsandPlayers();
}

void Subject::notifyPlayersTurn(int currentPlayer) {
    for (auto ob : observers) ob->playersTurn(currentPlayer);
}

void Subject::notifyInHandCard(int i, std::shared_ptr<Card> card) {
    for (auto ob : observers) ob->inHandCard(i, card);
}

void Subject::notifyPlayerWins(int i) {
    for (auto ob : observers) ob->playerWins(i);
}
