#include "move.h"

Move::Move(std::vector<int>* hand, int card, Pile* pile) {
    this->hand = hand;
    this->card = card;
    this->pile = pile;
    int top = pile->content.back();
    cost = pile->sgn * (card - top);
    if (cost > 0 | cost == -10) {
        legal = true;
    } else {
        legal = false;
    }
}
bool Move::perform() {
    if (legal) {
        pile->append(card);
        hand->erase(std::find(hand->begin(), hand->end(), card));
        return true;
    } else {
        return false;
    }
}
