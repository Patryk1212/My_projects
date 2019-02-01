//
// Created by ps2-ostrowski on 20/11/2018.
//
#include <cmath>

#include "Vector.h"

Vector::Vector(float x, float y, int speed)
{
    this->x = x;
    this->y = y;
    this->speed = speed;
}

Vector::~Vector()
{

}

void Vector::setX(float x)
{
    this->x = x;
}

void Vector::setY(float y)
{
    this->y = y;
}

void Vector::setSpeed(int speed)
{
    this->speed = speed;
}

float Vector::getX() const
{
    return x;
}

float Vector::getY() const
{
    return y;
}

int Vector::getSpeed() const
{
    return speed;
}

void Vector::normalise()
{
    float magnitude = sqrt(pow(x,2) + pow(y,2));

    x /= magnitude;
    y /= magnitude;
}

Vector Vector::operator*(float scalar)
{
    return Vector(scalar*x, scalar*y);
}