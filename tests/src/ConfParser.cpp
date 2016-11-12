//
// Created by greg on 11/11/16.
//

#include <cstdlib>
#include <sstream>
#include <stdlib.h>
#include "ConfParser.hh"


ConfParser::ConfParser(const std::string &path) {
    this->file.open(path, std::ios::in);
    if (!this->file.is_open()) {
        throw std::runtime_error("Cannot find " + path);
    }
    std::string line;

    while (getline(this->file, line)) {
        if (line.length() == 0) {
            continue;
        }
        line_t line1 = line_t(line);
        if (line1.comment) {
            std::cout << "comment" << std::endl;
            continue;
        }
        if (line1.cmd == "put") {
            this->commandList.push(line1);
        }
        if (line1.cmd == "end") {
            this->end = line1;
        }
    }
    this->file.close();
}

ConfParser::line_t ConfParser::getNextPlay() {
    if (this->commandList.size() == 0) {
        throw std::logic_error("No play left");
    }
    line_t line = this->commandList.back();
    this->commandList.pop();
    return line;
}

const ConfParser::line_t &ConfParser::getEnd() const {
    return end;
}

std::ostream &operator<<(std::ostream &ostream, const ConfParser::line_t &line) {
    ostream << "team:" << line.team << ", x: " << static_cast<int>(line.x) << ", y: " << static_cast<int>(line.y) << ", success:" << line.success;
    return ostream;
}

ConfParser::line_t::line_t(std::string toParse) {
    std::stringstream ss;
    ss.str(toParse);
    std::string item;
    std::vector<std::string> splited;

    if (toParse.compare(0, 2, "//") == 0) {
        this->comment = true;
        return;
    }
    while (std::getline(ss, item, ' ')) {
        splited.push_back(item);
    }
    this->cmd = splited[0];
    this->comment = false;
    if (splited.size() < 4) {
        throw std::logic_error("Bad conf file");
    } else {
        if (this->cmd == "put") {
            this->success = (splited[4] == "true");
        }
    }

    this->y = std::atoi(splited[1].c_str());
    this->x = std::atoi(splited[2].c_str());
    this->team = (splited[3] == "white" ? Team::WHITE : (splited[3] == "black" ? Team::BLACK : Team::NOPLAYER));
}

ConfParser::line_t::line_t() {}
