#include "pile.h"

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