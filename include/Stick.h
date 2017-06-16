/*
    HueBRGame - Ball.h
    Autor: Samuel de Souza Silva
    Data: 12/06/2017
*/

#ifndef STICK_H
#define STICK_H
#include "Position.h"
#include "Color.h"

class Stick
{
    public:
        Color color;
        float height;
        Position position;
        Stick();
        virtual ~Stick();
};

#endif // STICK_H
