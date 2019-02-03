#pragma once

#include <string>

#include <Engine/OGLGame.h>

#include "Vector.h"
#include "Ally.h"

class SMALL_RTS : public ASGE::OGLGame
{
public:

    SMALL_RTS();
    ~SMALL_RTS();
    virtual bool init() override;

private:

    void keyHandler(const ASGE::SharedEventData data);
    void clickHandler(const ASGE::SharedEventData data);

    virtual void update(const ASGE::GameTime &us) override;
    virtual void render(const ASGE::GameTime &us) override;

    void setAllySprite(ASGE::Sprite* image);
    void displayAllySprite(ASGE::Sprite* image);

    void addAlly();

    bool isInside(const ASGE::Sprite* sprite, float x, float y) const;

    Ally ally;
    ASGE::Sprite* tank = nullptr;

    int  key_callback_id = -1;
    int  mouse_callback_id = -1;

    int ally_number = 0;

};


