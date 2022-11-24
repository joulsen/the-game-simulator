#include "player.h"
void Player::set_hand_size(int hand_size_max) {
    this->hand_size_max = hand_size_max;
    hand.reserve(hand_size_max);
}
bool Player::draw() {
    int diff = hand_size_max - hand.size();
    for(int i=0; i < diff; i++) {
        if (deck.empty()) {
            return false;
        }
        hand.push_back(deck.back());
        deck.pop_back();
    }
    return true;
}
int Player::get_must_play() {
    return 2 - (int) deck.empty();
}
std::vector<Move> Player::get_legal_moves() {
    std::vector<Move> moves;
    moves.reserve(4*hand_size_max);
    for (int i = 0; i < 4; i++) {
        for (auto it = hand.begin(); it != hand.end(); ++it) {
            Move move(&hand, *it, &piles[i]);
            if (move.legal) {
                moves.push_back(move);
            }
        }
    }
    std::sort(moves.begin(), moves.end(),
        [](Move a, Move b) {
            return a.cost < b.cost;
        });
    return moves;
}

std::vector<Move> Player::play_robotic() {
    std::vector<Move> plays;
    for (int i = 0; i < get_must_play(); i++) {
        std::vector<Move> moves = get_legal_moves();
        if (!moves.empty()) {
            plays.push_back(moves[0]);
            moves[0].perform();
        }
    }
    return plays;
}
int Player::get_greed() {
    return 5;
}
std::vector<Move> Player::play_greedy() {
    std::vector<Move> plays = play_robotic();
    while (true) {
        std::vector<Move> moves = get_legal_moves();
        if (!moves.empty()) {
            if (moves[0].cost < get_greed()) {
                plays.push_back(moves[0]);
                moves[0].perform();
            } else {
                break;
            }
        } else {
            break;
        }
    }
    return plays;
}