#ifndef PATTERN_HH_
#define PATTERN_HH_

#define MAX_PATTERN_LENGTH 7

#include "Definitions.hh"

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
        void reallocLine();
        void allocLine();
    };
}

#endif
