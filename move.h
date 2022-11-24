#ifndef THEGAME_MOVE
#define THEGAME_MOVE
#include <vector>
#include <algorithm>
#include "pile.h"

class Move {
    public:
        int card;
        Pile* pile;
        std::vector<int>* hand;
        bool legal;
        int cost;
        Move(std::vector<int>* hand, int card, Pile* pile);
        bool perform();
};
#endif
