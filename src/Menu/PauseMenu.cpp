#include "../headers.h"
#include "PauseMenu.h"

/**
 * @brief Constructor
 */
PauseMenu::PauseMenu(std::shared_ptr<sf::RenderTarget> window)
    :   window_(window)
{
    // Background
    background_.setSize(sf::Vector2f(
        static_cast<float>(window->getSize().x),
        static_cast<float>(window->getSize().y)
    ));

    background_.setFillColor(sf::Color(50, 50, 50, 200));

    initFonts();
    initPausedText();
}

/**
 * @brief Destructor
 */
PauseMenu::~PauseMenu()
{

}

/**
 * @brief Function that updates the game state
 * @param dt    time since last frame
 */
void PauseMenu::update(const float& dt)
{
    for (const auto& button : buttons_)
    {
        button.second->update(dt);
    }
}

/**
 * @brief Function that updates the mouse position of the buttons
 */
void PauseMenu::updateMousePosition(Vector mousePosition)
{
    for (const auto& button : buttons_)
    {
        button.second->updateMousePosition(mousePosition);
    }
}

/**
 *  @brief Method that renders the game state
 *  @param target   RenderWindow where the state will be drawn
 */
void PauseMenu::render(std::shared_ptr<sf::RenderTarget> target)
{
    target->draw(background_);

    for (const auto& button : buttons_)
        button.second->render(target);

    target->draw(pausedText_);  
}

/**
 * @brief Method that adds a button to the pause menu
 * @param key                   Key to identify the button
 * @param position              Position of the button to add
 * @param colorButtonHandler    Color handler of the button to add
 */
void PauseMenu::addButton(const std::string& key, Vector position, gui::ColorButtonHandler handler, const std::string& title)
{
    buttons_.emplace(key, std::make_unique<gui::Button>(
        position,
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y),
        &font_,
        handler,
        title
    ));

}

/**
 * @brief Method that returns the button mapped to a certain key
 * @param key       Key mapping to button
 * @return          Reference to button
 */
const gui::Button& PauseMenu::getButton(const std::string& key) const
{
    return *(buttons_.at(key));
}

/**
 * @brief Function that adds a texture to a specified button
 * @param key       Key mapping to button
 * @param texture   Texture to be added
 */
void PauseMenu::addTextureToButton(const std::string& key, std::shared_ptr<sf::Texture> texture)
{
    buttons_[key]->addTexture(texture);
}

/**
 * @brief Function that returns whether the button is pressed or not
 * @param key       Key mapping to button
 * @return          Button pressed or not
 */
bool PauseMenu::isButtonPressed(const std::string& key)
{
    return buttons_.at(key)->getButtonState() == gui::Button_State::CLICKED;
}

/**
 * @brief Function that initializes the state's fonts
 */
void PauseMenu::initFonts()
{
    if (!font_.loadFromFile("fonts/basic_font.ttf"))
    {
        throw("Error : Could not load font : basic_font.ttf");
    }
    
}

/**
 * @brief Method that initializes the paused text
 */
void PauseMenu::initPausedText()
{
    pausedText_.setFont(font_);
    pausedText_.setString("PAUSED");
    pausedText_.setFillColor(sf::Color(255, 255, 255, 200));
    pausedText_.setCharacterSize(25);
    pausedText_.setPosition(
        static_cast<float>(window_->getSize().x) / 2.0f - pausedText_.getGlobalBounds().width / 2.0f, 
        32
    );
}

