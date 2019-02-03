#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "SMALL_RTS.h"

SMALL_RTS::SMALL_RTS()
{
    game_width = 1280;
    game_height = (game_width*9)/16;
}

SMALL_RTS::~SMALL_RTS()
{
    this->inputs->unregisterCallback(key_callback_id);
    this->inputs->unregisterCallback(mouse_callback_id);

}

bool SMALL_RTS::init()
{
    if (!initAPI())
    {
        return false;
    }

    renderer->setWindowTitle("SMALL RTS DEMO");
    renderer->setClearColour(ASGE::COLOURS::BLACK);


    tank = renderer->createRawSprite();
    tank->loadTexture("/data/images/enemy.png");
    tank->width(50);
    tank->height(75);
    tank->xPos(game_width/2);
    tank->yPos(game_height/2);


    renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

    // input handling functions
    key_callback_id = inputs->addCallbackFnc(
            ASGE::E_KEY, &SMALL_RTS::keyHandler, this);

    mouse_callback_id =inputs->addCallbackFnc(
            ASGE::E_MOUSE_CLICK, &SMALL_RTS::clickHandler, this);

    return true;
}

void SMALL_RTS::keyHandler(const ASGE::SharedEventData data)
{
    auto key = static_cast<const ASGE::KeyEvent*>(data.get());

    if(key->key == ASGE::KEYS::KEY_ESCAPE && key->action == ASGE::KEYS::KEY_PRESSED)
    {
        signalExit();
    }

}

void SMALL_RTS::clickHandler(const ASGE::SharedEventData data)
{
    auto click = static_cast<const ASGE::ClickEvent*>(data.get());
    double x_pos = click->xpos;
    double y_pos = click->ypos;

    if(isInside(tank, x_pos, y_pos))
    {

    }

}


void SMALL_RTS::update(const ASGE::GameTime &us)
{
    //Ally* ally = new Ally;

    //setAllySprite(ally->image);


}

void SMALL_RTS::render(const ASGE::GameTime &us)
{

    //displayAllySprite(ally->image);

    renderer->renderSprite(*tank);
}

void SMALL_RTS::setAllySprite(ASGE::Sprite* image)
{
    image = renderer->createRawSprite();
    image->loadTexture("/data/images/enemy.png");
    image->width(50);
    image->height(75);
    image->xPos(game_width/2);
    image->yPos(game_height/2);
}

void SMALL_RTS::addAlly()
{
    ally_number++;
    Ally* ally = new Ally[ally_number];


}

void SMALL_RTS::displayAllySprite(ASGE::Sprite *image)
{
    renderer->renderSprite(*image);
}

bool SMALL_RTS::isInside(const ASGE::Sprite* sprite, float x, float y) const
{
    float width = sprite->xPos() + sprite->width();
    float height = sprite->yPos() + sprite->height();

    return x > sprite->xPos() && x < width && y > sprite->yPos() && y < height;
}
