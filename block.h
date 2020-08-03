#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include "direction.h"
#include "piece.h"

class Block{


public:
    /* The constructor is protected so that it cannot be instantiated by anything other
	 * than its factory. It's not private because subclasses need to call it.
	 */
    virtual ~Block() {};
    std::vector<Piece> pieceList;
    int rotateAroundPivot[2];
    int level;
    void shiftDown(char board[18][11], int clearedRow);
    bool translate(Direction, char board[18][11]);

protected:
    Block();
    
private:
    bool inBounds_(newX, newY, board);
    bool translateLeft_(char board[18][11]);
    bool translateRight_(char board[18][11]);
    bool translateDown_(char board[18][11]);
    bool rotateClockwise_(char board[18][11]);
    bool translateCounterclockwise_(char board[18][11]);
};

#endif
