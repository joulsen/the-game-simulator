#ifndef THEGAME_PILE
#define THEGAME_PILE
#include <vector>   

class Pile {
    public:
        int sgn;
        std::vector<int> content;
        Pile();
        void set_type(bool descending);
        void append(int card);
};
#endif
