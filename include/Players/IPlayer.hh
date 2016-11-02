#ifndef  GOMOKU_IPLAYER_HH
#define  GOMOKU_IPLAYER_HH

#include <iostream>
#include "IReferee.hh"
namespace Players
{
    class IPlayer
    {
    public:
        virtual ~IPlayer(){};
        virtual const std::string &getName() const  = 0;
        virtual bool play() = 0;
        virtual bool init(Core::IReferee *referee) = 0;
    };
}
#endif