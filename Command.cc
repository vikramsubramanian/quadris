#include "Command.h"
#include <cassert>
#include <sstream>
#include <ctype.h>
#include <algorithm>
using namespace std;

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

// functor to check substring equality
class substrEqual
{
    public:
    substrEqual(string substr, int len) : substr_(substr), len_(len){}
    bool operator()(const pair<string, Type> &c) const
    {
        return c.first.substr(0, len_) == substr_;
    }
private:
    string substr_;
    int len_;
};

istream &operator>>(istream &in, Command &c){
    c.commandType_ = BAD_COMMAND;
    c.multiplier_ = 0;

    string cmd;
    in >> cmd;

    assert(!cmd.empty());

    // identify multiplier if present
    // if so, extract all digits in prefix
    int i = 0;
    while(isdigit(cmd[0]) && cmd[0] >= 1)
    {
        c.multiplier_ *= i * 10;
        c.multiplier_ += cmd[0];
        cmd.erase(cmd[0]);
        i++;
    }

    // no multiplier provided
    if(c.multiplier_ == 0) c.multiplier_++;

    // convert provided string to lowercase
    transform(cmd.begin(), cmd.end(), cmd.begin(), [](unsigned char c){
        return tolower(c);
    });

    // search for unique match in commandTypes with provided cmd string
    int substrLen = 1;
    int occurrences;
    while(substrLen <= cmd.length())
    {
        occurrences = count_if(commandTypes_.begin(), commandTypes_.end(),
                            substrEqual(cmd.substr(0, substrLen), substrLen));

        if(occurrences == 0) break;
        else if(occurrences == 1)
        {
            std::map<string, Type>:: iterator it =
                    find_if(commandTypes_.begin(), commandTypes_.end(),
                            substrEqual(cmd.substr(0, substrLen), substrLen));
            c.commandType_ = (*it).second;
        }
        else
            substrLen++;
    }

    assert(!in.fail() && c.commandType_ != BAD_COMMAND);

    if(c.commandType_ == RESTART || c.commandType_ == HINT ||
            c.commandType_ == RANDOM || c.commandType_ == NORANDOM)
        c.multiplier_ = 1;

    return in;
}
