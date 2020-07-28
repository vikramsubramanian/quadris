#ifndef _BLOCKFACTORY_H_
#define _BLOCKFACTORY_H_

#include "block.h"
#include "piece.h"

#include <map>


class BlockFactory
{
public:
    virtual ~BlockFactory() {}
    friend class BlockFactoryInitializer;
    static Block *createBlock(char);

private:
    virtual Block *create() = 0; //Factory Method
    static std::map<char, BlockFactory *> factories;
};

class BlockFactoryInitializer
{
    static BlockFactoryInitializer si;
    BlockFactoryInitializer();
    BlockFactoryInitializer(const BlockFactoryInitializer &);
};
#endif
