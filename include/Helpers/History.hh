//
// Created by greg on 13/11/2016.
//

#ifndef GOMOKU_HISTORY_HH
#define GOMOKU_HISTORY_HH


#include <cstdio>
#include <fstream>
#include <Core/Definitions.hpp>

namespace Core {

    class History {

    private:
        std::ofstream *stream;

        History();

    public:
        static void init();
        static History *getInstance();

        virtual ~History();

        static void close();

        void write(int y, int x, const std::string &name);

        void writeFail(int y, int x, const std::string &name);

        void writeWinner(const std::string &name);

        void writeRule(const RuleID id, bool on);
    };
}


#endif //GOMOKU_HISTORY_HH
