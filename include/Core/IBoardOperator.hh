#ifndef GOMOKU_IBOARDOPERATOR_HH
#define GOMOKU_IBOARDOPERATOR_HH

#include <vector>
#include <tuple>
#include "Definitions.hpp"

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
 
        virtual void getXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getFreeXPossible(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getX(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getFreeX(uint8_t numberPiece, Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getEatPos(Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getFreeDoubleThreePos(Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getFiveBreakable(Team player, std::vector<boardPos_t> *tab, weight_t w) = 0;

        virtual void getPercentDensityOnPos(boardPos_t, boardPos_t, std::vector<boardPos_t> *tab, weight_t w) = 0;
    };
}
#endif //GOMOKU_IBOARDOPERATOR_HH
