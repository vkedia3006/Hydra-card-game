#ifndef _VIEW_H
#define _VIEW_H
#include <memory>
#include "observer.h"
#include "Model.h"

class Card;

class View : public Observer {
    private:
        std::shared_ptr<Model> model;
        void printPlayers();
        void printHeads();
    public:
        View( std::shared_ptr<Model> m);
        virtual void printHeadsandPlayers() override;
        virtual void playersTurn(int currentPlayer) override;
        virtual void inHandCard(int i, std::shared_ptr<Card> card) override;
        virtual void playerWins(int i) override;
        virtual ~View();
};

#endif
