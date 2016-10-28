#ifndef REFEREE_HH_
# define REFEREE_HH_

#include "IReferee.hh"

namespace Core
{
  class Referee : public IReferee
  {
  public:
    Referee();
    ~Referee();

    virtual GameBoard_t			getBoardCopy();
    virtual const GameBoard_t&		getBoardRef();
    virtual void			setPlayer(TEAM player);
    virtual bool			tryplay(uint8_t x, uint8_t y);
    virtual bool			tryplay(uint8_t x, uint8_t y, const GameBoard &);
    virtual const BoardOperator&	getBoardOperator();
  }
}

#endif
