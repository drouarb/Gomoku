#ifndef GOMOKU_HUMAN_HH
#define GOMOKU_HUMAN_HH

#include "IHuman.hh"
#include "IUIHandle.hh"

namespace Players
{
    class Humain : public IHumain
    {
    private:
        std::string name;
        Core::IReferee *referee;
        GUI::IUIHandle *handle;
    public:
        Humain(std::string &Name, GUI::IUIHandle *);

        ~Humain();

        const std::string &getName() const;

        bool play();

        bool init(Core::IReferee *referee);

        bool tryPlay(uint8_t x, uint8_t y);
    };
}
#endif