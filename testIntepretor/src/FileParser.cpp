//
// Created by greg on 17/11/2016.
//

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <regex>
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
    if (this->mapList.size() == 0) {
        return NULL;
    }
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

    if (line.find("-- PATTERNS") != std::string::npos) {
        this->inPattern = true;
        return;
    }

    if (this->inPattern) {
        if (line.find("-- MAP") != std::string::npos) {
            this->inPattern = false;
            this->inPatternMap = true;
            return;
        }
        pattern_t *pattern = new pattern_t(line);
        this->current.patterns[pattern->ref] = pattern;
        std::cout << *pattern << std::endl;
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
        for (std::string each; std::getline(split, each, ' '); tokens.push_back(each)) {
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
    this->current.patterns = std::map<std::string, pattern_t *>();
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
    s << "], \n"
            "patterns: [";

    for (auto pair : e.patterns) {
        s << "{" << *pair.second << "}";
        s << ", ";
    }
    s << "{}], \n";

    s << "log: ["
            "" << std::endl;
    for (std::string *l : e.log) {
        s << "\"" << *l << "\", " << std::endl;
    }
    s << "\"\"]";
    return s;
}

int atoi(const char *);

FileParser::pattern_t::pattern_t(const std::string line) {
    std::regex ref("^0x([0-9a-f])+");
    std::regex length("length=\\d+");
    std::regex startPos("startPos=\\d+");
    std::regex dir("dir=\\d+");
    std::regex l("line=\\d+");

    std::smatch match;

    std::regex_search(line.begin(), line.end(), match, ref);
    this->ref = match.str();
    std::regex_search(line.begin(), line.end(), match, length);
    this->length = std::atoi(match.str().c_str() + 7);
    std::regex_search(line.begin(), line.end(), match, startPos);
    this->startPos = std::atoi(match.str().c_str() + 9);
    std::regex_search(line.begin(), line.end(), match, dir);
    this->dir = std::atoi(match.str().c_str() + 4);
    std::regex_search(line.begin(), line.end(), match, l);
    this->line = match.str().c_str() + 5;
}

std::ostream &operator<<(std::ostream &os, const FileParser::pattern_t &pattern) {
    os << "ref: \"" << pattern.ref << "\", length: " << pattern.length << ", startPos: " << pattern.startPos
       << ", dir: "
       << pattern.dir << ", line: \"" << pattern.line << "\"";
    return os;
}
