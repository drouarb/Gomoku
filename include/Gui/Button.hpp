//
// Created by celeri_y on 4/17/16.
//

#ifndef CPP_PLAZZA_BUTTON_HPP
#define CPP_PLAZZA_BUTTON_HPP

#include <string>
#include <iostream>
#include "IButton.hpp"

namespace GUI
{

  template <typename T>
  class Button : public IButton
  {
    typedef void  (T::*t_menb)(void *);
    typedef void  (T::*t_menb_noparam)();
    typedef void  *(T::*t_menb_noparam_re)();
    typedef void *(T::*t_menb_param_re)(void*);
   protected:
    int startx;
    int endx;
    int starty;
    int endy;
    int witdh;
    int height;
    visibility stats;
    std::string name;
    typeButton type;
    struct s_func_m
    {
      param type;
      T *obj;
      void *data;
      t_menb menb_param;
      t_menb_noparam  menb_noparam;
      t_menb_noparam_re menb_noparam_re;
      t_menb_param_re menb_param_re;
    };

    s_func_m func;
   public:
    Button(int witdh, int height, int pos_x, int pos_y,  std::string name, T *obj, t_menb menber) : Button(witdh, height, pos_x, pos_y, name)
    {
      this->type = DEFAULT;
      this->setFunc(obj, menber);
    }

    Button(int witdh, int height, int pos_x, int pos_y,  std::string name, T *obj, t_menb_noparam menber) : Button(witdh, height, pos_x, pos_y,  name)
    {
      this->type = DEFAULT;
      this->setFunc(obj, menber);
    }
    Button(int witdh, int height, int pos_x, int pos_y,  std::string name, T *obj, t_menb_noparam_re menber) : Button(witdh, height, pos_x, pos_y, name)
    {
      this->type = DEFAULT;
      this->setFunc(obj, menber);
    }
    Button(int witdh, int height, int pos_x, int pos_y,  std::string name, T *obj, t_menb_param_re menber) : Button(witdh, height, pos_x, pos_y,  name)
    {
      this->type = DEFAULT;
      this->setFunc(obj, menber);
    }
    virtual typeButton getType() const {
      return this->type;
    }
      virtual void setTypButton(typeButton l)
      {
        this->type = l;
      };
    Button(int witdh, int height, int pos_x, int pos_y, std::string name)
    {
      this->startx = pos_x;
      this->starty = pos_y;
      this->endx = this->startx + witdh;
      this->endy = this->starty + height;
      this->witdh = witdh;
      this->height = height;
      this->name = name;
      this->stats = NORMAL;
    }

    void *getObj() const

    {
      return static_cast<void*>(func.obj);
    }
    bool checkPos(int x, int y)
    {
      if (x >= startx && x <= endx && y >= starty && y <= endy)
	return true;
      return false;
    }


    int getStartx() const
    {
      return startx;
    }

    int getEndx() const
    {
      return endx;
    }

    int getStarty() const
    {
      return starty;
    }

    int getEndy() const
    {
      return endy;
    }


    int getWitdh() const
    {
      return witdh;
    }

    int getHeight() const
    {
      return height;
    }


    const std::string &getName() const
    {
      return name;
    }

    void moveTo(int x, int y)
    {
      this->startx = x;
      this->starty = y;
      this->endx = this->startx + witdh;
      this->endy = this->starty + height;
    }

    visibility getStats() const
    {
      return stats;
    }

    void setStats(visibility stats)
    {
      Button::stats = stats;
    }

    void setDataHandler(void *data)
    {
      this->func.data = data;
    }
    void  setFunc(T *obj,t_menb menber)
    {
      func.data = NULL;
      func.menb_param = menber;
      func.obj = obj;
      func.type = PARAM;
    }

    void  setFunc(T *obj,t_menb_param_re menber)
    {
      func.data = NULL;
      func.menb_param_re = menber;
      func.obj = obj;
      func.type = PARAMRE;
    }
    void  setFunc(T *obj,t_menb_noparam_re menber)
    {
      func.data = NULL;
      func.menb_noparam_re = menber;
      func.obj = obj;
      func.type = NOPARAMRE;
    }

    void  setFunc(T *obj,t_menb_noparam menber)
    {
      func.data = NULL;
      func.menb_noparam = menber;
      func.obj = obj;
      func.type = NOPARAM;
    }

    void *execute()
    {
      if (func.type == NOPARAM)
      (func.obj->*func.menb_noparam)();
      if (func.type == PARAM)
	(func.obj->*func.menb_param)(func.data);
      if (func.type == PARAMRE)
	{
	  return ((func.obj->*func.menb_param_re)(func.data));
	}
      if (func.type == NOPARAMRE)
	{
	  return ((func.obj->*func.menb_noparam_re)());
	}
      return (NULL);
    }
  };

}

#endif //CPP_PLAZZA_BUTTON_HPP
