/*
    HueBRGame - Ball.h
    Autor: Samuel de Souza Silva
    Data: 12/06/2017
*/
#ifndef BALL_H
#define BALL_H
#include "Position.h"
#include "Color.h"

class Ball
{
    public:
        float height;
        Color color;
        unsigned int speed;
        Position position;
        Ball();
        virtual ~Ball();

    protected:

    private:
};

#endif // BALL_H
