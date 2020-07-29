#ifndef _PIECE_
#define _PIECE_

class Piece
{
    public: 
        int x;
        int y;
        char type;

    Piece(int xVal, int yVal, char t)
    {
        x = xVal;
        y = yVal;
        type = t;
    }
    // Design choice we have to make:
    //We said we would have only one method called transform() but that is not enough, we need accessors and mutators for all values
    //So i just made this a  struct with public members. But we could have a class + accessors and mutators.
};

#endif




