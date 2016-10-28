#ifndef GOMOKU_IAI_HH
#define GOMOKU_IAI_HH

#include "IPlayer.hh"

namespace Players
{
    class IAi : public IPlayers
    {
    public:
        virtual ~IAi(){};
        virtual const std::string &getName() const  = 0;
        virtual bool play() = 0;
        virtual bool init(Core::IReferee &referee) = 0;
        virtual bool tryPlay(uint8_t x, uint8_t y) = 0;
    };
}
#endif
