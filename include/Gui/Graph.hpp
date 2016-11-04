//
// Created by celeri_y on 4/18/16.
//

#ifndef CPP_PLAZZA_GRAPH_HPP
#define CPP_PLAZZA_GRAPH_HPP

#define SHOWTIME 0.5

#include <SDL2/SDL.h>
#include <map>
#include "SDL2/SDL_ttf.h"
#include "IGUI.hh"
#include "IUIHandle.hh"
#include <chrono>
#include <mutex>
#include "Obs.hpp"

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::high_resolution_clock::time_point TimePoint;
namespace GUI
{

    class Graph : public IGUI, public IUIHandle
    {
    private:
        SDL_Event event;
        SDL_Window *fenetre;
        SDL_Renderer *pRenderer;
        std::map<std::string, void *> images;
        std::map<std::string, void *> Textureimages;
        TTF_Font *police;
        ICoreObserver *coreObserver;
        Obs mainObs;
        std::map<std::string, TimePoint> listMessage;
    private:
        SDL_Color colorTexte;
        t_size sizebuff;
    public:
        t_size *last;
        IPlayerObserver *players[2];
        Players::IPlayer *current;

        Graph(ICoreObserver *coreObserver);

        std::list<std::pair<std::string, bool>> rules;

        ~Graph()
        {};

        Graph()
        {};

        void init(ICoreObserver *);

        GameBoard_t board;

        ICoreObserver *getICoreObserver();

        void registerPlayer(Players::IPlayer *); //create observer
        void unregisterPlayer(Players::IPlayer *); //destroy observer
        void feedBoard(const GameBoard_t &);

        void feedRules(std::list<std::pair<std::string, bool>> rules);

        void setCurrentPlayer(Players::IPlayer *);

        void startGame();

        void endGame(const std::string &winner_name);

        void show(const std::string &);

        void prompt();

        void quit();

        void showError(const std::string &);

        void addToScreen(const std::string &name, int x, int y);

        typeButton loop();

        void refresh();

        void loadImage(const std::string &path, const std::string &name);

        void setPolice(const std::string &path, int size);

        void addTextToScreen(const std::string &text, int x, int y);

        void changeOpacity(const std::string &name, int r, int g, int b);

        t_size getSizePicture(const std::string &name);

        void popupString();
    };
}
#endif //CPP_PLAZZA_GRAPH_HPP
