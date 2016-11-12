//
// Created by greg on 11/11/16.
//

#include <IPlayer.hh>
#include <Gui/ICoreOberser.hh>
#include <Gui/PlayerObserver.hh>
#include <iomanip>
#include "testGUI.hh"

void GUI::testGUI::popupString() {}

void GUI::testGUI::show(const std::string &e) {
    std::cout << e << std::endl;
}

void GUI::testGUI::init(ICoreObserver *coreObserver) {
    this->coreObserver = coreObserver;
    this->coreObserver->playGame(GamePlayers::TWOPLAYERS);
}

GUI::ICoreObserver *GUI::testGUI::getICoreObserver() {
    return this->coreObserver;
}

void GUI::testGUI::registerPlayer(Players::IPlayer *player) {
    std::cout << "register player " << player->getName() << " : " << player->getScore() << std::endl;
    PlayerObserver *po = new PlayerObserver();
    po->setPlayer(dynamic_cast<Players::IHumain *>(player));
    if (players[0] == NULL)
        players[0] = po;
    else
        players[1] = po;
}

void GUI::testGUI::unregisterPlayer(Players::IPlayer *player) {
    std::cout << "unregister player " << (void *) player << std::endl;
    if (players[1] != NULL && players[1]->getPlayer() == player)
        players[1] = NULL;
    if (players[0] != NULL && players[0]->getPlayer() == player)
        players[0] = NULL;
}

void GUI::testGUI::feedBoard(const GameBoard_t &board) {
    this->board = board;
}

void GUI::testGUI::feedRules(std::list<std::pair<std::string, bool>> rules) {
    this->rules = rules;
}

void GUI::testGUI::setCurrentPlayer(Players::IPlayer *player) {
    this->current = player;
    show(player->getName() + "'s turn ");
}

void GUI::testGUI::startGame() {
    show("START GAME");
}

void GUI::testGUI::endGame(const std::string &winner_name) {
    show("END OF GAME. WINNER: " + winner_name);
    this->refresh();
    if ((winner_name == "NO ONE" && this->winner == Team::NOPLAYER) ||
        (winner_name == "Black" && this->winner == Team::BLACK) ||
        (winner_name == "White" && this->winner == Team::WHITE)) {
        return;
    }
    std::cerr << "Victory condition not respected : " << this->confParser->getEnd() << std::endl;
    exit(-1);
}

void GUI::testGUI::quit() {}

void GUI::testGUI::addToScreen(const std::string &name, int x, int y) {}

GUI::typeButton GUI::testGUI::loop() {
    return BOARD;
}

void GUI::testGUI::refresh() {

    std::cout << "\t";

    for (uint8_t y = 0; y < 19; ++y) {
        std::cout << std::setw(3) << y + 0;
    }

    std::cout << std::endl;

    for (uint8_t y = 0; y < 19; ++y) {
        std::cout << y + 0 << ":\t";

        for (uint8_t x = 0; x < 19; ++x) {
            std::cout << std::setw(3) << (this->board[y * 19 + x] + 0);
        }

        if (y == 8) {
            std::cout << "   P1: Black";
        }
        if (y == 10) {
            std::cout << "   P2: White";
        }

        std::cout << std::endl;
    }
}

void GUI::testGUI::getMousePose(int *x, int *y) {}

void GUI::testGUI::loadImage(const std::string &path, const std::string &name) {}

void GUI::testGUI::addTextToScreen(const std::string &text, int x, int y) {}

void GUI::testGUI::setPolice(const std::string &path, int size) {}

void GUI::testGUI::changeOpacity(const std::string &name, int r, int g, int b) {}

GUI::t_size GUI::testGUI::getSizePicture(const std::string &name) {
    return GUI::t_size();
}

GUI::Obs *GUI::testGUI::getObs() {
    return new Obs();
}

void GUI::testGUI::showError(const std::string &e) {
    std::cout << "Error: " << e << std::endl;
}

void GUI::testGUI::prompt() {
    ConfParser::line_t line;

    try {
        line = this->confParser->getNextPlay();
        this->winner = this->confParser->getEnd().team;
    } catch (std::logic_error) {
        this->coreObserver->endGame();
        return;
    }

    if (line.team == NOPLAYER) {
        std::cout << "Invalid play :" << line << std::endl;
        return;
    }
    this->players[line.team - 1]->sendPlay(line.y, line.x);
}

GUI::testGUI::testGUI(const std::string pathToTest) {
    this->players[0] = nullptr;
    this->players[1] = nullptr;
    this->confParser = new ConfParser(pathToTest);
}
