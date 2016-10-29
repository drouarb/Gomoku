#ifndef REFEREE_HH_
# define REFEREE_HH_

#include "IReferee.hh"

namespace Core
{
    class Referee : public IReferee
    {
    private:
      BoardOperator				boardOp;
      GameBoard_t				board;
    public:
        Referee();

        virtual ~Referee();

        virtual GameBoard_t getBoardCopy();

        virtual const GameBoard_t &getBoardRef();

        virtual void setPlayer(Team player);

        virtual bool tryPlay(uint8_t x, uint8_t y);

        virtual bool tryPlay(uint8_t x, uint8_t y, const GameBoard_t &);

        virtual const BoardOperator &getBoardOperator();
    };
}

#endif
