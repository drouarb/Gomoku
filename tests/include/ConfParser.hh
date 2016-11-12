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

class ConfParser {
public:
    struct line_t {
        bool comment;
        std::string cmd;
        int y;
        int x;
        Team team;
        bool success; //! if false, the play must failed

        line_t(std::string toParse);
    };


private:
    std::ifstream file;

    std::stack<line_t> commandList;

private:

public:
    ConfParser(const std::string &path);
};


#endif //GOMOKU_CONFPARSER_HH
