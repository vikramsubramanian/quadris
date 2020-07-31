#include "levels.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include "direction.h"

// -------------------------------------------------------------------------------
// Level0

// -------------------------------------------------------------------------------
// Next Block Decider
char Level0::nextBlock(int seed, std::ifstream& file, bool flag) const {
    char block;
    block = nextBlock_(file);
    return block;
}

// -------------------------------------------------------------------------------
// Next Block Decider (β)
char Level0::nextBlock_(std::ifstream& file) const {
    char block;
    if (!(file >> block)) {
        file.clear();
        file.seekg(std::ios::beg);
        file >> block;
    }
    return block;
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Direction> Level0::transform(Direction c) const {
    std::vector<Direction> Directions;
    Directions.push_back(c);
    return Directions;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Direction> Level0::drop(bool flag) const {
    std::vector<Direction> Directions;
    Directions.push_back(Direction::drop);
    return Directions;
}

// -------------------------------------------------------------------------------
// Level1

// -------------------------------------------------------------------------------
// Next Block Decider
char Level1::nextBlock(int seed, std::ifstream& file, bool flag) const {
    char block;
    block = nextBlock_(seed);
    return block;
}

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level1::nextBlock_(int seed) const {
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
// Transformer
std::vector<Direction> Level1::transform(Direction c) const {
    std::vector<Direction> Directions;
    Directions.push_back(c);
    return Directions;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Direction> Level1::drop(bool flag) const {
    std::vector<Direction> Directions;
    Directions.push_back(Direction::drop);
    return Directions;
}

// -------------------------------------------------------------------------------
// Level2

// -------------------------------------------------------------------------------
// Next Block Decider
char Level2::nextBlock(int seed, std::ifstream& file, bool flag) const {
    char block;
    block = nextBlock_(seed);
    return block;
}

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level2::nextBlock_(int seed) const {
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
// Transformer
std::vector<Direction> Level2::transform(Direction c) const {
    std::vector<Direction> Directions;
    Directions.push_back(c);
    return Directions;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Direction> Level2::drop(bool flag) const {
    std::vector<Direction> Directions;
    Directions.push_back(Direction::drop);
    return Directions;
}

// -------------------------------------------------------------------------------
// Level3

// -------------------------------------------------------------------------------
// Next Block Decider
char Level3::nextBlock(int seed, std::ifstream& file, bool random) const {
    char block;
    if (random) {
        block = nextBlock_(seed);
    } else {
        block = nextBlock_(file);
    }
    return block;
}


// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level3::nextBlock_(int seed) const {
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
char Level3::nextBlock_(std::ifstream& file) const {
    char block;
    if (!(file >> block)) {
        file.clear();
        file.seekg(std::ios::beg);
        file >> block;
    }
    return block;
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Direction> Level3::transform(Direction c) const {
    std::vector<Direction> Directions;
    Directions.push_back(c);
    Directions.push_back(Direction::down);
    return Directions;
}

// -------------------------------------------------------------------------------
// Dropper
std::vector<Direction> Level3::drop(bool flag) const {
    std::vector<Direction> Directions;
    Directions.push_back(Direction::drop);
    return Directions;
}


// -------------------------------------------------------------------------------
// Level4

// -------------------------------------------------------------------------------
// Next Block Decider
char Level4::nextBlock(int seed, std::ifstream& file, bool random) const {
    char block;
    if (random) {
        block = nextBlock_(seed);
    } else {
        block = nextBlock_(file);
    }
    return block;
}

// -------------------------------------------------------------------------------
// Next Block Decider (α)
char Level4::nextBlock_(int seed) const {
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
char Level4::nextBlock_(std::ifstream& file) const {
    char block;
    if (!(file >> block)) {
        file.clear();
        file.seekg(std::ios::beg);
        file >> block;
    }
    return block;
}

// -------------------------------------------------------------------------------
// Transformer
std::vector<Direction> Level4::transform(Direction c) const {
    std::vector<Direction> Directions;
    Directions.push_back(c);
    Directions.push_back(Direction::down);
    return Directions;
}

// -------------------------------------------------------------------------------
// Dropper
// flag represents whether a row has been cleared in the past between the last multiple of 5 turns (between 0 and 5, betwen 5 and 10, etc.)
std::vector<Direction> Level4::drop(bool flag) const {
    std::vector<Direction> Directions;
    Directions.push_back(Direction::drop);
    if (flag) {
        // Needs to send back a create block Direction with a b char
        // Also needs to drop that block
    }
    return Directions;
}


