#ifndef _DISPLAYSTRUCT_
#define _DISPLAYSTRUCT_

// struct to be passed to observers (displays)
// for Observer DP
struct DisplayStruct
{
    int level_;
    int score_;
    int hiScore_;
    char board_[18][11];
};

#endif