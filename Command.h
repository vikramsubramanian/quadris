#ifndef COMMAND_H
#define COMMAND_H
#include <istream>
#include <map>
#include <string>

enum Type { LEFT, RIGHT, DOWN, CLOCKWISE, COUNTERCLOCKWISE, DROP,
        I, J, L, S, Z, O, T, NORANDOM, RANDOM, SEQUENCE,
        LEVELUP, LEVELDOWN, RESTART, HINT, RENAME, BAD_COMMAND,
        ENABLE_BONUS, DISABLE_BONUS, ENDFILE };

struct Command{
    Type commandType_;
    int multiplier_;
    bool bonusOn_;

    Command() : commandType_(BAD_COMMAND), multiplier_(1),
        bonusOn_(false) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif //PROJECT_2_QUADRIS_COMMAND_H