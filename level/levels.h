#ifndef LEVELS_H_
#define LEVELS_H_
#include <fstream>
#include <vector>

enum Command { CLUB, DIAMOND, HEART, SPADE, SUIT_COUNT };

class Level {
    public:
        virtual char nextBlock(int) const = 0;
        virtual char nextBlock(std::ifstream) const = 0;
        virtual std::vector<Command> transform(Command) const = 0;
        virtual std::vector<Command> drop(Command) const = 0;
};

class Level0 : public Level {
    public:
        char nextBlock(int) const override;
        char nextBlock(std::ifstream) const override;
        std::vector<Command> transform(Command) const override;
        std::vector<Command> drop(Command) const override;
};

#endif
