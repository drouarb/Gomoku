//
// Created by greg on 11/11/16.
//

#include <Gui/ICoreOberser.hh>
#include <Gui/ICoreObserver.hh>
#include <Gui/PlayerObserver.hh>
#include "testGUI.hh"

void GUI::testGUI::popupString() {}

void GUI::testGUI::show(const std::string &) {}

void GUI::testGUI::init(ICoreObserver *) {

}

GUI::ICoreObserver *GUI::testGUI::getICoreObserver() {
    return nullptr;
}

void GUI::testGUI::registerPlayer(Players::IPlayer *player) {
    std::cout << "register player " << (void *) player << std::endl;
    PlayerObserver *po = new PlayerObserver();
    po->setPlayer(dynamic_cast<Players::IHumain *>(player));
    if (players[0] == NULL) //TODO why ?
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

}

void GUI::testGUI::endGame(const std::string &winner_name) {

}

void GUI::testGUI::quit() {

}

void GUI::testGUI::addToScreen(const std::string &name, int x, int y) {

}

GUI::typeButton GUI::testGUI::loop() {
    return BOARD;
}

void GUI::testGUI::refresh() {

}

void GUI::testGUI::getMousePose(int *x, int *y) {

}

void GUI::testGUI::loadImage(const std::string &path, const std::string &name) {

}

void GUI::testGUI::addTextToScreen(const std::string &text, int x, int y) {

}

void GUI::testGUI::setPolice(const std::string &path, int size) {

}

void GUI::testGUI::changeOpacity(const std::string &name, int r, int g, int b) {

}

GUI::t_size GUI::testGUI::getSizePicture(const std::string &name) {
    return GUI::t_size();
}

GUI::Obs *GUI::testGUI::getObs() {
    return nullptr;
}

void GUI::testGUI::showError(const std::string &) {

}

void GUI::testGUI::prompt() {

}

GUI::testGUI::testGUI(const std::string pathToTest) {

}
