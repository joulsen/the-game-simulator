#include <iostream>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm>

class Pile {
    public:
        int sgn;
        std::vector<int> content;
        Pile();
        void set_type(bool descending);
        void append(int card);
};
Pile::Pile() {
    content.reserve(100);
}
void Pile::set_type(bool descending) {
    if (descending) {
        sgn = -1;
        content.push_back(100);
    } else {
        sgn = 1;
        content.push_back(1);
    }
}
void Pile::append(int card) {
    content.push_back(card);
}

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
};
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
    draw();
    return plays;
}

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
            std::vector<Move> plays = p->play_robotic();
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
        std::cout << game.get_score() << '\n';
        for (int i = 0; i < 4; i++) {
            print_vector(game.piles[i].content);
        }
        for (auto it = game.players.begin(); it != game.players.end(); ++it) {
            print_vector(it->hand);
        }
        print_vector(game.deck);
    }
}
