#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include <memory>
#include "Model.h"
#include "card.h"

class Model;
class Player;
class Deck;

class Controller {
    private:
        std::istream *source;
    public:
        Controller(std::istream *inp);
        int makeMove(std::shared_ptr<Player> player);
        Suit getSuit( std::string suit );
        std::shared_ptr<Card> testCard();
        int getTotalPlayers();
        int getCardsToBeDealt();
        void setRankJoker( std::shared_ptr<Card>, bool newHead );
};

#endif
