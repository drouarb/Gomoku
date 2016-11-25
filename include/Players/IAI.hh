#ifndef GOMOKU_IAI_HH
#define GOMOKU_IAI_HH

#include "IPlayer.hh"

namespace Players
{
    class IAI : public IPlayer
    {
    public:
        virtual ~IAI(){};
        virtual const std::string &getName() const  = 0;
        virtual bool play() = 0;
        virtual bool init(Core::IReferee *referee) = 0;
    };
}
#endif
