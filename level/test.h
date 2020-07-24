#ifndef TEST_H_
#define TEST_H_
#include <memory>
class BiddingStrategy;

class AgileBidder {
    std::unique_ptr<BiddingStrategy> strat;
    size_t chips;
  public:
    AgileBidder(size_t);
    size_t bid();
    size_t chipCount() const;
    void setStrategy(std::unique_ptr<BiddingStrategy>);
};

#endif
