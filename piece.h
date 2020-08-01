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

};

#endif




