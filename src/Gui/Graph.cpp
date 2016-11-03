//
// Created by celeri_y on 4/18/16.
//

#include <SDL2/SDL_image.h>
#include "Gui/PlayerObserver.hh"
#include "Graph.hpp"
#include "GraphicException.hpp"
#include <thread>
#include <Gui/MenuGame.hh>

using namespace GUI;


void Graph::setPolice(const std::string &path, int size)
{
    police = TTF_OpenFont(path.c_str(), size);
}

void Graph::quit()
{
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

void Graph::addToScreen(const std::string &name, int x, int y)
{
    SDL_Surface *pSprite = static_cast<SDL_Surface *>(this->images[name]);
    SDL_Texture *pTexture;
    SDL_Rect dest;

    if (pSprite)
    {
        pTexture = SDL_CreateTextureFromSurface(this->pRenderer, pSprite);
        if (pTexture)
        {
            dest = {x, y, pSprite->w, pSprite->h};
            SDL_RenderCopy(this->pRenderer, pTexture, NULL, &dest);
            SDL_DestroyTexture(pTexture);
        }
    }
}

void Graph::loop()
{
    SDL_Delay(1);
    if (SDL_PollEvent(&this->event))
    {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            this->quit();
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                mainObs.notify(event.button.x, event.button.y);
                refresh();
            }
        }
    }
}
void Graph::showError(const std::string & str)
{
    show(str);
}
void Graph::refresh()
{
    SDL_RenderPresent(this->pRenderer);
    SDL_RenderClear(this->pRenderer);
}

void Graph::loadImage(const std::string &path, const std::string &name)
{
    void *pSprite;

    pSprite = static_cast<void *>(IMG_Load(path.c_str()));
    if (pSprite)
    {
        this->images.insert(std::pair<std::string, void *>(name, pSprite));
    }
}

void Graph::addTextToScreen(const std::string &text, int x, int y)
{
    if (police != NULL)
    {
        SDL_Color couleurBlanche;
        couleurBlanche.a = 0;
        couleurBlanche.b = 0;
        couleurBlanche.r = 0;
        couleurBlanche.g = 0;
        void *texte = static_cast<void *>(TTF_RenderText_Shaded(police, text.c_str(), colorTexte, couleurBlanche));
        SDL_Surface *pSprite = static_cast<SDL_Surface *>(texte);
        SDL_Texture *pTexture;
        SDL_Rect dest;
        if (pSprite)
        {
            Uint32 colorkey = SDL_MapRGB(pSprite->format, 255, 255, 255);
            SDL_SetColorKey(pSprite, SDL_TRUE, colorkey);
            pTexture = SDL_CreateTextureFromSurface(this->pRenderer, pSprite);
            if (pTexture)
            {
                dest = {x, y, pSprite->w, pSprite->h};
                SDL_RenderCopy(this->pRenderer, pTexture, NULL, &dest);
                SDL_DestroyTexture(pTexture);
            }
        }
    }
}

void Graph::changeOpacity(const std::string &name, int r, int g, int b)
{
    SDL_Surface *pSprite = static_cast<SDL_Surface *>(this->images[name]);
    if (pSprite)
    {
        Uint32 colorkey = SDL_MapRGB(pSprite->format, r, g, b);
        SDL_SetColorKey(pSprite, SDL_TRUE, colorkey);
    }
}

t_size Graph::getSizePicture(const std::string &name)
{
    SDL_Surface *pSprite = static_cast<SDL_Surface *>(this->images[name]);
    if (pSprite)
    {
        sizebuff.dimx = pSprite->w;
        sizebuff.dimy = pSprite->h;
        return this->sizebuff;
    }
    sizebuff.dimx = 48;
    sizebuff.dimy = 48;
    return this->sizebuff;
}

void Graph::init(ICoreObserver *coreObserver)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_DestroyWindow(this->fenetre);
        SDL_Quit();
        throw (GraphicException("init fail", SDL_GetError()));
    }
    TTF_Init();
    this->fenetre = SDL_CreateWindow("Desktop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1200,
                                     SDL_WINDOW_SHOWN);
    this->pRenderer = SDL_CreateRenderer(this->fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!this->pRenderer)
    {
        SDL_DestroyWindow(this->fenetre);
        SDL_Quit();
        throw (GraphicException("create Windows fail", SDL_GetError()));
    }
    this->police = NULL;
    colorTexte.a = 0;
    colorTexte.b = 0;
    colorTexte.r = 0;
    colorTexte.g = 0;
    std::cout << "init" << std::endl;
    this->coreObserver = coreObserver;
    MenuGame  toto(this);
    mainObs.addMenu(&toto);
    toto.aff();
    players[0] = NULL;
    players[1] = NULL;
    while (1)
    {
        loop();
        SDL_Delay(10);
    }

}

ICoreObserver *Graph::getICoreObserver()
{
    return this->coreObserver;
}
void Graph::registerPlayer(Players::IPlayer *player)
{
    std::cout << "register player " << (void *) player << std::endl;
    PlayerObserver *po = new PlayerObserver();
    po->setPlayer(dynamic_cast<Players::IHumain *>(player));
    if (players[0] == NULL)
        players[0] = po;
    else
        players[1] = po;
}

void Graph::unregisterPlayer(Players::IPlayer *player)
{
    std::cout << "unregister player " << (void *) player << std::endl;
    if  (players[1] != NULL &&  players[1]->getPlayer() == player)
            players[1] = NULL;
    if  (players[0] != NULL &&  players[0]->getPlayer() == player)
        players[0] = NULL;
}

void Graph::feedBoard(const GameBoard_t &)
{
    std::cout << "feed board" << std::endl;
}

void Graph::feedRules(std::list<std::pair<std::string, bool>> rules)
{
    this->rules = rules;
}

void Graph::setCurrentPlayer(Players::IPlayer *player)
{
    current = player;
    show("C'est le tour de " + player->getName());
}

void Graph::startGame()
{
    show("GAME START");
}

void Graph::endGame(const std::string &winner_name)
{}


void Graph::show(const std::string &str)
{
    auto t = Clock::now();
    listMessage[str] = t;
}

void Graph::popupString()
{
    std::map<const std::string, TimePoint>::iterator it = listMessage.begin();
    while ((it) != listMessage.end())
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - (*it).second).count() < SHOWTIME)
        {
            addTextToScreen((*it).first, 900, 520);
        }
        it++;
    }
}

void Graph::prompt()
{
}
