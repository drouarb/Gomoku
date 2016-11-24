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
            "    <link href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" rel=\"stylesheet\">\n"
            "\n"
            "\n"
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
