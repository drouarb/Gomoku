#ifndef REFEREE_HH_
# define REFEREE_HH_

#include <vector>
#include <tuple>
#include "IReferee.hh"
#include "IBoardOperator.hh"
#include "BoardOperator.hh"

#define EATWIN 10

namespace Core
{

  struct	statPlayer
  {
    Team	team;
    uint8_t	eaten;
  };
  
    class Referee : public IReferee
    {
    private:
      IBoardOperator				*boardOp;
      GameBoard_t				board;
      std::vector<statPlayer>			stats;
      Team					player;

      Team					winner;
      
    public:
        Referee();

        virtual ~Referee();

        virtual void initialize();

        virtual GameBoard_t getBoardCopy();

        virtual const GameBoard_t &getBoardRef();

        virtual void setPlayer(Team player);

        virtual bool tryPlay(uint8_t x, uint8_t y);

        virtual bool tryPlay(uint8_t x, uint8_t y, GameBoard_t *);

        virtual const IBoardOperator *getBoardOperator();

        virtual Team getWinner() const;
    };
}

#endif
