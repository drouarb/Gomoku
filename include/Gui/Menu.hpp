//
// Created by celeri_y on 4/17/16.
//

#ifndef CPP_PLAZZA_MENU_HPP
#define CPP_PLAZZA_MENU_HPP

#include <vector>
#include "IMenu.hpp"
#include "IButton.hpp"

namespace GUI
{
  class Menu : public  IMenu
  {
   protected:
    int posx;
    int posy;
    int witdh;
    int height;
    const std::vector<IButton *> & getListButton() const;
   protected:
    std::vector<IButton *> listButton;
   public:
    virtual void addButtons(IButton *button);
    virtual void delButton(IButton *button);
    virtual void clearListButton();
    virtual void loadAsset() = 0;
    virtual void loadButton() = 0;
    virtual void aff() = 0;
    virtual int getPosx();
    virtual int getPosy();
    virtual int getHeight();
    virtual int getWitdh ();
    void setSomething(void *) = 0;
  };
}
#endif //CPP_PLAZZA_MENU_HPP
