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
   public:
    void setListMenu(std::vector<IMenu *> &listMenu);
   private:
      bool stop;
    std::vector<IMenu*>listMenu;
   public:
    typeButton notify(int x, int y);
    void  addMenu(IMenu *menu);
    void notify(eventObs e);
      void actualMenu();
      void setStop(bool);
      bool getStop() const;
  };
}
#endif //CPP_PLAZZA_OBS_HPP
