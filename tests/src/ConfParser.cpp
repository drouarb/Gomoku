//
// Created by greg on 11/11/16.
//

#include <sstream>
#include "ConfParser.hh"

ConfParser::ConfParser(const std::string &path) {
    this->file.open(path, std::ios::in);
    if (!this->file.is_open()) {
        throw std::runtime_error("Cannot find " + path);
    }
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
    if (splited.size() != 4) {
        throw std::logic_error("Bad conf file");
    }
    this->cmd = splited[0];
    this->y = std::atoi(splited[1].c_str());
    this->x = std::atoi(splited[2].c_str());
    this->team = (splited[3] == "white" ? Team::WHITE : (splited[3] == "black" ? Team::BLACK : Team::NOPLAYER));
}
