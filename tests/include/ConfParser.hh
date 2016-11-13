//
// Created by greg on 11/11/16.
//

#ifndef GOMOKU_CONFPARSER_HH
#define GOMOKU_CONFPARSER_HH

#include <string>
#include <iostream>
#include <fstream>
#include <Core/Definitions.hh>
#include <vector>
#include <stack>
#include <queue>

class ConfParser {
public:
    struct line_t {
        bool comment;
        std::string cmd;
        uint8_t y;
        uint8_t x;
        Team team;
        bool success; //! if false, the play must failed

        bool isRule;
        RuleID ruleID;

        line_t(std::string toParse);

        line_t();
    };



private:
    std::ifstream file;

    std::stack<line_t> commandList;

    line_t end;

    std::vector<RuleID> rules;
private:

public:
    ConfParser(const std::string &path);

    line_t getNextPlay();

    const line_t &getEnd() const;

    const std::vector<RuleID> &getRules() const;
};

std::ostream &operator<<(std::ostream &ostream, const ConfParser::line_t &line);


#endif //GOMOKU_CONFPARSER_HH
