#ifndef _MODEL_H
#define _MODEL_H
#include <vector>
#include <memory>
#include "subject.h"

class Deck;
class Controller;
class View;
class Player;
class Head;
class Card;

class Model : public Subject {
    public:
        Model(std::shared_ptr<Deck> deck, std::shared_ptr<Controller> controller, bool testing, int seed);
        void initializeGame();
        std::shared_ptr<Player> getPlayer( int i );
        std::shared_ptr<Head> getHead( int i );
        int getTotalPlayers();
        int getTotalHeads();
        void addDiscard( std::shared_ptr<Deck> d, int player );
        ~Model();
    
    private:
        std::shared_ptr<Deck> deck;
        std::shared_ptr<Controller> controller;
        bool testingMode;
        std::vector<std::shared_ptr<Player>> players;
        std::vector<std::shared_ptr<Head>> heads;
        int totalPlayer;
        int seed;
        void dealCards( int k );
        void addHead(int player, int index);
        std::shared_ptr<Head> findHead( int headNo );
        bool hasToCutHead( std::shared_ptr<Card> inHand );
        void makeMove( int headNo, int player, std::shared_ptr<Card> inHand );
        void PlayGame();
};

#endif
