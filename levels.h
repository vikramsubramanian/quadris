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
        virtual char nextBlock(int) const = 0;
        virtual char nextBlock(std::ifstream&) const = 0;
        virtual std::vector<Direction> transform(Direction) const = 0;
        virtual std::vector<Direction> drop() const = 0;
        virtual std::vector<Direction> drop(bool) const = 0;
};

class Level0 : public Level {
    public:
        char nextBlock(int) const override;
        char nextBlock(std::ifstream&) const override;
        std::vector<Direction> transform(Direction) const override;
        std::vector<Direction> drop() const override;
        std::vector<Direction> drop(bool) const override;
};

class Level1 : public Level {
    public:
        char nextBlock(int) const override;
        char nextBlock(std::ifstream&) const override;
        std::vector<Direction> transform(Direction) const override;
        std::vector<Direction> drop() const override;
        std::vector<Direction> drop(bool) const override;
};

class Level2 : public Level {
    public:
        char nextBlock(int) const override;
        char nextBlock(std::ifstream&) const override;
        std::vector<Direction> transform(Direction) const override;
        std::vector<Direction> drop() const override;
        std::vector<Direction> drop(bool) const override;
};

class Level3 : public Level {
    public:
        char nextBlock(int) const override;
        char nextBlock(std::ifstream&) const override;
        std::vector<Direction> transform(Direction) const override;
        std::vector<Direction> drop() const override;
        std::vector<Direction> drop(bool) const override;
};

class Level4 : public Level {
    public:
        char nextBlock(int) const override;
        char nextBlock(std::ifstream&) const override;
        std::vector<Direction> transform(Direction) const override;
        std::vector<Direction> drop() const override;
        std::vector<Direction> drop(bool) const override;
};

#endif
