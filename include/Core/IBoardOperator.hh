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

        virtual void feed(GameBoard_t *board) = 0;

        virtual bool checkFreeDoubleThree(Team player, uint8_t x, uint8_t y) = 0;

        virtual std::vector<std::pair<uint8_t, uint8_t>> getFreeDoubleThreePos(Team player) = 0;

        virtual bool checkEatPlayer(Team player, uint8_t x, uint8_t y) = 0;

        virtual std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> getEatPos(Team player) = 0;

        virtual bool checkfiveWin(Team player) = 0;

        virtual std::vector<std::pair<uint8_t, uint8_t>> getXPossible(uint8_t numberPiece, Team player) = 0;

        virtual bool checkBreakable(Team player) = 0;

        virtual Team checkPos(uint8_t x, uint8_t y) = 0;

        virtual uint8_t applyEat(Team player, uint8_t x, uint8_t y) = 0;

        virtual void ForceupdateBoard(Team player, uint8_t x, uint8_t y) = 0;
    };
}
#endif //GOMOKU_IBOARDOPERATOR_HH
