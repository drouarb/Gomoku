//
// Created by celeriy on 02/11/16.
//

#ifndef GOMOKU_LAYER_HH
#define GOMOKU_LAYER_HH

#include "ILayer.hh"
#include <iostream>

namespace GUI
{
    class Layer : public  ILayer
    {
    private:
        int witdh;
        int height;
        int starty;
        int startx;
        std::string name;
    public:
        virtual ~Layer(){};
        Layer(int startx, int starty, int witdh, int height, const std::string & name);
        const std::string &getName() const;

        int getStartx() const;

        int getWitdh() const;

        int getHeight() const;

        int getStarty() const;
    };
}
#endif //GOMOKU_LAYER_HH
