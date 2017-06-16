/*
    HueBRGame - Color Class
    Autor: Samuel de Souza Silva
    Data: 12/06/2017
*/
#include "Color.h"

Color::Color(){}

Color::Color(float rc, float gc, float bc, float ac)
{
    r = rc;
    g = gc;
    b = bc;
    a = ac;
}

float *Color::rgba(){
    float *aReturn = new float[4];
    aReturn[0] = r;
    aReturn[1] = g;
    aReturn[2] = b;
    aReturn[3] = a;
    return aReturn;
}


Color::~Color()
{
    //dtor
}
