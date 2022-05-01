#include "head.h"
#include <memory>
#include <vector>
#include "card.h"

Head::Head( int index ) : index{index} {
	head = std::make_shared<Deck>(-1);
}

std::shared_ptr<Card> Head::getTop() {
	return head->top();
}

void Head::addCardHead(std::shared_ptr<Card> c) {
	head->addCard(c);
}

int Head::getIndex() {
	return index;
}

int Head::getSize() {
	return head->getSize();
}

std::shared_ptr<Deck> Head::getDeck() {
	return head;
}

