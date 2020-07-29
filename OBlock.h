#ifndef _OBLOCK_H_
#define _OBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class OBlock : public Block
{
    OBlock();
    ~OBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        OBlock *create();
        friend class BlockFactoryInitializer;
    };
};

#endif
