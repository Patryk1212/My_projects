//
// Created by ps2-ostrowski on 20/11/2018.
//
#pragma once
#include <string>
#include <Engine/OGLGame.h>

class Vector
{
public:
    Vector(float x1, float y1);
    ~Vector();

    void setX(float x1);
    void setY(float y1);

    float getX();
    float getY();

    void normalise();
    Vector operator*(float scalar);

private:
    float x = 0;
    float y = 0;
    float speed = 0;
};