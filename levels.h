#ifndef LEVELS_H_
#define LEVELS_H_
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
#include "direction.h"

enum Direction;

class Level {
    public:
        virtual char nextBlock(std::mt19937&, std::ifstream&, bool) const = 0;
        virtual std::vector<Direction> transform(int, Direction) const = 0;
};

class Level0 : public Level {
    public:
        char nextBlock(std::mt19937&, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
    private:
        char nextBlock_(std::ifstream&) const;
};

class Level1 : public Level {
    public:
        char nextBlock(std::mt19937&, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
    private:
        char nextBlock_(std::mt19937&) const;
};

class Level2 : public Level {
    public:
        char nextBlock(std::mt19937&, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
    private:
        char nextBlock_(std::mt19937&) const;
};

class Level3 : public Level {
    public:
        char nextBlock(std::mt19937&, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
    private:
        char nextBlock_(std::mt19937&) const;
        char nextBlock_(std::ifstream&) const;
};

class Level4 : public Level {
    public:
        char nextBlock(std::mt19937&, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
    private:
        char nextBlock_(std::mt19937&) const;
        char nextBlock_(std::ifstream&) const;
};

#endif
