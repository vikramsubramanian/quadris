#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include "piece.h"


enum direction { down, left, right, clockwise, counterclockwise };


class Block{

protected:
    Block();

public:
    /* The constructor is protected so that it cannot be instantiated by anything other
	 * than its factory. It's not private because subclasses need to call it.
	 */
    virtual ~Block() {};
    std::vector<Piece> pieceList;
    int rotateAroundPivot[2];
    int level;
    bool translate(direction, char board[18][11]);
};

#endif
