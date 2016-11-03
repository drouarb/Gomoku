//
// Created by celeriy on 02/11/16.
//

#ifndef GOMOKU_MENUGAME_HH
#define GOMOKU_MENUGAME_HH

#include "Menu.hpp"
#include "IGUI.hh"
#define calcx(x) (460 + 31 + x * 54 - 20 - (x))
#define calcy(x) (8 +  31 + x * 54 - 22 - (x))
using namespace GUI;
namespace GUI
{
    class MenuGame : public Menu
    {
    private:
        IGUI *gui;
    public:
        ~MenuGame(){};
        MenuGame(IGUI *gui);
        void loadAsset();
        void loadButton();
        void aff();
        void loadLayer();
        void setSomething(void *);
        void affButtons() const;
        void sendRule(void *data);
        void playGameOnePlayers();
        void playGameTwoPlayers();
        void playGameIa();
    };
}
#endif //GOMOKU_MENUGAME_HH
