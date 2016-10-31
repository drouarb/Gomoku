#ifndef GOMOKU_AI_HH
#define GOMOKU_AI_HH

#include "IAi.hh"

namespace Players
{
    class Ai : public IAi
    {
    public:
        Ai(std::string &name);

        ~Ai();

        const std::string &getName() const;

        bool play();

        bool init(Core::IReferee *referee);

        bool tryPlay(uint8_t x, uint8_t y);

        void setIBoardOperator(Core::IBoardOperator *);

    private:
        std::string name;
        Core::IBoardOperator *boardOperator;
        Core::IReferee *referee;
    };
}
#endif
