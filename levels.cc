#include "levels.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>

// -------------------------------------------------------------------------------
// Level0

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level0::nextBlock(int seed) const {
    // Should not be called
    std::cerr << "This function is off-limits. It should not be called in the final code." << std::endl;
    return '*';
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level0::nextBlock(std::ifstream file) const {
    char block;
    file >> block;
    return block;
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

// -------------------------------------------------------------------------------
// Level1

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level1::nextBlock(int seed) const {
    static std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double ran = dis(rng);
    if (0 <= ran && ran < (1.0/6.0)) {
        return 'I';
    } else if ((1.0/6.0) <= ran && ran < (2.0/6.0)) {
        return 'J';
    } else if ((2.0/6.0) <= ran && ran < (3.0/6.0)) {
        return 'L';
    } else if ((3.0/6.0) <= ran && ran < (4.0/6.0)) {
        return 'O';
    } else if ((4.0/6.0) <= ran && ran < (9.0/12.0)) {
        return 'S';
    } else if ((9.0/12.0) <= ran && ran < (10.0/12.0)) {
        return 'Z';
    } else {
        return 'T';
    }
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level1::nextBlock(std::ifstream file) const {
    // Should not be called
    std::cerr << "This function is off-limits. It should not be called in the final code." << std::endl;
    return '*';
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Command> Level1::transform(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Command> Level1::drop(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Level2

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level2::nextBlock(int seed) const {
    static std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double ran = dis(rng);
    if (0 <= ran && ran < (1.0/7.0)) {
        return 'I';
    } else if ((1.0/7.0) <= ran && ran < (2.0/7.0)) {
        return 'J';
    } else if ((2.0/7.0) <= ran && ran < (3.0/7.0)) {
        return 'L';
    } else if ((3.0/7.0) <= ran && ran < (4.0/7.0)) {
        return 'O';
    } else if ((4.0/7.0) <= ran && ran < (5.0/7.0)) {
        return 'S';
    } else if ((5.0/7.0) <= ran && ran < (6.0/7.0)) {
        return 'Z';
    } else {
        return 'T';
    }
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level2::nextBlock(std::ifstream file) const {
    // Should not be called
    std::cerr << "This function is off-limits. It should not be called in the final code." << std::endl;
    return '*';
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Command> Level2::transform(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Command> Level2::drop(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Level3

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level3::nextBlock(int seed) const {
    static std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double ran = dis(rng);
    if (0 <= ran && ran < (1.0/9.0)) {
        return 'I';
    } else if ((1.0/9.0) <= ran && ran < (2.0/9.0)) {
        return 'J';
    } else if ((2.0/9.0) <= ran && ran < (1.0/3.0)) {
        return 'L';
    } else if ((1.0/3.0) <= ran && ran < (4.0/9.0)) {
        return 'O';
    } else if ((4.0/9.0) <= ran && ran < (2.0/3.0)) {
        return 'S';
    } else if ((2.0/3.0) <= ran && ran < (8.0/9.0)) {
        return 'Z';
    } else {
        return 'T';
    }
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level3::nextBlock(std::ifstream file) const {
    char block;
    file >> block;
    return block;
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Command> Level3::transform(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Command> Level3::drop(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Level4

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level4::nextBlock(int seed) const {
    static std::mt19937 rng(seed);
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    double ran = dis(rng);
    if (0 <= ran && ran < (1.0/9.0)) {
        return 'I';
    } else if ((1.0/9.0) <= ran && ran < (2.0/9.0)) {
        return 'J';
    } else if ((2.0/9.0) <= ran && ran < (3.0/9.0)) {
        return 'L';
    } else if ((3.0/9.0) <= ran && ran < (4.0/9.0)) {
        return 'O';
    } else if ((4.0/9.0) <= ran && ran < (6.0/9.0)) {
        return 'S';
    } else if ((6.0/9.0) <= ran && ran < (8.0/9.0)) {
        return 'Z';
    } else {
        return 'T';
    }
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level4::nextBlock(std::ifstream file) const {
    char block;
    file >> block;
    return block;
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Command> Level4::transform(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Command> Level4::drop(Command c) const {
    std::vector<Command> commands;
    commands.push_back(c);
    return commands;
}

