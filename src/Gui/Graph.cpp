//
// Created by celeri_y on 4/18/16.
//

#include <SDL2/SDL_image.h>
#include "Gui/PlayerObserver.hh"
#include "Graph.hpp"
#include "GraphicException.hpp"

using namespace GUI;


void  Graph::setPolice(const std::string &path, int size)
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
	      refresh();
	    }
	}
    }
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
    std::cout << path << std::endl;
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
      couleurBlanche.a = 255;
      couleurBlanche.b = 255;
      couleurBlanche.r = 255;
      couleurBlanche.g = 255;
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

void Graph::init(ICoreObserver * coreObserver)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        SDL_DestroyWindow(this->fenetre);
        SDL_Quit();
        throw  (GraphicException("init fail", SDL_GetError()));
    }
    TTF_Init();
    this->fenetre = SDL_CreateWindow("Desktop", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1200, SDL_WINDOW_SHOWN);
    this->pRenderer = SDL_CreateRenderer(this->fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!this->pRenderer)
    {
        SDL_DestroyWindow(this->fenetre);
        SDL_Quit();
        throw  (GraphicException("create Windows fail", SDL_GetError()));
    }
    this->police = NULL;
    colorTexte.a = 0;
    colorTexte.b = 0;
    colorTexte.r = 0;
    colorTexte.g = 0;
    std::cout << "init" << std::endl;
    this->coreObserver = coreObserver;

}

void  Graph::registerPlayer(Players::IPlayer * player)
{
    std::cout << "register player " << (void*)player << std::endl;
    PlayerObserver * po = new PlayerObserver();
    po->setPlayer(dynamic_cast<Players::IHumain *>(player));
    if (players[0] == NULL)
        players[0] = po;
    else
        players[1] = po;
}

void Graph::unregisterPlayer(Players::IPlayer * player)
{
    std::cout << "unregister player " << (void*)player << std::endl;
    if (players[1]->getPlayer() == player)
        players[1] = NULL;
    else
        players[0] = NULL;
}

void  Graph::feedBoard(const GameBoard_t &)
{
    std::cout << "feed board" << std::endl;
}

void Graph::feedRules(std::list<std::pair<std::string, bool>> rules)
{
    for (std::list<std::pair<std::string, bool> >::iterator it = rules.begin();
         it != rules.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
    std::cout << std::endl;
}

void Graph::setCurrentPlayer(Players::IPlayer * player)
{
    current = player;
}

void Graph::startGame()
{ }

void Graph::endGame(const std::string &winner_name)
{ }

void Graph::showErrror(std::string)
{
    std::cout << "nope" << std::endl;
}

void Graph::prompt()
{
    std::cout << "prompt: " << current->getName() << std::endl;
    uint8_t x, y;
    std::cout << "x? > ";
    std::cin >> x;
    std::cout << "y? > ";
    std::cin >> y;
    if (current)
    {
        if (players[0] && players[0]->getPlayer() == current)
            players[0]->sendPlay(x, y);
        else if (players[1] && players[1]->getPlayer() == current)
            players[1]->sendPlay(x, y);
    }

    //should not happen
    if (!current)
        std::cout << "/!\\ no current player" << std::endl;
    if (!players[0] || !players[1])
        std::cout << "/!\\ not enough players" << std::endl;
}
