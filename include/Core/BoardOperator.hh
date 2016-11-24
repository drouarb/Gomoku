#ifndef GOMOKU_BOARDOPERATOR_HH
#define GOMOKU_BOARDOPERATOR_HH

#include "IBoardOperator.hh"
#include "PatternManager.hh"

namespace Core
{
  class BoardOperator : public IBoardOperator
    {
    private:
      PatternManager	patternM;
    private:
      int       findDoubleThree(Team player, boardPos_t pos);
      bool      findAnotherDoubleThree(Team player, boardPos_t pos1, boardPos_t pos2, boardPos_t pos3, boardPos_t mypos, boardPos_t ommittedDir);
      bool      checkPosForDoubleThree(Team player, boardPos_t pos, boardPos_t ommittedDir);
      bool      isFreeAndMine(Pattern * pat, Team me);
      uint8_t		pApplyEat(Team player, boardPos_t pos);

    public:
      BoardOperator();
      BoardOperator(const BoardOperator & other);
      ~BoardOperator();

        /**
         * Do not call from inside the class.
         */

      Team      boardAt(boardPos_t x, boardPos_t y);

      bool		checkFreeDoubleThree(Team player, boardPos_t x, boardPos_t y);

      bool		checkEatPlayer(Team player, boardPos_t x, boardPos_t y);
      
      bool		checkfiveWinBreak(Team player);

      bool		checkfiveWinNoBreak(Team player);
      
      bool		checkBreakable(Team player);

      uint8_t		applyEat(Team player, boardPos_t x, boardPos_t y);
      
      void		ForceupdateBoard(Team player, boardPos_t x, boardPos_t y);
    };
}
#endif //GOMOKU_BOARDOPERATOR_HH
