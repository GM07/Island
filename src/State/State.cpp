#include "../../include/headers.h"
#include "../../include/State/State.h"

/**
 * @brief Constructor with parameters
 * @param states    Stack of the states in the game
 * @param window    Window where the state will be drawn into
 * @param keys      Keys supported by the game
 */
State::State(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys)
    :   window_(window)
    ,   states_(states)
    ,   keys_(keys)
    ,   keyTime_(0)
    ,   keyTimeMax_(10.0f)
    ,   paused_(false)
    ,   quit_(false)
{

}
/**
 * @brief Destructor
 */
State::~State()
{

}

/**
 * @brief Function that ends the state
 */
void State::endState()
{
    quit_ = true;
}

/**
 * @brief Function that updates the key time
 * @param dt        Time since last frame
 */
void State::updateKeyTime(const float& dt)
{
    if (keyTime_ <= keyTimeMax_)
        keyTime_ += 50.0f * dt;
}

/**
 * @brief Method that updates the mouse position
 */
void State::updateMousePosition()
{
    mousePositionScreen = sf::Mouse::getPosition();
    mousePositionWindow = sf::Mouse::getPosition(*window_);
    mousePositionView = window_->mapPixelToCoords(sf::Mouse::getPosition(*window_));
}

/**
 * @brief Method that pauses the state
 */
void State::pause()
{
    paused_ = true;
}


/**
 * @brief Method that unpauses the state
 */
void State::unpause()
{
    paused_ = false;
}

/**
 * @brief Function that returns whether the states has to end of not
 * @return Whether the state has to end or not
 */
const bool& State::getQuit() const
{
    return quit_;
}

/**
 * @brief Function that returns whether we can press a key or not
 * @return Key can be pressed or not
 */
bool State::getKeyTime()
{
    if (keyTime_ >= keyTimeMax_)
    {
        keyTime_ = 0;
        return true;
    }
    return false;
}