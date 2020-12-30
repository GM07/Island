#include "../headers.h"
#include "ColorButtonHandler.h"

/**
 * @brief Constructor
 * @param color             Base color
 * @param hoverColor        Color when mouse is on button
 * @param clickedColor      Color when button is clicked
 * @param offColor          Color when button is disabled
 * @param textColor         Text color
 * @param shadowTextColor   Color of the text's shadow
 */
gui::ColorButtonHandler::ColorButtonHandler(
    sf::Color color,
    sf::Color hoverColor,
    sf::Color clickedColor,
    sf::Color offColor,
    sf::Color textColor,
    sf::Color shadowTextColor,
    sf::Color outlineColor,
    sf::Color outlineHoverColor,
    sf::Color outlineClickedColor,
    sf::Color outlineOffColor
)
    :   color_(color)
    ,   hoverColor_(hoverColor)
    ,   clickedColor_(clickedColor)
    ,   offColor_(offColor)
    ,   textColor_(textColor)
    ,   shadowTextColor_(shadowTextColor)
    ,   outlineColor_(outlineColor)
    ,   outlineHoverColor_(outlineHoverColor)
    ,   outlineClickedColor_(outlineClickedColor)
    ,   outlineOffColor_(outlineOffColor)
{}

/**
 * @brief Destructor
 */
gui::ColorButtonHandler::~ColorButtonHandler()
{
    
}

/**
 * @brief Function that returns the main color
 * @return Main color
 */
sf::Color gui::ColorButtonHandler::getColor() const
{
    return color_;
}

/**
 * @brief Function that returns the hover color
 * @return Hover color
 */
sf::Color gui::ColorButtonHandler::getHoverColor() const
{
    return hoverColor_;
}

/**
 * @brief Function that returns the color when button is clicked
 * @return Clicked color
 */
sf::Color gui::ColorButtonHandler::getClickedColor() const
{
    return clickedColor_;
}

/**
 * @brief Function that returns the color when button is disabled
 * @return Off color
 */
sf::Color gui::ColorButtonHandler::getOffColor() const
{
    return offColor_;
}

/**
 * @brief Function that returns the text color
 * @return Text color
 */
sf::Color gui::ColorButtonHandler::getTextColor() const
{
    return textColor_;
}

/**
 * @brief Function that returns the color of the text's shadow
 * @return Off color
 */
sf::Color gui::ColorButtonHandler::getShadowTextColor() const
{
    return shadowTextColor_;
}


/**
 * @brief Function that returns the main outline color
 * @return Main color
 */
sf::Color gui::ColorButtonHandler::getOutlineColor() const
{
    return outlineColor_;
}

/**
 * @brief Function that returns the hover outline color
 * @return Hover color
 */
sf::Color gui::ColorButtonHandler::getOutlineHoverColor() const
{
    return outlineHoverColor_;
}

/**
 * @brief Function that returns the outline color when button is clicked
 * @return Clicked color
 */
sf::Color gui::ColorButtonHandler::getOutlineClickedColor() const
{
    return outlineClickedColor_;
}

/**
 * @brief Function that returns the outline color when button is disabled
 * @return Off color
 */
sf::Color gui::ColorButtonHandler::getOutlineOffColor() const
{
    return outlineOffColor_;
}

/**
 * @brief Function that returns the object but without an outline color
 * @return Object without outline
 */
gui::ColorButtonHandler gui::ColorButtonHandler::getWithoutOutline() const
{
    return gui::ColorButtonHandler(color_, hoverColor_, clickedColor_, offColor_, textColor_, shadowTextColor_);
}

/**
 * @brief Function that changes the main color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setColor(sf::Color color)
{
    color_ = color;
}

/**
 * @brief Function that changes the hover color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setHoverColor(sf::Color color)
{
    hoverColor_ = color;
}

/**
 * @brief Function that changes the color when the button is clicked
 * @param color     New Color
 */
void gui::ColorButtonHandler::setClickedColor(sf::Color color)
{
    clickedColor_ = color;
}

/**
 * @brief Function that changes the off color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setOffColor(sf::Color color)
{
    offColor_ = color;
}

/**
 * @brief Function that changes the text color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setTextColor(sf::Color color)
{
    textColor_ = color;
}

/**
 * @brief Function that changes the text's shadow color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setShadowTextColor(sf::Color color)
{
    shadowTextColor_ = color;
}


/**
 * @brief Function that changes the main outline color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setOutlineColor(sf::Color color)
{
    outlineColor_ = color;
}

/**
 * @brief Function that changes the hover outline color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setOutlineHoverColor(sf::Color color)
{
    outlineHoverColor_ = color;
}

/**
 * @brief Function that changes the outline color when the button is clicked
 * @param color     New Color
 */
void gui::ColorButtonHandler::setOutlineClickedColor(sf::Color color)
{
    outlineClickedColor_ = color;
}

/**
 * @brief Function that changes the off outline color
 * @param color     New Color
 */
void gui::ColorButtonHandler::setOutlineOffColor(sf::Color color)
{
    outlineOffColor_ = color;
}
