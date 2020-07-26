#include "level_test.h"
#include "levels.h"
#include <memory>
#include <utility>
using namespace std;

AgileBidder::AgileBidder(size_t chips) : 
    strat{make_unique<Conservative>()}, chips{chips} {}

size_t AgileBidder::bid() {
    size_t bid = strat->bid(*this);
    chips -= bid;
    return bid;
}
size_t AgileBidder::chipCount() const {
    return chips;
}
void AgileBidder::setStrategy(unique_ptr<BiddingStrategy> s) {
    strat = move(s);
}
