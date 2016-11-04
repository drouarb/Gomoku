#ifndef IREFEREE_HH_
# define IREFEREE_HH_

#include "Definitions.hh"
#include "BoardOperator.hh"

namespace Core
{
    class IReferee
    {
    public:
        virtual ~IReferee() { };

        virtual void initialize() = 0;

        virtual GameBoard_t getBoardCopy() = 0;
      
        virtual const GameBoard_t &getBoardRef() = 0;
      
        virtual void setPlayer(Team player) = 0;
      
        virtual bool tryPlay(uint8_t x, uint8_t y) = 0;
      
        virtual bool tryPlay(uint8_t x, uint8_t y, GameBoard_t *) = 0;
      
        virtual Team getWinner() const = 0 ;
    };
}

#endif
