//
// Created by celeri_y on 4/17/16.
//

#ifndef CPP_PLAZZA_IBUTTON_HPP
#define CPP_PLAZZA_IBUTTON_HPP

#include <string>

namespace GUI
{
  enum visibility
  {
    VISIBLE,
    INVISIBLE
  };
  enum param
  {
    PARAM,
    NOPARAMRE,
    PARAMRE,
    NOPARAM
  };

  enum typeButton
  {
    NAVIGATION,
    SELECTION,
    DEFAULT
  };
  class IButton
  {
   public:
    virtual  ~IButton()
    { };

    virtual bool checkPos(int x, int y) = 0;

    virtual void moveTo(int x, int y) = 0;

    virtual void *execute() = 0;

    virtual void setDataHandler(void *data) = 0;

    virtual void setStats(visibility stats) = 0;

    virtual const std::string &getName() const = 0;

    virtual int getStartx() const = 0;

    virtual int getStarty() const = 0;
    virtual void *getObj() const = 0;
    virtual typeButton getType() const = 0;
  };

}
#endif //CPP_PLAZZA_IBUTTON_HPP
