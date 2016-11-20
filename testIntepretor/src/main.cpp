//
// Created by greg on 17/11/2016.
//

#include <algorithm>
#include <string>
#include <iostream>
#include <FileParser.hh>
#include <HTMLWriter.hh>

static const char *htmlBoard = "";

char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}

int     main(int ac, char **av)
{
    if (!cmdOptionExists(av, av + ac, "-i") || !cmdOptionExists(av, av + ac, "-o")) {
        std::cerr << "usage ./" << av[0] << " -i infile -o outfile.html" << std::endl;
        return -1;
    }
    std::string infile = getCmdOption(av, av + ac, "-i");
    std::string outfile = getCmdOption(av, av + ac, "-o");
    FileParser *parser = new FileParser(infile);
    HTMLWriter *writer = new HTMLWriter(outfile);
    writer->writeHeader(infile);
    writer->writeTitle("test");
    
    std::stringstream ss;

    FileParser::elem *pElem = parser->getNextMap();
    ss << "var game = [";
    while (pElem) {
        ss << "{" << *pElem;
        ss << "},";
        pElem = parser->getNextMap();
    }
    ss << "{}";
    ss << "];";

    writer->writeScript(ss.str());
    writer->writeRaw(htmlBoard);

    

    delete (writer);
}