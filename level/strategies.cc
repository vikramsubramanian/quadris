#include "strategies.h"
#include "player.h"

size_t Aggressive::bid(const AgileBidder &p) const {
    return p.chipCount();
}

size_t Conservative::bid(const AgileBidder &p) const {
    return p.chipCount()/10;
}
