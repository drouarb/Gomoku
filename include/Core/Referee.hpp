#ifndef REFEREE_HH_
# define REFEREE_HH_

#include <vector>
#include <tuple>
#include <map>
#include "Definitions.hpp"
#include "IReferee.hh"
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
      BoardOperator				boardOp;
      std::map<Team, statPlayer>    stats;
      Team					player;
      Team					winner;
      std::map<RuleID, Rule> *			rRules;
      boardPos_t				lastMove;
      uint16_t					nbrPlay;
        char gameId;
      
    public:
        Referee();
        Referee(const Referee & other);
        ~Referee();

        void initialize();

        GameBoard_t getBoardCopy();

        void feedRules(std::map<RuleID, Rule> & rules);

        void setPlayer(Team player);

        //bool tryPlay(uint8_t x, uint8_t y);

        bool tryPlay(boardPos_t x, boardPos_t y);

        bool tryPlay(boardPos_t pos);

        Team getWinner() const;

        uint8_t getTeamEat(Team player);

        BoardOperator *getBoOp();

        IReferee *clone();

        void undoLastMove(boardPos_t newLastMove);

        Team getPlayer() const;

      boardPos_t getLastMove() const;

      uint16_t getNbrPlay() const;

        char getGameId() const;
    };
}

#endif
