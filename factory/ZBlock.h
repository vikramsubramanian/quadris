#ifndef _ZBLOCK_H_
#define _ZBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class ZBlock : public Block
{
    ZBlock();
    ~ZBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        ZBlock *create();
        friend class BlockFactoryInitializer;
    };
};

#endif
