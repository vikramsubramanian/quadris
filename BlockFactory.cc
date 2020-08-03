#include "BlockFactory.h"
#include "blockTypes.h"
#include <iostream>
using namespace std;

// Factory DP

Block* BlockFactory::createBlock(char id)
{
    if (factories.find(id) != factories.end())
    {      
        return factories[id]->create();
    }
    else
    {
        return NULL;
    }
}

BlockFactory::~BlockFactory() {}

//static member
std::map<char, BlockFactory *> BlockFactory::factories;

BlockFactoryInitializer::BlockFactoryInitializer()
{
    BlockFactory::factories['T'] = new TBlock::Factory;
    BlockFactory::factories['Z'] = new ZBlock::Factory;
    BlockFactory::factories['S'] = new SBlock::Factory;
    BlockFactory::factories['O'] = new OBlock::Factory;
    BlockFactory::factories['L'] = new LBlock::Factory;
    BlockFactory::factories['J'] = new JBlock::Factory;
    BlockFactory::factories['I'] = new IBlock::Factory;
    BlockFactory::factories['B'] = new BBlock::Factory;
}

BlockFactoryInitializer::~BlockFactoryInitializer()
{
    std::map<char, BlockFactory *>::iterator it =
            BlockFactory::factories.begin();
    while (it != BlockFactory::factories.end())
    {
        delete it++->second;
    }
}

//Static member definition:
BlockFactoryInitializer BlockFactoryInitializer::si;