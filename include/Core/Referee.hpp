#ifndef REFEREE_HH_
# define REFEREE_HH_

#include <vector>
#include <tuple>
#include <map>
#include "Definitions.hh"
#include "IReferee.hh"
#include "IBoardOperator.hh"
#include "BoardOperator.hh"

#define EATWIN 5

namespace Core
{

  struct	statPlayer
  {
    statPlayer() {
      eaten = 0;
    };
    
    uint8_t	eaten;
  };
  
    class Referee : public IReferee
    {
    private:
      IBoardOperator				*boardOp;
      std::map<Team, statPlayer>		stats;
      Team					player;
      Team					winner;
      std::map<RuleID, Rule>			rRules;
      
    public:
        Referee();
        Referee(const Referee & other);
        ~Referee();

        void initialize();

        GameBoard_t getBoardCopy();

        void feedRules(std::map<RuleID, Rule> rules);

        void setPlayer(Team player);

        bool tryPlay(uint8_t x, uint8_t y);

        Team getWinner() const;

        uint8_t getTeamEat(Team player);

        Referee * clone();
    };
}

#endif
