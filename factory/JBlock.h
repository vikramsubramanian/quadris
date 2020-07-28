#ifndef _JBLOCK_H_
#define _JBLOCK_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

class JBlock : public Block
{
    JBlock();
    ~JBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        JBlock *create();
        friend class BlockFactoryInitializer;
    };

};

#endif
