#ifndef COMMAND_H
#define COMMAND_H
#include <istream>
#include <map>
#include <string>

enum Type { LEFT, RIGHT, DOWN, CLOCKWISE, COUNTERCLOCKWISE, DROP,
        I, J, L, S, Z, O, T, NORANDOM, RANDOM, LEVELUP, LEVELDOWN,
        RESTART, HINT, BAD_COMMAND };

std::map <std::string, Type> commandTypes_ = {{"left", LEFT},
                                        {"right", RIGHT},
                                        {"down", DOWN},
                                        {"clockwise", CLOCKWISE},
                                        {"counterclockwise", COUNTERCLOCKWISE},
                                        {"drop", DROP},
                                        {"i", I}, {"j", J}, {"l", L}, {"s", S},
                                        {"z", Z}, {"o", O}, {"t", T},
                                        {"norandom", NORANDOM},
                                        {"random", RANDOM},
                                        {"levelup", LEVELUP},
                                        {"leveldown", LEVELDOWN},
                                        {"restart", RESTART},
                                        {"hint", HINT}};

struct Command{
    Type commandType_;
    int multiplier_;

    Command() : commandType_(BAD_COMMAND), multiplier_(1) {}
};

std::istream &operator>>(std::istream &, Command &);

#endif //PROJECT_2_QUADRIS_COMMAND_H
