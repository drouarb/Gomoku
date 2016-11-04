//
// Created by celeriy on 02/11/16.
//

#ifndef GOMOKU_ILAYER_HH
#define GOMOKU_ILAYER_HH

#include <iostream>
namespace GUI
{
    class ILayer
    {
    public:
        virtual ~ILayer(){};
         virtual const std::string &getName() const = 0;

        virtual int getStartx() const = 0;

        virtual int getWitdh() const = 0;

        virtual int getHeight() const = 0;

        virtual int getStarty() const = 0;

    };
}
#endif //GOMOKU_ILAYER_HH
