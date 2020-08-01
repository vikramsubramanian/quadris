#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual void notify_() = 0; // to be overridden by view
    virtual ~Observer();
};

#endif
