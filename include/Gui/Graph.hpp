//
// Created by celeri_y on 4/18/16.
//

#ifndef CPP_PLAZZA_GRAPH_HPP
#define CPP_PLAZZA_GRAPH_HPP

#include <SDL2/SDL.h>
#include <map>
#include "SDL2/SDL_ttf.h"
#include "IGUI.hh"
#include "IUIHandle.hh"

namespace GUI {
    struct t_size {
        int dimx;
        int dimy;
    };

    class Graph : public IGUI, public IUIHandle {
    private:
        SDL_Event event;
        SDL_Window *fenetre;
        SDL_Renderer *pRenderer;
        std::map<std::string, void *> images;
        TTF_Font *police;
    private:
        SDL_Color colorTexte;
        t_size sizebuff;
        ICoreObserver *coreObserver;
        IPlayerObserver *players[2];
        Players::IPlayer *current;

    public:
        Graph(ICoreObserver *coreObserver);

        ~Graph() {};

        Graph() {};

        void init(ICoreObserver *);

        void registerPlayer(Players::IPlayer *); //create observer
        void unregisterPlayer(Players::IPlayer *); //destroy observer
        void feedBoard(const GameBoard_t &);

        void feedRules(std::list<std::pair<std::string, bool>> rules);

        void setCurrentPlayer(Players::IPlayer *);

        void startGame();

        void endGame(const std::string &winner_name);

        void showErrror(std::string);

        void prompt();

        void quit();

        void addToScreen(const std::string &name, int x, int y);

        void loop();

        void refresh();

        void loadImage(const std::string &path, const std::string &name);

        void setPolice(const std::string &path, int size);

        void addTextToScreen(const std::string &text, int x, int y);

        void changeOpacity(const std::string &name, int r, int g, int b);

        t_size getSizePicture(const std::string &name);
    };
}
#endif //CPP_PLAZZA_GRAPH_HPP
