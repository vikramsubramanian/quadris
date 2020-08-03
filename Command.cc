#include "Command.h"
#include <cassert>
#include <sstream>
#include <ctype.h>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// map that holds kvp of command string and command type enum
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
                                    {"sequence", SEQUENCE},
                                    {"levelup", LEVELUP},
                                    {"leveldown", LEVELDOWN},
                                    {"restart", RESTART},
                                    {"hint", HINT},
                                    {"playhint", PLAY_HINT},
                                    {"rename", RENAME},
                                    {"force", FORCE},
                                    {"enablebonus", ENABLE_BONUS},
                                    {"disablebonus", DISABLE_BONUS}};

// functor to check substring equality
class substrEqual
{
    public:
    substrEqual(string substr, int len) :
        substr_(substr), len_(len){}
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
    if (!(in >> cmd))
    {
        c.commandType_ = ENDFILE;
        return in;
    }

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

    // no multiplier provided, set to default 1
    if(i == 1) c.multiplier_++;

    // convert provided string to lowercase
    transform(cmd.begin(), cmd.end(), cmd.begin(),
            [](unsigned char c){
        return tolower(c);
    });

    // recognize single letter commands to avoid prefix issues
    if(cmd == "i" || cmd == "j" || cmd == "l" || cmd == "s" ||
        cmd == "z"|| cmd == "o" || cmd == "t")
    {
        c.commandType_ = commandTypes_[cmd];
        return in;
    }

    // search for unique match in commandTypes with provided string
    unsigned int substrLen = 1;
    int occurrences;
    while(substrLen <= cmd.length())
    {
        // occurrences tracks number of matching commands
        // with the current substring
        occurrences = count_if(commandTypes_.begin(),
                commandTypes_.end(),
                substrEqual(cmd.substr(0, substrLen), substrLen));

        if(occurrences == 0) break;
        else if(occurrences == 1)
        {
            // check that the match is actually equal as commands
            // that match a unique prefix aren't necessarily valid
            std::map<string, Type>:: iterator it =
                    find_if(commandTypes_.begin(),
                            commandTypes_.end(),
                            substrEqual(cmd, cmd.length()));
            if(it != commandTypes_.end())
                c.commandType_ = (*it).second;
            break;
        }
        else
            substrLen++;
    }

    // reset multiplier for commands that don't support it
    // and handle bonus enablement
    if(c.commandType_ == RESTART || c.commandType_ == HINT ||
            c.commandType_ == RANDOM || c.commandType_ == NORANDOM ||
            c.commandType_ == SEQUENCE || c.commandType_ == FORCE ||
            c.commandType_ == ENABLE_BONUS ||
            c.commandType_ == DISABLE_BONUS)
    {
        c.multiplier_ = 1;
        if (c.commandType_ == ENABLE_BONUS)
            c.bonusOn_ = true;
        if (c.commandType_ == DISABLE_BONUS)
            c.bonusOn_ = false;
        if(c.commandType_ == RESTART)
            c.resetMap_();
    }

    // update map for rename command if bonus on
    // otherwise, "eat" the tokens after rename
    if(c.commandType_ == RENAME)
    {
        c.multiplier_ = 1;
        string oldCmd, newCmd;
        cin >> oldCmd;
        cin >> newCmd;
        if(c.bonusOn_ == true)
        {
            auto kvp = commandTypes_.find(oldCmd);
            if (kvp != end(commandTypes_))
            {
                auto const value = move(kvp->second);
                commandTypes_.erase(kvp);
                commandTypes_.insert({newCmd, std::move(value)});
            }
        }
        else
        {
            c.commandType_ = BAD_COMMAND;
        }
    }

    if(c.commandType_ == PLAY_HINT && c.bonusOn_ == false)
        c.commandType_ = BAD_COMMAND;

    return in;
}

// reset renamed commands in case of game restart
void Command::resetMap_()
{
    commandTypes_.clear();
    commandTypes_ = {{"left", LEFT},
                     {"right", RIGHT},
                     {"down", DOWN},
                     {"clockwise", CLOCKWISE},
                     {"counterclockwise", COUNTERCLOCKWISE},
                     {"drop", DROP},
                     {"i", I}, {"j", J}, {"l", L}, {"s", S},
                     {"z", Z}, {"o", O}, {"t", T},
                     {"norandom", NORANDOM},
                     {"random", RANDOM},
                     {"sequence", SEQUENCE},
                     {"levelup", LEVELUP},
                     {"leveldown", LEVELDOWN},
                     {"restart", RESTART},
                     {"hint", HINT},
                     {"playhint", PLAY_HINT},
                     {"rename", RENAME},
                     {"force", FORCE},
                     {"enablebonus", ENABLE_BONUS},
                     {"disablebonus", DISABLE_BONUS}};
}