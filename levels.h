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
        virtual char nextBlock(int, std::ifstream&, bool) const = 0;
        virtual std::vector<Direction> transform(int, Direction) const = 0;
        virtual std::vector<Direction> drop(bool) const = 0;
};

class Level0 : public Level {
    public:
        char nextBlock(int, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
        std::vector<Direction> drop(bool) const override;
    private:
        char nextBlock_(std::ifstream&) const;
};

class Level1 : public Level {
    public:
        char nextBlock(int, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
        std::vector<Direction> drop(bool) const override;
    private:
        char nextBlock_(int) const;
};

class Level2 : public Level {
    public:
        char nextBlock(int, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
        std::vector<Direction> drop(bool) const override;
    private:
        char nextBlock_(int) const;
};

class Level3 : public Level {
    public:
        char nextBlock(int, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
        std::vector<Direction> drop(bool) const override;
    private:
        char nextBlock_(int) const;
        char nextBlock_(std::ifstream&) const;
};

class Level4 : public Level {
    public:
        char nextBlock(int, std::ifstream&, bool) const override;
        std::vector<Direction> transform(int, Direction) const override;
        std::vector<Direction> drop(bool) const override;
    private:
        char nextBlock_(int) const;
        char nextBlock_(std::ifstream&) const;
};

#endif
