/*
    HueBRGame - Position.h
    Autor: Samuel de Souza Silva
    Data: 12/06/2017
*/

#ifndef POSITION_H
#define POSITION_H

class Position
{
    public:
        float x, y, z;
        Position();
        Position(float xParam, float yParam, float zParam);
        virtual ~Position();
};

#endif // POSITION_H
