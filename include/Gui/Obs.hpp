//
// Created by celeri_y on 4/18/16.
//

#ifndef CPP_PLAZZA_OBS_HPP
#define CPP_PLAZZA_OBS_HPP

#include <vector>
#include "IMenu.hpp"

namespace  GUI
{
  enum eventObs {
    COREQUIT
  };
  class Obs {
   public:
    Obs();
   private:
   public:
    void setListMenu(std::vector<IMenu *> &listMenu);
   private:
    std::vector<IMenu*>listMenu;
   public:
    void notify(int x, int y);
    void  addMenu(IMenu *menu);
    void notify(eventObs e);
  };
}
#endif //CPP_PLAZZA_OBS_HPP
