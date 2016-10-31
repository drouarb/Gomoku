//
// Created by celeriy on 31/10/16.
//

#ifndef GOMOKU_IUIHANDLE_HH
#define GOMOKU_IUIHANDLE_HH

#include "IPlayer.hh"
namespace GUI
{
    class IUIHandle
    {
    public:
        virtual ~IUIHandle(){};
        virtual void showErrror(std::string) = 0;
        virtual void prompt(Players::IPlayer *) = 0;
    };
}
#endif //GOMOKU_IUIHANDLE_HH
