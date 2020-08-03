#ifndef _PIECE_
#define _PIECE_

class Piece {
public:
  // coordinates of piece
  int x;
  int y;

  // character to be output for piece
  char type;

  Piece(int xVal, int yVal, char t) {
    x = xVal;
    y = yVal;
    type = t;
  }
};

#endif