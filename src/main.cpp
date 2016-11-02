//
// Created by celeriy on 28/10/16.
//

#include <Gui/Graph.hpp>
#include "Core.hh"
#include "CoreOberser.hh"
#include "MenuGame.hh"
int main(int ac, char **av)
{
  Core::Core core;
   MenuGame  toto(core.gui);

  while (1)
  {
    core.gui->loop();
    core.gui->refresh();
    toto.aff();
    SDL_Delay(10);
  }
    return (0);
}