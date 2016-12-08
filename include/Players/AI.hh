#ifndef GOMOKU_AI_HH
#define GOMOKU_AI_HH

#include "IAI.hh"

namespace Players
{
    class AIPlayer : public IAI
    {
    private:
        int score = 0;
    public:
        AIPlayer(std::string &name, Team);

        ~AIPlayer();

        const std::string &getName() const;

        bool play();

        bool init(Core::IReferee *referee);

        void setIBoardOperator(Core::BoardOperator *);
        void setScore(int);
        int getScore();

    private:
        std::string name;
        Core::BoardOperator *boardOperator;
        Core::IReferee *referee;
        Team team;
    };
}
#endif
