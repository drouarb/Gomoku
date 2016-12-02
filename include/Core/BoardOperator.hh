#ifndef GOMOKU_BOARDOPERATOR_HH
#define GOMOKU_BOARDOPERATOR_HH

#include <vector>
#include "PatternManager.hh"

#define DENSITYRANGE 2

namespace Core
{
  class BoardOperator
    {
  private:
      PatternManager	patternM;
      fastList<boardPos_t> lastTakenStones;
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

      BoardOperator & operator=(const BoardOperator &);

        /**
         * Do not call from inside the class.
         */

        void clearLastMove();

      const fastList<boardPos_t> & getLastTakenStones() const;

        const PatternManager & getPatternManager() const;

      Team		boardAt(boardPos_t x, boardPos_t y);

      bool		checkFreeDoubleThree(Team player, boardPos_t x, boardPos_t y);

      bool		checkEatPlayer(Team player, boardPos_t x, boardPos_t y);

      bool		checkfiveWinBreak(Team player);

      bool		checkfiveWinNoBreak(Team player);
      
      uint8_t		applyEat(Team player, boardPos_t x, boardPos_t y);
      
      void		ForceupdateBoard(Team player, boardPos_t x, boardPos_t y);

      void		ForceupdateBoard(Team player, boardPos_t pos);

      void		getXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w);

      void		getFreeXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w);

      void		getX(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w);

      void		getFreeX(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w);

      void		getEatPos(Team player, std::vector<boardPos_t> *tab, weight_t w);
      
      void		getFreeDoubleThreePos(Team player, std::vector<boardPos_t> *tab, weight_t w);
      
      void		getFiveBreakable(Team player, std::vector<boardPos_t> *tab, weight_t w);

      void		getPercentDensityOnPos(boardPos_t, boardPos_t, std::vector<boardPos_t> *tab, weight_t w);
    };
}
#endif //GOMOKU_BOARDOPERATOR_HH
