#include <iostream>
#include <vector>
#include <random>
#include <numeric>
// #include "pile.h"
// #include "move.h"
// #include "player.h"
#include "game.h"


void print_vector(std::vector<int> v) {
    for (auto it=v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

int main(){
    std::default_random_engine rng(0);
    for (int i = 0; i < 1; i++) {
        Game game(4, &rng);
        game.emulate();
        std::cout << game.get_score();
    }
}
