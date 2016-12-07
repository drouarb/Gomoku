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

Obs *Graph::getObs()
{
    return this->mainObs;
}

void Graph::quit()
{
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
}

void Graph::loadImage(const std::string &path, const std::string &name)
{
    SDL_Surface *pSprite;
    SDL_Texture *pTexture;
    pSprite = IMG_Load(path.c_str());
    if (pSprite)
    {
        this->images.insert(std::pair<std::string, void *>(name, pSprite));
        pTexture = SDL_CreateTextureFromSurface(this->pRenderer, pSprite);
        if (pTexture)
            this->Textureimages.insert(std::pair<std::string, void *>(name, pTexture));
    }
}

void Graph::addToScreen(const std::string &name, int x, int y)
{
    SDL_Texture *pTexture = static_cast<SDL_Texture *>(this->Textureimages[name]);
    SDL_Surface *pSprite = static_cast<SDL_Surface *>(this->images[name]);
    if (pTexture && pSprite)
    {
        SDL_Rect dest = {x, y, pSprite->w, pSprite->h};
        SDL_RenderCopy(this->pRenderer, pTexture, NULL, &dest);
    }
}

typeButton Graph::loop()
{
    SDL_Delay(1);
    typeButton re;
    if (SDL_PollEvent(&this->event))
    {
        if (event.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            this->quit();
            mainObs->setStop(true);
            return (DEFAULT);
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                last->dimy = event.button.y;
                last->dimx = event.button.x;
                re = mainObs->notify(event.button.x, event.button.y);
                refresh();
                return (re);
            }
        }
    }
    return (DEFAULT);
}

void Graph::showError(const std::string &str)
{
    show(str);
}

void Graph::refresh()
{
    mainObs->actualMenu();
    popupString();
    SDL_RenderPresent(this->pRenderer);
    SDL_RenderClear(this->pRenderer);
}


void Graph::addTextToScreen(const std::string & text, int x, int y)
{
    if (police != NULL)
    {
        SDL_Color backgrounColor;
        backgrounColor.a = 0;
        backgrounColor.b = 0;
        backgrounColor.r = 0;
        backgrounColor.g = 0;
        std::string text_cpy(text);
        SDL_Surface *pSprite = TTF_RenderText_Shaded(police, text_cpy.c_str(), colorTexte, backgrounColor);
        SDL_Texture *pTexture;
        SDL_Rect dest;
        if (pSprite)
        {
            // Uint32 colorkey = SDL_MapRGB(pSprite->format, 0, 0, 0);
            //SDL_SetColorKey(pSprite, SDL_TRUE, colorkey);
            pTexture = SDL_CreateTextureFromSurface(this->pRenderer, pSprite);
            if (pTexture)
            {
                dest = {x, y, pSprite->w, pSprite->h};
                SDL_RenderCopy(this->pRenderer, pTexture, NULL, &dest);
                SDL_DestroyTexture(pTexture);
            }
            SDL_FreeSurface(pSprite);
        }
    }
}

void Graph::changeOpacity(const std::string &name, int r, int g, int b)
{
    SDL_Surface *pSprite = static_cast<SDL_Surface *>(this->images[name]);
    SDL_Texture *pTexture;
    if (pSprite)
    {
        Uint32 colorkey = SDL_MapRGB(pSprite->format, r, g, b);
        SDL_SetColorKey(pSprite, SDL_TRUE, colorkey);
        pTexture = SDL_CreateTextureFromSurface(this->pRenderer, pSprite);
        if (pTexture)
        {
            this->Textureimages[name] = pTexture;
        }

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
        SDL_Quit();
        throw (GraphicException("init fail", SDL_GetError()));
    }
    this->fenetre = SDL_CreateWindow("Desktop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080,
                                     SDL_WINDOW_SHOWN);
    TTF_Init();
    this->pRenderer = SDL_CreateRenderer(this->fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!this->pRenderer)
    {
        SDL_DestroyWindow(this->fenetre);
        SDL_Quit();
        throw (GraphicException("create Windows fail", SDL_GetError()));
    }
    this->last = new t_size;
    last->dimy = 0;
    last->dimx = 0;
    this->police = NULL;
    colorTexte.a = 255;
    colorTexte.b = 255;
    colorTexte.r = 255;
    colorTexte.g = 255;
    this->coreObserver = coreObserver;
    this->permMessage = "";
    board = NULL;
    players[0] = NULL;
    players[1] = NULL;
    current = NULL;
    MenuGame toto(this);
    mainObs = new Obs();
    mainObs->addMenu(&toto);
    auto t = Clock::now();
    while (getObs()->getStop() == false)
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t).count() > 0.5)
        {
            refresh();
            t = Clock::now();
        }
        SDL_Delay(10);
        loop();
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
    po->setPlayer(player);
    if (players[0] == NULL)
        players[0] = po;
    else
        players[1] = po;
}

void Graph::unregisterPlayer(Players::IPlayer *player)
{
    std::cout << "unregister player " << (void *) player << std::endl;
    if (players[1] != NULL && players[1]->getPlayer() == player)
        players[1] = NULL;
    if (players[0] != NULL && players[0]->getPlayer() == player)
        players[0] = NULL;
}

void Graph::feedBoard(GameBoard_t board)
{
    if (this->board)
    {
        delete [] this->board;
    }
    this->board = board;
    refresh();
}

void Graph::feedRules(std::list<std::pair<std::string, bool>> rules)
{
    this->rules = rules;
}

void Graph::setCurrentPlayer(Players::IPlayer *player)
{
    current = player;
    show(player->getName() + "'s turn ");
}

void Graph::startGame()
{
    listMessage.clear();
    permMessage = "";
    show("START GAME");
}

void Graph::endGame(const std::string &winner_name)
{
    this->permMessage = "END OF GAME. WINNER: " + winner_name;
    mainObs->actualMenu();
    popupString();
    refresh();
    current = NULL;
}


void Graph::show(const std::string &str)
{
    auto t = Clock::now();
    listMessage[str] = t;
}

void Graph::popupString()
{
    std::map<const std::string, TimePoint>::iterator it = listMessage.begin();
    int y = 0;
     while ((it) != listMessage.end())
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - (*it).second).count() < SHOWTIME)
        {
            addTextToScreen((*it).first, 1000 - (*it).first.length() * 10, 520 + y);
            y += 100;
            listMessage.erase((it));
            break;
        }
        it++;
    }
    if (permMessage != "")
    {
        addTextToScreen(permMessage, 1000 - permMessage.length() * 10, 520 + y);
    }
}

void Graph::prompt()
{
    auto t = Clock::now();
    refresh();
    while (loop() != BOARD && mainObs->getStop() == false && getICoreObserver()->gameIsRunning())
    {
        if (std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - t).count() > SHOWTIME)
        {
            refresh();
            t = Clock::now();
        }
        SDL_Delay(10);
    }
}

void Graph::getMousePose(int *x, int *y)
{
    SDL_GetMouseState(x, y);
}

