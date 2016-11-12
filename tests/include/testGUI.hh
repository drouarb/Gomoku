//
// Created by greg on 11/11/16.
//

#ifndef GOMOKU_TESTGUI_HH
#define GOMOKU_TESTGUI_HH

#include <Gui/IGUI.hh>
#include <Gui/IUIHandle.hh>
#include "ConfParser.hh"

namespace GUI {

    class testGUI : public IGUI, public IUIHandle {
    private:

        ConfParser *confParser;
        IPlayerObserver *players[2];
        GameBoard_t board;
        std::list<std::pair<std::string, bool>> rules;
        Players::IPlayer *current;
        ICoreObserver *coreObserver;

    public:
        testGUI(const std::string pathToTest);
        void show(const std::string &);
        void init(ICoreObserver *);

        ICoreObserver *getICoreObserver();

        void registerPlayer(Players::IPlayer *);

        void unregisterPlayer(Players::IPlayer *);

        void feedBoard(const GameBoard_t &);

        void feedRules(std::list<std::pair<std::string, bool>> rules);

        void setCurrentPlayer(Players::IPlayer *);

        void startGame();

        void endGame(const std::string &winner_name);

        void quit();

        void addToScreen(const std::string &name, int x, int y);

        typeButton loop();

        void refresh();

        void getMousePose(int *x, int *y);

        void loadImage(const std::string &path, const std::string &name);

        void addTextToScreen(const std::string &text, int x, int y);

        void setPolice(const std::string &path, int size);

        void changeOpacity(const std::string &name, int r, int g, int b);

        t_size getSizePicture(const std::string &name);

        void popupString();

        Obs *getObs();


        void showError(const std::string &);
        void prompt();



    };

}

#endif //GOMOKU_TESTGUI_HH
