//
// Created by greg on 17/11/2016.
//

#include <algorithm>
#include <string>
#include <iostream>
#include <FileParser.hh>
#include <HTMLWriter.hh>

static const char *htmlBoard = "";

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

int main(int ac, char **av) {
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

    writer->writeRaw("    <div class=\"\">\n"
                             "        <div class=\"row\">\n"
                             "            <div class=\"col-md-5\"></div>\n"
                             "            <div class=\"col-md-3\">\n"
                             "                <button class=\"btn btn-default\" onclick=\"toto = (toto > 0 ? toto -1 : 0); load()\">Prev</button>\n"
                             "                <button class=\"btn btn-default\"\n"
                             "                        onclick=\"toto = (toto < game.length - 2 ? toto + 1 : game.length - 2); load()\">\n"
                             "                    Next\n"
                             "                </button>\n"
                             "            </div>\n"
                             "        </div>\n"
                             "        <br>\n"
                             "        <br>\n"
                             "        <div class=\"row\">\n"
                             "            <div class=\"col-md-5\">\n"
                             "                <canvas style=\"border:1px solid #000000;\" id=\"myCanvas\" width=\"700\" height=\"700\"></canvas>\n"
                             "            </div>\n"
                             "            <div class=\"col-md-5\">\n"
                             "                <canvas style=\"border:1px solid #000000;\" id=\"patternCanvas\" width=\"700\" height=\"700\"></canvas>\n"
                             "            </div>\n"
                             "            <div class=\"col-md-2\" id=\"checkList\">\n"
                             "            </div>\n"
                             "        </div>\n"
                             "        <p id=\"log\"></p>\n"
                             "\n"
                             "    </div>");
    writer->writeScript(ss.str());
    writer->writeScript("/**\n"
                                " * Created by greg on 21/11/2016.\n"
                                " */\n"
                                "\n"
                                "var c = document.getElementById(\"myCanvas\");\n"
                                "var c_pattern = document.getElementById(\"patternCanvas\");\n"
                                "var ctx = c.getContext(\"2d\");\n"
                                "var ctx_pattern = c_pattern.getContext(\"2d\");\n"
                                "var toto = 1;\n"
                                "var log = document.getElementById(\"log\");\n"
                                "var currentPatterns = null;\n"
                                "\n"
                                "\n"
                                "const numbershift = 37;\n"
                                "\n"
                                "\n"
                                "function put(ctx, x, y, color) {\n"
                                "//    ctx.rect(,  - 20, 40, 40);\n"
                                "    ctx.lineWidth = 1;\n"
                                "    ctx.strokeStyle = '#000000';\n"
                                "    ctx.fillStyle = color;\n"
                                "    ctx.borderStyle = color;\n"
                                "    ctx.beginPath();\n"
                                "    ctx.arc(x * numbershift, y * numbershift, 15, 0, 2 * Math.PI);\n"
                                "    ctx.fill();\n"
                                "    ctx.stroke();\n"
                                "    ctx.fillStyle = 'black';\n"
                                "}\n"
                                "\n"
                                "function e(ctx) {\n"
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
                                "\n"
                                "    ctx.fill();\n"
                                "    log.innerHTML = \"\";\n"
                                "    var r = \"\";\n"
                                "    for (var i = 0; i < game[toto - 1].log.length; ++i) {\n"
                                "        r += game[toto - 1].log[i] + \"<br>\";\n"
                                "    }\n"
                                "    log.innerHTML = r;\n"
                                "    return;\n"
                                "}\n"
                                "\n"
                                "function fill(ctx) {\n"
                                "    for (var y = 0; y < 19; y++) {\n"
                                "        for (var x = 0; x < 19; x++) {\n"
                                "            if (game[toto].map[y][x] != 0) {\n"
                                "                put(ctx, x, y, (game[toto].map[y][x] == 1 ? 'white' : 'black'));\n"
                                "            }\n"
                                "        }\n"
                                "    }\n"
                                "}\n"
                                "\n"
                                "function fillPattern(ctx) {\n"
                                "\n"
                                "    var c = false;\n"
                                "\n"
                                "    if (toto == 0) {\n"
                                "        return;\n"
                                "    }\n"
                                "\n"
                                "    if (toto > 0) {\n"
                                "        toto--;\n"
                                "        c = true;\n"
                                "    }\n"
                                "\n"
                                "\n"
                                "    function getPos(startPos) {\n"
                                "        var y = parseInt(startPos / 21 - 1);\n"
                                "        var x = parseInt(startPos % 21 + 1);\n"
                                "        return {y: y, x: x};\n"
                                "    }\n"
                                "\n"
                                "    function getNextPos(current, dir) {\n"
                                "        if (dir < 0) {\n"
                                "            throw \"problem dir = \" + dir;\n"
                                "        }\n"
                                "        switch (dir) {\n"
                                "            case 1:\n"
                                "                return {y: current.y, x: current.x + 1};\n"
                                "            case 21:\n"
                                "                return {y: current.y + 1, x: current.x};\n"
                                "            case 20:\n"
                                "                return {y: current.y + 1, x: current.x - 1};\n"
                                "            case 22:\n"
                                "                return {y: current.y + 1, x: current.x + 1};\n"
                                "        }\n"
                                "        if (dir < 0) {\n"
                                "            throw \"problem dir = \" + dir;\n"
                                "        }\n"
                                "    }\n"
                                "\n"
                                "    function generatePos(pattern) {\n"
                                "        var res = [];\n"
                                "        var pos = getPos(pattern.startPos);\n"
                                "        for (var i = 0; i < pattern.length; ++i) {\n"
                                "            /*if (pattern[i].enable == false) {\n"
                                "             continue;\n"
                                "             }*/\n"
                                "            var c = pattern.line.charAt(i);\n"
                                "            var color;\n"
                                "            if (c == '0') {\n"
                                "                color = 'red'\n"
                                "            }\n"
                                "            if (c == '1') {\n"
                                "                color = 'white';\n"
                                "            }\n"
                                "            if (c == '2') {\n"
                                "                color = 'black';\n"
                                "            }\n"
                                "            res.push({x: pos.x, y: pos.y, color: color});\n"
                                "            pos = getNextPos(pos, pattern.dir);\n"
                                "        }\n"
                                "        return res;\n"
                                "    }\n"
                                "\n"
                                "    var turn = currentPatterns;\n"
                                "\n"
                                "    for (var i = 0; i < turn.length - 1; ++i) {\n"
                                "        ctx.strokeStyle = '#000000';\n"
                                "        if (turn[i].enable == false) {\n"
                                "            continue;\n"
                                "        }\n"
                                "        var res = generatePos(turn[i]);\n"
                                "        for (var j = 0; j < res.length; ++j) {\n"
                                "            ctx.strokeStyle = '#000000';\n"
                                "            put(ctx, res[j].x, res[j].y, res[j].color);\n"
                                "        }\n"
                                "        ctx.stroke();\n"
                                "        ctx.moveTo(res[0].x * (710 / 19) - 3, res[0].y * (710 / 19) - 3);\n"
                                "        ctx.lineTo(res[res.length - 1].x * (710 / 19) - 3, res[res.length - 1].y * (710 / 19) - 3);\n"
                                "        ctx.lineWidth = 3;\n"
                                "        ctx.strokeStyle = '#0000ff';\n"
                                "        ctx.stroke();\n"
                                "        ctx.lineWidth = 1;\n"
                                "        ctx.strokeStyle = '#000000';\n"
                                "    }\n"
                                "    ctx.lineWidth = 1;\n"
                                "    ctx.strokeStyle = '#000000';\n"
                                "\n"
                                "    if (c) {\n"
                                "        toto++;\n"
                                "    }\n"
                                "\n"
                                "}\n"
                                "\n"
                                "function addPatternCheckBox(patterns) {\n"
                                "    var res = \"<form class='form-horizontal'>\"\n"
                                "    for (var i = 0; i < patterns.length - 1; ++i) {\n"
                                "        currentPatterns[i].enable = true;\n"
                                "        res += '<div class=\"form-group\">' +\n"
                                "            '<div class=\"col-sm-offset-2 col-sm-10\">' +\n"
                                "            '<div class=\"checkbox\">' +\n"
                                "            '<label>' +\n"
                                "            '<input type=\"checkbox\" checked=\"checked\" onchange=\"currentPatterns[' + i + '].enable = !currentPatterns[' + i + '].enable;     e(ctx_pattern); fillPattern(ctx_pattern);\">' + patterns[i].line +\n"
                                "            '</label>' +\n"
                                "            '</div>' +\n"
                                "            '</div>' +\n"
                                "            '</div>'\n"
                                "    }\n"
                                "    res += \"</form>\";\n"
                                "    var elementById = document.getElementById('checkList');\n"
                                "    elementById.innerHTML = res;\n"
                                "}\n"
                                "\n"
                                "function load() {\n"
                                "    e(ctx);\n"
                                "    fill(ctx);\n"
                                "    e(ctx_pattern);\n"
                                "    currentPatterns = game[toto - 1].patterns;\n"
                                "    addPatternCheckBox(currentPatterns);\n"
                                "    fillPattern(ctx_pattern);\n"
                                "}\n"
                                "\n"
                                "load();");
    writer->writeRaw(htmlBoard);


    delete (writer);
}