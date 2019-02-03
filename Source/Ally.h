//
// Created by Patryk on 2019-01-31.
//

#ifndef SMALL_RTS_ALLY_H
#define SMALL_RTS_ALLY_H

#include "Vector.h"

class Ally : public Vector
{
public:

    Ally();
    ~Ally();

    friend class SMALL_RTS;

    void setActive(bool active);

    bool getActive() const;

private:

    ASGE::Sprite* image = nullptr;

    int width = 0;
    int height = 0;

    int x_pos = 0;
    int y_pos = 0;

    int health = 0;
    int damage = 0;
    bool active = false;

};

#endif //SMALL_RTS_ALLY_H
