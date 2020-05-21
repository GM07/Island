#include "../../include/headers.h"
#include "../../include/Entities/HitboxComponent.h"

/**
 * @brief Constructor
 * @param sprite    Sprite
 * @param offset    Offset of the hitbox in the sprite
 * @param size      Size of the hitbox
 */
HitboxComponent::HitboxComponent(sf::Sprite& sprite, Vector offset, Vector size)
    :   offset_(offset),
        sprite_(sprite)
{
    // Creating the hitbox
    hitbox_.setSize(size.getAsVector2f());
    hitbox_.setPosition(sprite.getPosition().x + offset.getX(), sprite.getPosition().y + offset.getY());
    hitbox_.setFillColor(sf::Color::Transparent);
    hitbox_.setOutlineColor(sf::Color::Red);
    hitbox_.setOutlineThickness(1.0f);
}

/**
 * @brief Destructor
 */
HitboxComponent::~HitboxComponent()
{

}

/**
 * @brief Method that updates the hitbox component
 * @param dt    Time since last frame
 */
void HitboxComponent::update(const float& dt)
{
    // TO CONTINUE (dt not used)
    float a = dt - dt;
    hitbox_.setPosition(sprite_.getPosition().x + offset_.getX() + a, sprite_.getPosition().y + offset_.getY());
}

/**
 * @brief Method that renders the hitbox component
 * @param window    Target where the draw the hitbox
 */
void HitboxComponent::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(hitbox_);
}

/**
 * @brief Function that returns whether a rectangle intersects with the hitbox
 * @param rect      Rectangle
 */
bool HitboxComponent::isIntersecting(const sf::FloatRect& rect) const
{
    return hitbox_.getGlobalBounds().intersects(rect);
}

/**
 * @brief Function that returns the hitbox
 * @return hitbox
 */
sf::FloatRect HitboxComponent::getHitbox() const
{
    return hitbox_.getGlobalBounds();
}