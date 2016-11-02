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

  int i = 0;
  while (1)
  {
   toto.aff();
    core.gui->loop();
    core.gui->refresh();
    SDL_Delay(1);
  }
    return (0);
}