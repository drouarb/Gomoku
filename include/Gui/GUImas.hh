#ifndef GUIMAS_HH_
#define GUIMAS_HH_

#include "IGUI.hh"
#include "IUIHandle.hh"

namespace GUI
{
    class GUImas : public IGUI , public IUIHandle
    {
    public:
        GUImas();
        ~GUImas();
        
        void init(ICoreObserver *);
        void registerPlayer(Players::IPlayer *); //create observer
        void unregisterPlayer(Players::IPlayer *); //destroy observer
        void feedBoard(const GameBoard_t &);
        void feedRules(std::list<std::pair<std::string, bool>> rules);
        void setCurrentPlayer(Players::IPlayer *);
        void startGame();
        void endGame(const std::string & winner_name);
        void showErrror(std::string);
        void prompt();

    private:
        ICoreObserver * coreObserver;
        IPlayerObserver * players[2];
        Players::IPlayer * current;
    };
}

#endif