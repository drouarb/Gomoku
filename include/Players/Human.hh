#ifndef GOMOKU_HUMAN_HH
#define GOMOKU_HUMAN_HH

#include "IHuman.hh"

namespace Players
{
    class Humain : public IHumain
    {
    private:
        std::string name;
        Core::IReferee *referee;
    public:
        Humain(std::string & Name);
        virtual ~Humain();
        virtual const std::string &getName() const;
        virtual bool play();
        virtual bool init(Core::IReferee & referee);
        virtual bool tryPlay(uint8_t x, uint8_t y);
    };
}
#endif