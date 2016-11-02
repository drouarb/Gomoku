#ifndef GOMOKU_IHUMAN_HH
#define GOMOKU_IHUMAN_HH

#include "IPlayer.hh"

namespace Players
{
    class IHumain : public IPlayer
    {
    public:
        virtual ~IHumain(){};
        virtual const std::string &getName() const  = 0;
        virtual bool play() = 0;
        virtual bool init(Core::IReferee *referee) = 0;
        virtual bool tryPlay(uint8_t x, uint8_t y) = 0;
        virtual int getScore() = 0;
        virtual  void setScore(int) = 0;
    };
}
#endif