#include "player.h"
#include "strategies.h"
#include <iostream>
#include <memory>
using namespace std;


int main() {
    AgileBidder p(10000);
    cout << "Player starts with: " << p.chipCount() << endl;
    cout << "Player bids: " <<  p.bid() << " and still has: " \
         << p.chipCount() << endl;
    cout << "Switching strategies" << endl;
    p.setStrategy(make_unique<Aggressive>());
    cout << "Player bids: " << p.bid() << " and still has: " \
         << p.chipCount() << endl;
    return 0;
}
