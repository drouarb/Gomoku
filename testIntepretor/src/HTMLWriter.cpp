//
// Created by greg on 17/11/2016.
//

#include <stdexcept>
#include "HTMLWriter.hh"

void HTMLWriter::writeHeader(std::string title) {
    ss << "<head>\n"
            "    <meta charset=\"utf-8\">\n"
            "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
            "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
            "    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->\n"
            "    <meta name=\"description\" content=\"\">\n"
            "    <meta name=\"author\" content=\"\">\n"
            "    <link rel=\"icon\" href=\"http://getbootstrap.com/favicon.ico\">\n"
            "\n"
            "    <title>" << title << "</title>\n"
            "\n"
            "    <!-- Bootstrap core CSS -->\n"
            "    <link href=\"http://getbootstrap.com/dist/css/bootstrap.min.css\" rel=\"stylesheet\">\n"
            "\n"
            "    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->\n"
            "    <link href=\"http://getbootstrap.com/assets/css/ie10-viewport-bug-workaround.css\" rel=\"stylesheet\">\n"
            "\n"
            "    <!-- Custom styles for this template -->\n"
            "    <link href=\"sticky-footer.css\" rel=\"stylesheet\">\n"
            "\n"
            "    <!-- Just for debugging purposes. Don't actually copy these 2 lines! -->\n"
            "    <!--[if lt IE 9]><script src=\"http://getbootstrap.com/assets/js/ie8-responsive-file-warning.js\"></script><![endif]-->\n"
            "    <script src=\"http://getbootstrap.com/assets/js/ie-emulation-modes-warning.js\"></script>\n"
            "\n"
            "    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->\n"
            "    <!--[if lt IE 9]>\n"
            "      <script src=\"https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js\"></script>\n"
            "      <script src=\"https://oss.maxcdn.com/respond/1.4.2/respond.min.js\"></script>\n"
            "    <![endif]-->\n"
            "  </head>\n"
            "<body>\n"
            "<div class='container-fluid'>\n"
            ""
            ""
            "";
}

void HTMLWriter::writeArray(std::vector<std::vector<HTMLWriter::element_t>> array) {

}

void HTMLWriter::writeTitle(std::string title, int level) {
    if (level > 3) {
        throw std::invalid_argument(std::to_string(level) + " is not a valid");
    }
    ss << "<h" << level << ">" << title << "</h" << level << ">\n";
}

HTMLWriter::HTMLWriter(const std::string path) {
    this->outputFile = new std::ofstream(path);
    if (!this->outputFile->is_open()) {
        throw std::runtime_error("Cannot create " + path);
    }
}

HTMLWriter::~HTMLWriter() {
    ss << "</div>\n</body>";
    *this->outputFile << ss.str();
    this->outputFile->flush();
}

void HTMLWriter::writeScript(const std::string &js) {
    ss << "<script>" << js << "</script>";
}

void HTMLWriter::writeRaw(const std::string &html) {
    ss << html;
}
