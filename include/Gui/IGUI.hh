#ifndef IGUI_HH_
#define IGUI_HH_

#include "IPlayer.hh"
#include "Definitions.hpp"
#include "ICoreOberser.hh"
#include "IPlayerObserver.hh"
#include "IButton.hpp"
#include "Obs.hpp"
#include <string>
#include <list>
#include <map>

namespace GUI
{
    struct t_size {
        int dimx;
        int dimy;
    };

    class IGUI
    {
    public:
        virtual ~IGUI()
        {}

        virtual void show(const std::string &) = 0;
        virtual void init(ICoreObserver *) = 0;

        virtual ICoreObserver *getICoreObserver() = 0;

        virtual void registerPlayer(Players::IPlayer *) = 0;

        virtual void unregisterPlayer(Players::IPlayer *) = 0;

        virtual void feedBoard(GameBoard_t) = 0;

        virtual void feedRules(std::list<std::pair<std::string, bool>> rules) = 0;

        virtual void setCurrentPlayer(Players::IPlayer *) = 0;

        virtual void startGame() = 0;

        virtual void endGame(const std::string &winner_name) = 0;

        virtual void quit() = 0;

        virtual void addToScreen(const std::string &name, int x, int y) = 0;

        virtual typeButton loop() = 0;

        virtual void refresh() = 0;

        virtual void getMousePose(int *x, int *y) = 0;

        virtual void loadImage(const std::string &path, const std::string &name) = 0;

        virtual void addTextToScreen(const std::string &text, int x, int y) = 0;

        virtual void setPolice(const std::string &path, int size) = 0;

        virtual void changeOpacity(const std::string &name, int r, int g, int b) = 0;

        virtual t_size getSizePicture(const std::string &name) = 0;

        virtual void popupString() = 0;

        virtual Obs *getObs() = 0;
    };
}

#endif
