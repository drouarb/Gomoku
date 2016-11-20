//
// Created by greg on 17/11/2016.
//

#ifndef GOMOKU_HTMLWRITER_HH
#define GOMOKU_HTMLWRITER_HH


#include <fstream>
#include <vector>
#include <sstream>

class HTMLWriter {
    std::ofstream *outputFile;
    std::stringstream ss;
public:
    struct element_t {
        std::string style;

    };

    virtual ~HTMLWriter();

    HTMLWriter(const std::string file);

    void writeHeader(std::string title);

    void writeArray(std::vector<std::vector<element_t>> array);

    void writeTitle(std::string title, int level = 1);

    void writeScript(const std::string &js);

    void writeRaw(const std::string &html);

};


#endif //GOMOKU_HTMLWRITER_HH
