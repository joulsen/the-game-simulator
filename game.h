#ifndef THEGAME_GAME
#define THEGAME_GAME
#include <random>
#include <vector>
#include "pile.h"
#include "move.h"
#include "player.h"

class Game {
    public:
        std::vector<int> deck;
        Pile* piles;
        std::vector<Player> players;
        int playercount;
        std::default_random_engine* rng;
        Game(int playercount, std::default_random_engine* rng);
        void emulate();
        int get_score();
};
#endif
