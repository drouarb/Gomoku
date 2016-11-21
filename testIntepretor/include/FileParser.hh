//
// Created by greg on 17/11/2016.
//

#ifndef GOMOKU_FILEPARSER_HH
#define GOMOKU_FILEPARSER_HH


#include <fstream>
#include <queue>
#include <map>
#include <ostream>

class FileParser {

public:
    struct pattern_t {
        std::string ref;
        uint16_t length;
        uint16_t startPos;
        uint16_t dir;
        std::string line;

        pattern_t(const std::string line);

    };



    struct elem {
        uint8_t map[19][19];
        std::vector<std::string *> log;
        std::map<std::string, pattern_t *> patterns;
    };


private:

    std::ifstream *inputFile;
    bool inMap = false;
    bool inPattern = false;
    bool inPatternMap = false;
    std::queue<elem *> mapList;

    elem current;

    int line;

public:

    FileParser(const std::string &path);

    elem *getNextMap();


private:
    void parseLine(std::string line);

    void reset();


};

std::ostream &operator<<(std::ostream &, const FileParser::elem &);
std::ostream &operator<<(std::ostream &os, const FileParser::pattern_t &pattern);


#endif //GOMOKU_FILEPARSER_HH
