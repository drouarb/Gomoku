#ifndef GOMOKU_IBOARDOPERATOR_HH
#define GOMOKU_IBOARDOPERATOR_HH

#include <vector>
#include <tuple>
#include "Definitions.hh"

namespace Core
{
    class IBoardOperator
    {
    public:
        virtual ~IBoardOperator()
        {};

        virtual Team boardAt(boardPos_t x, boardPos_t y) = 0;

        virtual bool checkFreeDoubleThree(Team player, boardPos_t x, boardPos_t y) = 0;

        virtual bool checkfiveWinBreak(Team player) = 0;

        virtual bool checkfiveWinNoBreak(Team player) = 0;

        virtual uint8_t applyEat(Team player, boardPos_t x, boardPos_t y) = 0;

        virtual void ForceupdateBoard(Team player, boardPos_t x, boardPos_t y) = 0;

        virtual std::vector<boardPos_t> getXPossible(uint8_t numberPiece, Team player) = 0;

        virtual std::vector<boardPos_t> getFreeXPossible(uint8_t numberPiece, Team player) = 0;

        virtual std::vector<boardPos_t> getX(uint8_t numberPiece, Team player) = 0;

        virtual std::vector<boardPos_t> getFreeX(uint8_t numberPiece, Team player) = 0;

        virtual std::vector<std::pair<boardPos_t, uint8_t>> getEatPos(Team player) = 0;

        virtual std::vector<boardPos_t> getFreeDoubleThreePos(Team player) = 0;

        virtual std::vector<boardPos_t> getFiveBreakable(Team player) = 0;

      virtual boardPos_t getPercentDensityOnPos(boardPos_t, boardPos_t) = 0;
    };
}
#endif //GOMOKU_IBOARDOPERATOR_HH
