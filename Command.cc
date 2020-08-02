#include "Command.h"
#include <cassert>
#include <sstream>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

map <string, Type> commandTypes_ = {{"left", LEFT},
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
                                    {"hint", HINT},
                                    {"rename", RENAME}};

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

    // EOF terminates program
    string cmd;
    if (!(in >> cmd)) {
        c.commandType_ = ENDFILE;
        return in;
    }

    assert(!cmd.empty());

    // identify multiplier if present
    // if so, extract all digits in prefix
    int i = 1;
    while(!cmd.empty() && isdigit(cmd[0]) && cmd[0] >= 0)
    {
        c.multiplier_ *= i;
        c.multiplier_ += cmd[0] - '0';
        cmd.erase(cmd.begin());
        i *= 10;
    }

    // no multiplier provided
    if(i == 1) c.multiplier_++;

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
                            substrEqual(cmd, cmd.length()));
            if(it != commandTypes_.end())
                c.commandType_ = (*it).second;
            break;
        }
        else
            substrLen++;
    }

    // reset multiplier for commands that don't support it
    if(c.commandType_ == RESTART || c.commandType_ == HINT ||
            c.commandType_ == RANDOM || c.commandType_ == NORANDOM)
        c.multiplier_ = 1;

    // update map for rename command
    if(c.commandType_ == RENAME)
    {
        c.multiplier_ = 1;
        vector <string> tokens;
        stringstream renameCmd(cmd);
        string temp;

        while(getline(renameCmd, temp, ' '))
            tokens.push_back(temp);

//        std::map<string, Type>:: iterator it =
//                find_if(commandTypes_.begin(), commandTypes_.end(),
//                        substrEqual(tokens[1], tokens[1].length()));

//        if(it != commandTypes_.end())
//        {
            auto kvp = commandTypes_.find(tokens[1]);
        if(kvp != end(commandTypes_))
            {
            auto const value = move(kvp->second);
            commandTypes_.erase(kvp);
            commandTypes_.insert({tokens[2], std::move(value)});
            }
        //}
    }

    return in;
}
