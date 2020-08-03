#include "subject.h"

// Observer DP

//--------------------------------------------------------------------------------------------
// Constructor and Destructor
Subject::Subject() {}
Subject::~Subject() {}

//--------------------------------------------------------------------------------------------
// Manipulate Observers
void Subject::attach(Observer *o)
{
    observers.emplace_back(o);
}

void Subject::detach(Observer *o)
{
    for (auto it = observers.begin(); it != observers.end();)
    {
        if (*it == o)
        {
            observers.erase(it);
        } else { ++it; }
    }
}

//--------------------------------------------------------------------------------------------
// Notify Observers
void Subject::notifyObservers()
{
    for (auto ob : observers) ob->notify_();
}