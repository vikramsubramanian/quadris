#ifndef _SBLOCK_H_
#define _SBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class SBlock : public Block
{
    SBlock();
    ~SBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        SBlock *create();
        friend class BlockFactoryInitializer;
    };

};

#endif
