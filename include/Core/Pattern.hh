#ifndef PATTERN_HH_
#define PATTERN_HH_

#define MAX_PATTERN_LENGTH 7

#include "Definitions.hh"

namespace Core
{
    struct Pattern
    {
        /**
         * Creates and fills a new Pattern entirely. The latter can be interrupted or not.
         * \param team Team owning the pattern.
         * \param length Total length of the line, extremities included.
         * \param interruptionIndex Index of the place where the line is interrupted. 0 if line is not interrupted.
         * \param first First value of the line, right before the pattern.
         * \param last Last value of the line, right after the pattern.
         */
        Pattern(Team team, uint8_t length, uint8_t interruptionIndex, Team first, Team last);

        /**
         * Creates and fills a new non-interrupted Pattern entirely.
         * \param team Team owning the pattern.
         * \param length Total length of the line, extremities included.
         * \param first First value of the line, right before the pattern.
         * \param last Last value of the line, right after the pattern.
         */
        Pattern(Team team, uint8_t length, Team first, Team last);

        /**
         * Creates and fills a one-stone pattern.
         * \param team The team owning the stone.
         */
        Pattern(Team team);

        ~Pattern();

        bool operator==(const Pattern &);

        //char * line; + 1 malloc + 1 void* = too slow + too much mem space
        Team line[MAX_PATTERN_LENGTH];
        //you can get the team owning the pattern simply by doing line[1]
        uint8_t lineLength;
        uint8_t interrupted; //1 if line is interrupted, 0 if not
    };
}

#endif
