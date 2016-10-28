#ifndef IREFEREE_HH_
# define IREFEREE_HH_

#include "Definitions.hh"

namespace Core
{
  class IReferee
  {
    virtual GameBoard_t			getBoardCopy() = 0;
    virtual const GameBoard_t&		getBoardRef() = 0;
    virtual void			setPlayer(TEAM player) = 0;
    virtual bool			tryPlay(uint8_t x, uint8_t y) = 0;
    virtual bool			tryPlay(uint8_t x, uint8_t y, const GameBoard &) = 0;
    virtual const BoardOperator&	getBoardOperator() = 0;
  };
}

#endif
