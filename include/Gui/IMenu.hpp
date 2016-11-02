//
// Created by celeri_y on 4/17/16.
//

#ifndef CPP_PLAZZA_IMENU_HPP
#define CPP_PLAZZA_IMENU_HPP

#include "IButton.hpp"

namespace  GUI
{
  class IMenu
  {

   public:
    virtual ~IMenu(){};
    virtual void addButtons(IButton *button) = 0;
    virtual void delButton(IButton *button) =  0;
    virtual void clearListButton() = 0;
    virtual const std::vector<IButton *> & getListButton() const = 0;
    virtual void loadAsset() = 0;
    virtual void loadButton() = 0;
    virtual void aff() = 0;
    virtual int getPosx() = 0;
    virtual int getPosy() = 0;
    virtual int getHeight() = 0;
    virtual int getWitdh () = 0;
    virtual  void setSomething(void *) = 0;
  };
}
#endif //CPP_PLAZZA_IMENU_HPP
