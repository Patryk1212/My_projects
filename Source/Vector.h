//
// Created by ps2-ostrowski on 20/11/2018.
//
#pragma once

#include <string>

#include <Engine/OGLGame.h>

class Vector
{
public:

    Vector(float x = 0, float y = 0, int speed = 0);
    ~Vector();

    void setX(float x);
    void setY(float y);
    void setSpeed(int speed);

    float getX() const;
    float getY() const;
    int getSpeed() const;

    void normalise();
    Vector operator*(float scalar);

private:

    float x = 0;
    float y = 0;
    int speed = 0;
};