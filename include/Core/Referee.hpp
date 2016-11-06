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
      GameBoard_t				board;
      std::map<Team, statPlayer>		stats;
      Team					player;
      Team					winner;
      std::map<RuleID, Rule>			rRules;
      
    public:
        Referee();

        virtual ~Referee();

        virtual void initialize();

        virtual GameBoard_t getBoardCopy();

        virtual const GameBoard_t &getBoardRef();

        virtual void feedRules(std::map<RuleID, Rule> rules);

        virtual void setPlayer(Team player);

        virtual bool tryPlay(uint8_t x, uint8_t y);

        virtual bool tryPlay(uint8_t x, uint8_t y, GameBoard_t *);

        virtual Team getWinner() const;
    };
}

#endif
