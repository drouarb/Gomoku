//
// Created by greg on 17/11/2016.
//

#ifndef GOMOKU_FILEPARSER_HH
#define GOMOKU_FILEPARSER_HH


#include <fstream>
#include <queue>

class FileParser {

public:
    struct elem {
        uint8_t map[19][19];
        std::vector<std::string *> log;
    };

private:

    std::ifstream *inputFile;
    bool inMap;
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

#endif //GOMOKU_FILEPARSER_HH
