#ifndef STRATEGIES_H_
#define STRATEGIES_H_
#include <cstddef>
class AgileBidder;

class BiddingStrategy {
  public:
    virtual size_t bid(const AgileBidder &) const = 0;
};

class Aggressive : public BiddingStrategy {
  public:
    size_t bid(const AgileBidder &) const override;
};

class Conservative : public BiddingStrategy {
  public:
    size_t bid(const AgileBidder &) const override;
};
#endif
