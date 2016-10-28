#ifndef GOMOKU_AI_HH
#define GOMOKU_AI_HH

#include "IAi.hh"

namespace Players
{
    class Ai : public IAi
    {

        virtual ~Ai();
        virtual const std::string &getName();
        virtual bool play();
        virtual bool init(Core::IReferee &referee);
        virtual bool tryPlay(uint8_t x, uint8_t y);
    };
}
#endif
