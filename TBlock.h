#ifndef _TBLOCK_H_
#define _TBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class TBlock : public Block
{
    TBlock();
    ~TBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        TBlock *create();
        friend class BlockFactoryInitializer;
    };


};

#endif
