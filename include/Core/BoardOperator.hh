#ifndef GOMOKU_BOARDOPERATOR_HH
#define GOMOKU_BOARDOPERATOR_HH

#include "IBoardOperator.hh"
#include "PatternManager.hh"

namespace Core
{
  class BoardOperator : public IBoardOperator
    {
    private:
      GameBoard_t	*board;
      PatternManager	*patternM;
    private:
      bool		checkThreeFreeOnMe(Team player, Pattern *pats);
    public:
      BoardOperator();
      virtual ~BoardOperator();

      virtual void		feed(GameBoard_t *board);
      
      virtual bool		checkFreeDoubleThree(Team player, uint8_t x, uint8_t y);
      
      virtual std::vector<std::pair<uint8_t, uint8_t>> getFreeDoubleThreePos(Team player);
      
      virtual bool		checkEatPlayer(Team player, uint8_t x, uint8_t y);
      
      virtual std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> getEatPos(Team player);
      
      virtual bool		checkfiveWinBreak(Team player);

      virtual bool		checkfiveWinNoBreak(Team player);
      
      virtual std::vector<std::pair<uint8_t, uint8_t>> getXPossible(uint8_t numberPiece, Team player);
      
      virtual bool		checkBreakable(Team player);
      
      virtual Team		checkPos(uint8_t x, uint8_t y);

      virtual uint8_t		applyEat(Team player, uint8_t x, uint8_t y);
      
      virtual void		ForceupdateBoard(Team player, uint8_t x, uint8_t y);
    };
}
#endif //GOMOKU_BOARDOPERATOR_HH
