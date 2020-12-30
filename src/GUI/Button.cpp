#include "../headers.h"
#include "Button.h"

const float gui::Button::BUTTON_SIZE_X = 200;
const float gui::Button::BUTTON_SIZE_Y = 50;

/**
 * @brief Constructor
 * @param position      Position of the button
 * @param size          Size of the button
 * @param font          Font of the text
 * @param title         Text on the button
 * @param characterSize Character size of the font
 */
gui::Button::Button(
    Vector position, Vector size, 
    sf::Font* font,
    ColorButtonHandler colorButtonHandler,
    std::string title, 
    unsigned int characterSize
)
    :   buttonState_(Button_State::NORMAL)
    ,   position_(position)
    ,   size_(size)
    ,   colorButtonHandler_(colorButtonHandler)
    ,   title_(title)
    ,   characterSize_(characterSize)
    ,   rect_(size_.getAsVector2f())
    ,   font_(font)
    ,   text_(title, *font, characterSize)
    ,   shadowText_(title, *font, characterSize)
{
    // Rectangle settings  
    rect_.setPosition(position_.getAsVector2f());
    rect_.setFillColor(colorButtonHandler_.getColor());
    if (colorButtonHandler.getOutlineColor() != sf::Color::Transparent ||
        colorButtonHandler.getOutlineHoverColor() != sf::Color::Transparent ||
        colorButtonHandler.getOutlineClickedColor() != sf::Color::Transparent ||
        colorButtonHandler.getOutlineOffColor() != sf::Color::Transparent)
    {
        rect_.setOutlineColor(colorButtonHandler_.getOutlineColor());
        rect_.setOutlineThickness(1.0f);
    }
    
    if (!font_)
        throw("Error : Font not initialized when creating button");

    // Text settings
    text_.setPosition(rect_.getPosition());
    text_.setFillColor(colorButtonHandler_.getTextColor());
    shadowText_.setPosition(rect_.getPosition());
    shadowText_.setFillColor(colorButtonHandler_.getShadowTextColor());

    // Sprite settings
    sprite_.setPosition(rect_.getPosition());
    sprite_.setColor(colorButtonHandler_.getColor());

    updateText();
}

/**
 * @brief Copy constructor
 * @param button    Button to copy
 */
gui::Button::Button(const gui::Button& button)
    :   buttonState_(Button_State::NORMAL)
    ,   position_(button.position_.getX(), button.position_.getY())
    ,   size_(button.size_.getX(), button.size_.getY())
    ,   colorButtonHandler_(button.colorButtonHandler_)
    ,   title_(button.title_)
    ,   characterSize_(button.characterSize_)
    ,   rect_(button.rect_)
    ,   font_(button.font_)
    ,   text_(button.title_, *button.font_, button.characterSize_)
    ,   shadowText_(button.title_, *button.font_, button.characterSize_)
{
    // Rectangle settings  
    rect_.setPosition(position_.getAsVector2f());
    rect_.setFillColor(colorButtonHandler_.getColor());
    rect_.setOutlineColor(colorButtonHandler_.getOutlineColor());
    rect_.setOutlineThickness(1.0f);
    
    if (!font_)
        throw("Error : Font not initialized when creating button");

    // Rectangle settings  
    rect_.setPosition(position_.getAsVector2f());
    rect_.setFillColor(colorButtonHandler_.getColor());
    
    if (!font_)
        throw("Error : Font not initialized when creating button");

    // Text settings
    text_.setPosition(rect_.getPosition());
    text_.setFillColor(colorButtonHandler_.getTextColor());
    shadowText_.setPosition(rect_.getPosition());
    shadowText_.setFillColor(colorButtonHandler_.getShadowTextColor());

    // Sprite settings
    sprite_.setPosition(rect_.getPosition());
    sprite_.setColor(colorButtonHandler_.getColor());

    updateText();
}

gui::Button::~Button()
{ }

/**
 * @brief Function that updates the color button and the pressed variable
 * @param mousePosition     Position of the mouse
 */
void gui::Button::updateMousePosition(const Vector& mousePosition)
{
    bool hovered = rect_.getGlobalBounds().contains(mousePosition.getAsVector2f());
    bool clicked = hovered && sf::Mouse::isButtonPressed(sf::Mouse::Left);

    buttonState_ = static_cast<Button_State>(hovered + clicked);
}

/**
 * @brief Function that updates the button (changes the color based on its state and updates the rectangle's position and size)
 * @param dt    time since last frame
 */
void gui::Button::update(const float& dt)
{

    // Adujsting rectangle
    rect_.setPosition(position_.getAsVector2f());
    rect_.setSize(size_.getAsVector2f());

    updateText();

    // Updating button's color
    switch (buttonState_)
    {
        case NORMAL:
            rect_.setFillColor(colorButtonHandler_.getColor());
            rect_.setOutlineColor(colorButtonHandler_.getOutlineColor());
            sprite_.setColor(colorButtonHandler_.getColor());
            break;
        case HOVER:
            rect_.setFillColor(colorButtonHandler_.getHoverColor());
            rect_.setOutlineColor(colorButtonHandler_.getOutlineHoverColor());
            sprite_.setColor(colorButtonHandler_.getHoverColor());
            break;
        case CLICKED:
            rect_.setFillColor(colorButtonHandler_.getClickedColor());
            rect_.setOutlineColor(colorButtonHandler_.getOutlineClickedColor());
            sprite_.setColor(colorButtonHandler_.getClickedColor());
            break;
        case OFF:
            rect_.setFillColor(colorButtonHandler_.getOffColor());
            rect_.setOutlineColor(colorButtonHandler_.getOutlineOffColor());
            sprite_.setColor(colorButtonHandler_.getOffColor());
            break;
        default:
            throw("Error : Button state not defined");
            break;
    }
}

/**
 *  @brief Function that renders the button
 *  @param target   RenderWindow where the state will be drawn
 */
void gui::Button::render(std::shared_ptr<sf::RenderTarget> target)
{
    if (target)
    {
        target->draw(rect_);
        target->draw(sprite_);
        target->draw(shadowText_);
        target->draw(text_);
    }
    else
        throw("Error : Cannot draw button : Target is null");
    
    
}

/**
 * @brief Function that adds a texture to the button (changes the sprite too)
 * @param texture   Shared pointer pointing to the texture
 */
void gui::Button::addTexture(std::shared_ptr<sf::Texture> texture)
{
    texture_ = texture;
    sprite_.setTexture(*texture_);
}


/**
 * @brief Function that returns the state of the button
 * @return Button's state
 */
gui::Button_State gui::Button::getButtonState() const
{
    return buttonState_;
}

/**
 * @brief Function that returns the position of the button
 * @return Button's position
 */
Vector gui::Button::getPosition() const
{
    return position_;
}

/**
 * @brief Function that returns the size of the button
 * @return Button's size
 */
Vector gui::Button::getSize() const
{
    return size_;
}

/**
 * @brief Function that returns the title of the button
 * @return Title
 */
const std::string& gui::Button::getTitle() const
{
    return title_;
}

/**
 * @brief Function that changes the state of the button
 * @param state Button's state
 */
void gui::Button::setButtonState(const Button_State& state)
{
    buttonState_ = state;
    update(0);
}

/**
 * @brief Function that changes the button's position
 * @param position  Button's position
 */
void gui::Button::setPosition(const Vector& position)
{
    position_ = position;
    rect_.setPosition(position_.getX(), position_.getY());
}

/**
 * @brief Function that changes the button's size
 * @param position  Button's size
 */
void gui::Button::setSize(const Vector& size)
{
    size_ = size;
    rect_.setSize(sf::Vector2f(size_.getX(), size_.getY()));
}

/**
 * @brief Function that changes the button's title
 * @param title     New title
 */
void gui::Button::setTitle(const std::string& title)
{
    title_ = title;
    text_.setString(title);
    shadowText_.setString(title);
}

/**
 * @brief Function that updates the text
 */
void gui::Button::updateText()
{
    text_.setPosition(
        position_.getX() + size_.getX() / 2.0f - (text_.getGlobalBounds().width) / 2.0f,
        position_.getY() + size_.getY() / 2.0f - (text_.getGlobalBounds().height * 1.5f) / 2.0f
    );
    shadowText_.setPosition(
        text_.getPosition().x + 1,
        text_.getPosition().y + 1   
    );

}