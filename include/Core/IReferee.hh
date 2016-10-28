#ifndef IREFEREE_HH_
# define IREFEREE_HH_

namespace Core
{
  class IReferee
  {
    GameBoard_t			getBoardCopy() = 0;
    const GameBoard_t&		getBoardRef() = 0;
    void			setPlayer(TEAM player);
    bool			tryPlay(uint8_t x, uint8_t y);
    bool			tryPlay(uint8_t x, uint8_t y, const GameBoard &);
    const BoardOperator&	getBoardOperator();
  };
}

#endif
