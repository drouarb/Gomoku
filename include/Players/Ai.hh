#ifndef GOMOKU_AI_HH
#define GOMOKU_AI_HH

#include "IAi.hh"

namespace Players
{
    class Ai : public IAi
    {
    public:
        Ai(std::string & name);
        virtual ~Ai();
        virtual const std::string &getName() const;
        virtual bool play();
        virtual bool init(Core::IReferee &referee);
        virtual bool tryPlay(uint8_t x, uint8_t y);

    private:
        std::string name;
    };
}
#endif
