//
// Created by ps2-ostrowski on 20/11/2018.
//

#include "Vector.h"
#include <cmath>

Vector::Vector(float x1, float y1) {
        x =x1;
        y = y1;
}

Vector::~Vector() {

}

void Vector::setX(float x1) {
        x = x1;
}

void Vector::setY(float y1) {
        y = y1;
}

float Vector::getX() {
        return x;
}

float Vector::getY() {
        return y;
}

void Vector::normalise()
{
        speed = sqrt(pow(x,2) + pow(y,2));

        x /= speed;
        y /= speed;
}

Vector Vector::operator*(float scalar)
{
        return Vector(scalar*x, scalar*y);
}
