//
// Created by celeriy on 02/11/16.
//

#ifndef GOMOKU_MENUGAME_HH
#define GOMOKU_MENUGAME_HH

#include "Menu.hpp"
#include "IGUI.hh"
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
    };
}
#endif //GOMOKU_MENUGAME_HH
