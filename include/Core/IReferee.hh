#ifndef IREFEREE_HH_
# define IREFEREE_HH_

namespace Core
{
  class IReferee
  {
    GameBoard_t			getBoardCopy() = 0;
    const GameBoard_t&		getBoardRef() = 0;
    void			setPlayer(TEAM player) = 0;
    bool			tryPlay(uint8_t x, uint8_t y) = 0;
    bool			tryPlay(uint8_t x, uint8_t y, const GameBoard &) = 0;
    const BoardOperator&	getBoardOperator() = 0;
  };
}

#endif
