#include "BlockFactory.h"
#include "TBlock.h"
#include "ZBlock.h"
#include "SBlock.h"
#include "OBlock.h"
#include "LBlock.h"
#include "JBlock.h"
#include "IBlock.h"

using namespace std;

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
}

//Static member defination:
BlockFactoryInitializer BlockFactoryInitializer::si;