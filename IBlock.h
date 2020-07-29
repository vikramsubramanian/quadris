#ifndef _IBLOCK_H_
#define _IBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class IBlock : public Block
{
    IBlock();
    ~IBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        IBlock *create();
        friend class BlockFactoryInitializer;
    };
};

#endif
