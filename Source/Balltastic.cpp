#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Balltastic.h"

Balltastic::Balltastic()
{
    game_width = 1024;
    game_height = 768;
}

Balltastic::~Balltastic()
{
    this->inputs->unregisterCallback(key_callback_id);
    this->inputs->unregisterCallback(mouse_callback_id);

}

bool Balltastic::init()
{
    if (!initAPI())
    {
        return false;
    }



    renderer->setWindowTitle("Balltastic Fun");
    renderer->setClearColour(ASGE::COLOURS::BLACK);

    ball = renderer->createRawSprite();
    ball->loadTexture("data/images/8bit_ball.png");
    ball->width(16);
    ball->height(16);


    renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);

    // input handling functions
    key_callback_id = inputs->addCallbackFnc(
            ASGE::E_KEY, &Balltastic::keyHandler, this);

    mouse_callback_id =inputs->addCallbackFnc(
            ASGE::E_MOUSE_CLICK, &Balltastic::clickHandler, this);

    ball->xPos(game_width/2);
    ball->yPos(game_height/2);

    return true;
}

void Balltastic::keyHandler(const ASGE::SharedEventData data)
{
    auto key = static_cast<const ASGE::KeyEvent*>(data.get());

    if (key->key == ASGE::KEYS::KEY_ENTER &&
        key->action == ASGE::KEYS::KEY_RELEASED)
    {
        in_menu = false;

    }
    if (key->key == ASGE::KEYS::KEY_ESCAPE)
    {
        signalExit();
    }
}

void Balltastic::clickHandler(const ASGE::SharedEventData data)
{
    auto click = static_cast<const ASGE::ClickEvent*>(data.get());
    double x_pos = click->xpos;
    double y_pos = click->ypos;
}


void Balltastic::update(const ASGE::GameTime& us)
{
    if (!in_menu)
    {
        velocity.normalise();
        float x_pos = ball->xPos();
        float y_pos = ball->yPos();
        int speed = 500;

        x_pos += speed * velocity.getX() * (us.delta_time.count()/ 1000.f);
        y_pos += speed * velocity.getY() * (us.delta_time.count()/ 1000.f);

        if (y_pos > game_height - ball->height())
        {
            velocity.setY(-velocity.getY());
        }
        else if (y_pos < 0)
        {
            velocity.setY(-velocity.getY());
        }
        else if (x_pos < 0)
        {
            velocity.setX(-velocity.getX());
        }
        else if (x_pos > game_width - ball->height())
        {
            velocity.setX(-velocity.getX());
        }


        ball->xPos(x_pos);
        ball->yPos(y_pos);
    }
}

void Balltastic::render(const ASGE::GameTime &)
{
    renderer->setFont(0);

    if (in_menu)
    {
        renderer->renderText("Press ENTER to start a game", 330, 300, 1.0, ASGE::COLOURS::BLUE);
    }
    else
    {
        renderer->renderSprite(*ball);
        // creates a string with the score appended
        std::string score_str = "SCORE: " + std::to_string(score);

        // renders the string. a std string is not a c string so needs to be converted hence .c_str()
        renderer->renderText(score_str.c_str(), 850, 25, 1.0, ASGE::COLOURS::DARKORANGE);
    }

}
