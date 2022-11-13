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
        void* strategy;
        std::vector<int> hand;
        Player() {};
        void set_hand_size(int hand_size_max);
        bool draw(std::vector<int> &deck);
        std::vector<Move> get_legal_moves(Pile* piles);
};
void Player::set_hand_size(int hand_size_max) {
    this->hand_size_max = hand_size_max;
    hand.reserve(hand_size_max);
}
bool Player::draw(std::vector<int> &deck) {
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
std::vector<Move> Player::get_legal_moves(Pile* piles) {
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

class Game {
    public:
        std::vector<int> deck;
        Pile* piles;
        Player* players;
        int playercount;
        Game(int playercount);
};
Game::Game(int playercount) {
    deck.reserve(99);
    for (int i = 0; i < 99; i++) {
        deck.push_back(i+1);
    }
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine());
    int hand_size_max = 9 - std::min(3, playercount);
    piles = new Pile[4];
    players = new Player[playercount];
    for (int i=0; i < 4; i++) {
        piles[i].set_type((i <= 1));
        players[i].set_hand_size(hand_size_max);
        players[i].draw(deck);
    }
}

void print_vector(std::vector<int> v) {
    for (auto it=v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

int main(){
    Game game(4);
    game.piles[0].append(79);
    auto moves = game.players[0].get_legal_moves(game.piles);
    for (auto it = moves.begin(); it != moves.end(); ++it) {
        std::cout << it->card << " onto " << it->pile->content.back() << " of cost " << it->cost << '\n';
    }
}