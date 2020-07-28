#ifndef _LBLOCK_H_
#define _LBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class LBlock : public Block
{
    LBlock();
    ~LBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        LBlock *create();
        friend class BlockFactoryInitializer;
    };
};

#endif
