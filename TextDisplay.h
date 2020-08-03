#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include "observer.h"
#include "gameBoard.h"
#include "displayStruct.h"
#include <iostream>

// Observer DP

class TextDisplay : public Observer {

public:
    TextDisplay(std::ostream &, gameBoard *);
    ~TextDisplay();

    void notify_() override;

private:
    gameBoard* subject_;
    std::ostream& out;

};

#endif //TEXTDISPLAY_H