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
      ~BoardOperator();

      void		feed(GameBoard_t *board);
      
      bool		checkFreeDoubleThree(Team player, uint8_t x, uint8_t y);

      /**
       * Do not call with a single-stone pattern.
       */
      bool      isFreeAndMine(Pattern * pat, Team me);
      
      std::vector<std::pair<uint8_t, uint8_t>> getFreeDoubleThreePos(Team player);
      
      bool		checkEatPlayer(Team player, uint8_t x, uint8_t y);
      
      std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> getEatPos(Team player);
      
      bool		checkfiveWinBreak(Team player);

      bool		checkfiveWinNoBreak(Team player);
      
      std::vector<std::pair<uint8_t, uint8_t>> getXPossible(uint8_t numberPiece, Team player);
      
      bool		checkBreakable(Team player);
      
      Team		checkPos(uint8_t x, uint8_t y);

      uint8_t		applyEat(Team player, uint8_t x, uint8_t y);
      
      void		ForceupdateBoard(Team player, uint8_t x, uint8_t y);
    };
}
#endif //GOMOKU_BOARDOPERATOR_HH
