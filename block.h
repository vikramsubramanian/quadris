#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include "direction.h"
#include "piece.h"

// Factory DP

class Block{
    private:
        void _translate(bool, bool);
        void _clockwise();
        void _transform(Direction);
        bool _inBounds(char board[18][11]);

    protected:
    // The constructor is protected so that it cannot
    // be instantiated by anything other than its factory.
        Block();

    public:
        virtual ~Block() {};
        std::vector<Piece> pieceList;
        int level_;
        void shiftDown(char board[18][11], int clearedRow);
        bool translate(Direction, char board[18][11]);
    
};

#endif