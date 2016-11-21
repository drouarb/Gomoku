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

    writer->writeRaw("<div class=\"\">\n"
                             "    <div class=\"row\">\n"
                             "        <div class=\"col-md-5\"></div>\n"
                             "        <div class=\"col-md-3\">\n"
                             "            <button class=\"btn btn-default\" onclick=\"toto = (toto > 0 ? toto -1 : 0); e()\">Prev</button>\n"
                             "            <button class=\"btn btn-default\" onclick=\"toto = (toto < game.length - 2 ? toto + 1 : game.length - 2); e()\">Next</button>\n"
                             "        </div>\n"
                             "    </div>\n"
                             "    <br>\n"
                             "    <br>\n"
                             "    <div class=\"row\">\n"
                             "        <div class=\"col-md-5\">\n"
                             "            <canvas style=\"border:1px solid #000000;\" id=\"myCanvas\" width=\"810\" height=\"810\"></canvas>\n"
                             "        </div>\n"
                             "    </div>\n"
                             "\n"
                             "</div>");
    writer->writeScript(ss.str());
    writer->writeScript("/**\n"
                                " * Created by greg on 21/11/2016.\n"
                                " */\n"
                                "\n"
                                "var c = document.getElementById(\"myCanvas\");\n"
                                "var ctx = c.getContext(\"2d\");\n"
                                "var toto = 0;\n"
                                "\n"
                                "\n"
                                "const numbershift = 45;\n"
                                "\n"
                                "\n"
                                "function put(x, y, color) {\n"
                                "//    ctx.rect(,  - 20, 40, 40);\n"
                                "    ctx.fillStyle = color;\n"
                                "    ctx.borderStyle = color;\n"
                                "    ctx.beginPath();\n"
                                "    ctx.arc(x * numbershift, y * numbershift, 20, 0, 2 * Math.PI);\n"
                                "    ctx.fill();\n"
                                "    ctx.stroke();\n"
                                "    ctx.fillStyle = 'black';\n"
                                "}\n"
                                "\n"
                                "function e() {\n"
                                "    ctx.clearRect(0, 0, 2000, 2000);\n"
                                "\n"
                                "    for (var j = 0; j < 19; ++j) {\n"
                                "        ctx.moveTo(j * numbershift, 0);\n"
                                "        ctx.lineTo(j * numbershift, 1900);\n"
                                "        ctx.stroke();\n"
                                "    }\n"
                                "\n"
                                "    for (var j = 0; j < 19; ++j) {\n"
                                "        ctx.moveTo(0, j * numbershift);\n"
                                "        ctx.lineTo(1900, j * numbershift);\n"
                                "        ctx.stroke();\n"
                                "    }\n"
                                "    for (var y = 0; y < 19; y++) {\n"
                                "        for (var x = 0; x < 19; x++) {\n"
                                "            if (game[toto].map[y][x] != 0) {\n"
                                "                put(x, y, (game[toto].map[y][x] == 1 ? 'black' : 'white'));\n"
                                "            }\n"
                                "        }\n"
                                "    }\n"
                                "    ctx.fill();\n"
                                "    return;\n"
                                "}\n"
                                "\n"
                                "e();");
    writer->writeRaw(htmlBoard);

    

    delete (writer);
}