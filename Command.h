#ifndef COMMAND_H
#define COMMAND_H
#include <istream>
#include <map>
#include <string>

enum Type { LEFT, RIGHT, DOWN, CLOCKWISE, COUNTERCLOCKWISE, DROP,
        I, J, L, S, Z, O, T, NORANDOM, RANDOM, LEVELUP, LEVELDOWN,
        RESTART, HINT, BAD_COMMAND, ENDFILE };

struct Command{
    Type commandType_;
    int multiplier_;

    Command() : commandType_(BAD_COMMAND), multiplier_(1) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif //PROJECT_2_QUADRIS_COMMAND_H
