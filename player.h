#ifndef THEGAME_PLAYER
#define THEGAME_PLAYER
#include <vector>
#include "pile.h"
#include "move.h"

class Player {
    public:
        int hand_size_max;
        std::vector<int> hand;
        Pile* piles;
        std::vector<int> &deck;
        Player(Pile* p, std::vector<int> &d): piles(p), deck(d) {};
        void set_hand_size(int hand_size_max);
        bool draw();
        int get_must_play();
        std::vector<Move> get_legal_moves();
        std::vector<Move> play_robotic();
        int get_greed();
        std::vector<Move> play_greedy();
};
#endif
