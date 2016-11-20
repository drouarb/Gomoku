//
// Created by greg on 13/11/2016.
//

#include <ctime>
#include <string>
#include "Helpers/History.hh"

using namespace Core;

static History *history = nullptr;

History *History::getInstance() {
    if (history == NULL) {
        history = new History();
    }
    return history;
}

History::History() {
    time_t i = time(NULL);
    std::string filename(std::to_string(i) + std::string(".log"));
    struct tm * now = localtime( &i);


    this->stream = new std::ofstream(filename, std::ios::out | std::ios::trunc);
    (*this->stream) << "//Play started the ";
    (*this->stream) << (now->tm_year + 1900) << '-'
                 << (now->tm_mon + 1) << '-'
                 <<  now->tm_mday
                 << std::endl;
}

void History::close() {
    History *pHistory = History::getInstance();
    if (pHistory == NULL) {
        return;
    }
    history = NULL;
    delete pHistory;
}

void History::write(int y, int x, const std::string &name) {
    if (name == "White player") {
        (*this->stream) << "put " << y << " " << x << " " << "white true" << std::endl;
    }
    if (name == "Black player") {
        (*this->stream) << "put " << y << " " << x << " " << "black true" << std::endl;
    }
}

void History::init() {
    history = NULL;
    History::getInstance();
}

void History::writeFail(int y, int x, const std::string &name) {
    if (name == "White player") {
        (*this->stream) << "put " << y << " " << x << " " << "white false" << std::endl;
    }
    if (name == "Black player") {
        (*this->stream) << "put " << y << " " << x << " " << "black false" << std::endl;
    }
}

History::~History() {
    delete (this->stream);
}

void History::writeWinner(const std::string &name) {
    if (name.find("hite") != std::string::npos) {
        (*this->stream) << "end " << 0 << " " << 0 << " " << "white" << std::endl;
        return;
    }
    if (name.find("lac") != std::string::npos) {
        (*this->stream) << "end " << 0 << " " << 0 << " " << "black" << std::endl;
        return;
    }
    (*this->stream) << "end " << 0 << " " << 0 << " " << "noone" << std::endl;
}

void History::writeRule(const RuleID id, bool on) {
    if (on)
        (*this->stream) << "set " << static_cast<int>(id) << std::endl;
    else
        (*this->stream) << "unset " << static_cast<int>(id) << std::endl;
}