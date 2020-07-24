#include "levels.h"
#include <fstream>
#include <vector>

// -------------------------------------------------------------------------------
// Level0

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level0::nextBlock(int seed) const {
    return 't';
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level0::nextBlock(std::ifstream file) const {
    return 't';
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Command> Level0::transform(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Command> Level0::drop(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}