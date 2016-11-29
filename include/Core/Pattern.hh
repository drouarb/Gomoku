#ifndef PATTERN_HH_
#define PATTERN_HH_

#include "Definitions.hpp"
#include "Helpers/reservationList.hpp"

namespace Core
{
    struct Pattern
    {
        /**
         * Creates and fills a new Pattern entirely.
         * \param team Team owning the pattern.
         * \param length Total length of the line, extremities included.
         * \param first First value of the line, right before the pattern.
         * \param last Last value of the line, right after the pattern.
         * \param The position of "first" on the board.
         * \param direction The value to add to a position to get the next position on the line.
         */
        Pattern(Team team, uint8_t length, Team first, Team last, boardPos_t posOfFirst, boardPos_t direction);

        /**
         * Creates and fills a one-stone pattern.
         * \param team The team owning the stone.
         * \param pos The position of the stone on the board;
         */
        Pattern(Team team, boardPos_t pos);

        Pattern();

        ~Pattern();

        bool operator==(const Pattern &);

        void set(uint8_t length, Team first, Team last, boardPos_t posOfFirst, boardPos_t direction);
        /**
         * The given position becomes an empty value (no stone), and only the first half of the pattern is kept.
         * \param team The team owning the pattern.
         * \param posOnPattern Position on the pattern where the stone was removed.
         */
        void breatAt(uint8_t posOnPattern);
        /**
         * Returns the team owning the pattern.
         */
        Team getTeam();

        //char * line; + 1 malloc + 1 void* = too slow + too much mem space
        Team *line;
        uint8_t lineLength;
        boardPos_t posOfFirst;
        boardPos_t direction; //number to add to get to the next stone in the line

    private:
        void freeLine();
        void allocLine();
        
        static reservList<Team[1]> line1Stock;
        static reservList<Team[4]> line2Stock;
        static reservList<Team[5]> line3Stock;
        static reservList<Team[6]> line4Stock;
        static reservList<Team[7]> line5Stock;
        static reservList<Team[12]> line10Stock;
        static reservList<Team[21]> line19Stock;

        void createLine1();
        void createLine2();
        void createLine3();
        void createLine4();
        void createLine5();
        void createLine6to10();
        void createLine11to19();

        typedef void (Pattern::*createLineFun)();
        static const createLineFun createLineFunArr[];
        
        void delLine1();
        void delLine2();
        void delLine3();
        void delLine4();
        void delLine5();
        void delLine6to10();
        void delLine11to19();

        typedef void (Pattern::*delLineFun)();
        static const delLineFun delLineFunArr[];
    };
}

#endif
