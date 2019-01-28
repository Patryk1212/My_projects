#include <string>

#include <Engine/Keys.h>
#include <Engine/Input.h>
#include <Engine/InputEvents.h>
#include <Engine/Sprite.h>

#include "Balltastic.h"

/**
*   @brief   Default Constructor.
*   @details Consider setting the game's width and height
             and even seeding the random number generator.
*/
Balltastic::Balltastic()
{
    game_width = 1024;
    game_height = 768;
    std::srand(time(NULL));
}

/**
*   @brief   Destructor.
*   @details Remove any non-managed memory and callbacks.
*/
Balltastic::~Balltastic()
{
    this->inputs->unregisterCallback(key_callback_id);
    this->inputs->unregisterCallback(mouse_callback_id);

    if (background)
    {
        delete background;
        background = nullptr;
    }

    if (ball)
    {
        delete ball;
        ball = nullptr;
    }
}

/**
*   @brief   Initialises the game.
*   @details The game window is created and all assets required to
			 run the game are loaded. The keyHandler and clickHandler
			 callback should also be set in the initialise function.
*   @return  True if the game initialised correctly.
*/
bool Balltastic::init()
{
    // initialises the graphics API, check to make sure it was a success
    if (!initAPI())
    {
        return false;
    }

    // disable sprite batching for simplicity
    renderer->setSpriteMode(ASGE::SpriteSortMode::IMMEDIATE);
    renderer->setWindowTitle("Balltastic Fun");
    renderer->setClearColour(ASGE::COLOURS::BLACK);

    toggleFPS();

    ball = renderer->createRawSprite();
    ball->loadTexture("data/images/8bit_ball.png");
    ball->width(16);
    ball->height(16);

    // input handling functions
    key_callback_id = inputs->addCallbackFnc(
            ASGE::E_KEY, &Balltastic::keyHandler, this);

    mouse_callback_id =inputs->addCallbackFnc(
            ASGE::E_MOUSE_CLICK, &Balltastic::clickHandler, this);

    ball->xPos(game_width/2);
    ball->yPos(game_height/2);

    return true;
}

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
			 keyboard input. For this game, calls to this function
			 are thread safe, so you may alter the game's state as you
			 see fit.
*   @param   data The event data relating to key input.
*   @see     KeyEvent
*   @return  void
*/
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

/**
*   @brief   Processes any key inputs
*   @details This function is added as a callback to handle the game's
		     mouse button input. For this game, calls to this function
             are thread safe, so you may alter the game's state as you
             see fit.
*   @param   data The event data relating to key input.
*   @see     ClickEvent
*   @return  void
*/
void Balltastic::clickHandler(const ASGE::SharedEventData data)
{
    auto click = static_cast<const ASGE::ClickEvent*>(data.get());
    double x_pos = click->xpos;
    double y_pos = click->ypos;
}



/**
*   @brief   Updates the scene
*   @details Prepares the renderer subsystem before drawing the
		     current frame. Once the current frame is has finished
		     the buffers are swapped accordingly and the image shown.
*   @return  void
*/
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



        // move the ball in the upward direction, say 500pixels/sec?
        // delta time is measured in milliseconds, so divide by 1000 and multiply
        // use us for the delta measurements

        ball->xPos(x_pos);
        ball->yPos(y_pos);
    }
}

/**
*   @brief   Renders the scene
*   @details Renders all the game objects to the current frame.
	         Once the current frame is has finished the buffers are
			 swapped accordingly and the image shown.
*   @return  void
*/
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
