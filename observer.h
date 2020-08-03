#ifndef OBSERVER_H
#define OBSERVER_H

// Observer DP

class Observer {
public:
  virtual ~Observer();

  // to be overridden by displays
  virtual void notify_() = 0;
};

#endif