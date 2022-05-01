#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include "observer.h"

class Subject {

   std::vector<Observer*> observers;

 public:
    Subject();
    void attach( Observer *o );
    void detach( Observer *o );
    void notifyToPrintHeadsandPlayers();
    void notifyPlayersTurn(int currentPlayer);
    void notifyInHandCard(int i, std::shared_ptr<Card> card);
    void notifyPlayerWins(int i);
    virtual ~Subject() = 0;
};

#endif
