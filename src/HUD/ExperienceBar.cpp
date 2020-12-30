#include "../headers.h"
#include "ExperienceBar.h"

/**
 * @brief Constructor
 * @param font      Font needed to draw the experience number
 * @param size      Size of the bar
 * @param position  Position of the bar
 */
HUD::ExperienceBar::ExperienceBar(sf::Font& font, const Vector& size, const Vector& position)
    :   experience_(0.0f)
{
    bar_.setOutlineColor(sf::Color(51, 51, 51));
    bar_.setOutlineThickness(1.0f);
    bar_.setFillColor(sf::Color::Transparent);
    bar_.setSize(size.getAsVector2f());
    bar_.setPosition(position.getAsVector2f());

    insideBar_.setFillColor(sf::Color::Green);
    insideBar_.setSize(sf::Vector2f(0.0f, size.getY()));
    insideBar_.setPosition(position.getAsVector2f());

    experienceNumber_.setPosition((position + size * 0.5f).getAsVector2f());
    experienceNumber_.setFont(font);
    experienceNumber_.setColor(sf::Color(51, 51, 51));
    experienceNumber_.setString(std::to_string((int) experience_));
    experienceNumber_.setPosition(experienceNumber_.getPosition() - sf::Vector2f(experienceNumber_.getGlobalBounds().width / 2.0f, 0.0f));

}

/**
 * @brief Function that updates the player's position, size, ...
 * @param dt        Time since last frame
 */
void HUD::ExperienceBar::update(const float& dt)
{
    float size = (experience_ - std::floor(experience_)) * bar_.getSize().x;
    insideBar_.setSize(sf::Vector2f(size, bar_.getSize().y));
    experienceNumber_.setString(std::to_string((int) experience_));

}

/**
 * @brief Function that draws the player on the window
 * @param window    Window where the player will be drawn into
 */
void HUD::ExperienceBar::render(std::shared_ptr<sf::RenderTarget> target)
{
    target->draw(insideBar_);
    target->draw(bar_);
    target->draw(experienceNumber_);
}
