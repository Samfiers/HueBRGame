/*
    HueBRGame - Color.h
    Autor: Samuel de Souza Silva
    Data: 12/06/2017
*/
#ifndef COLOR_H
#define COLOR_H

class Color
{
    public:
        float r;
        float g;
        float b;
        float a;
        Color();
        Color(float rc, float gc, float bc, float ac);
        virtual ~Color();
        float *rgba();


};

#endif // COLOR_H
