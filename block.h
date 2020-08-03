#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include "direction.h"
#include "piece.h"

class Block{
    private:
        void _translate(bool, bool);
        void _clockwise();
        bool _inBounds(char board[18][11]);

    protected:
        Block();

    public:
        /* The constructor is protected so that it cannot be instantiated by anything other
        * than its factory. It's not private because subclasses need to call it.
        */
        virtual ~Block() {};
        std::vector<Piece> pieceList;
        int rotateAroundPivot[2];
        int level_;
        void shiftDown(char board[18][11], int clearedRow);
        void transform(Direction);
        bool translate(Direction, char board[18][11]);
    
};

#endif
