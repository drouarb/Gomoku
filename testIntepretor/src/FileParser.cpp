//
// Created by greg on 17/11/2016.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include "FileParser.hh"

FileParser::FileParser(const std::string &path) : inMap(false) {
    this->inputFile = new std::ifstream(path);
    if (!this->inputFile->is_open()) {
        throw std::runtime_error("Cannot open " + path);
    }
    this->reset();
    std::string line;
    while (std::getline(*this->inputFile, line)) {
        this->parseLine(line);
    }
}

FileParser::elem *FileParser::getNextMap() {
    elem *&pElem = this->mapList.front();
    this->mapList.pop();
    return pElem;
}

void FileParser::parseLine(std::string line) {
    std::string s(line);

    if (line.find("MAP BEGIN") != std::string::npos) {
        this->inMap = true;
        return;
    }
    if (line.find("MAP END") != std::string::npos) {
        this->inMap = false;
        this->reset();
        return;
    }

    if (inMap) {
        if (this->line == 0) {
            this->line++;
            return;
        }
        while (s.find("  ") != std::string::npos) {
            s.replace(s.find("  "), 2, " ");
        }
        std::istringstream split(s);
        std::vector<std::string> tokens;
//        std::cout << "line: " << s << std::endl;
        for (std::string each; std::getline(split, each, ' '); tokens.push_back(each)) {
//            std::cout << "each: " << each << std::endl;
        }
        for (int i = 1; i < tokens.size() && i < 19; ++i) {
            this->current.map[this->line - 1][i - 1] = static_cast<uint8_t >(std::stoi(tokens[i]));
        }
        this->line++;
        return;
    }

    this->current.log.push_back(new std::string(line));
}

void FileParser::reset() {
    this->mapList.push(new elem(this->current));
    this->line = 0;
    memset(&this->current, 0, sizeof(this->current));
}

std::ostream &operator<<(std::ostream &s, const FileParser::elem &e) {
    s << "map: [" << std::endl;
    for (int i = 0; i < 19; ++i) {
        s << "[";
        for (int j = 0; j < 19; ++j) {
            s << static_cast<int>(e.map[i][j]) << (j < 18 ? ", " : "");
        }
        s << "]" << (i < 18 ? ", " : "") << std::endl;
    }
    s << "], "
            "log: ["
            "" << std::endl;
    for (std::string *l : e.log) {
        s << "\"" << *l << "\", " << std::endl;
    }
    s << "\"\"]";
    return s;
}