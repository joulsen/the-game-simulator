#include "game.h"
Game::Game(int playercount, std::default_random_engine* rng) {
    deck.reserve(99);
    for (int i = 0; i < 99; i++) {
        deck.push_back(i+1);
    }
    std::shuffle(deck.begin(), deck.end(), *rng);
    int hand_size_max = 9 - std::min(3, playercount);
    piles = new Pile[4];
    players.reserve(playercount);
    for (int i=0; i < 4; i++) {
        Player player(piles, deck);
        player.set_hand_size(hand_size_max);
        player.draw();
        players.push_back(player);
        piles[i].set_type((i <= 1));
    }
}
void Game::emulate() {
    while (true) {
        for (auto p = players.begin(); p != players.end(); ++p) {
            std::vector<Move> plays = p->play_greedy();
            p->draw();
            if (plays.size() < 2 - deck.empty()) {
                return;
            }
        }
    }
}
int Game::get_score() {
    int score = deck.size();
    for (auto p = players.begin(); p != players.end(); ++p) {
        score += p->hand.size();
    }
    return score;
}