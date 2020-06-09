#include "../../include/headers.h"
#include "../../include/Entities/Sword.h"


/**
 * @brief Constructor
 * @param position          Position of the sword
 * @param size              Size of the sword
 * @param attackDamage      Attack of the sword
 * @param offset            Where to draw the sword relative to the player's sprite
 * @param playerSprite      Player's sprite
 */
Sword::Sword(const Vector& position, const Vector& size, float attackDamage, const Vector& offset, const sf::Sprite& playerSprite)
    :   Entity(position, size)
    ,   attackDamage_(attackDamage)
    ,   offset_(offset)
    ,   playerSprite_(playerSprite)
{
    sprite_.setPosition((Vector(playerSprite_.getPosition()) + offset_).getAsVector2f());
    createHitboxComponent(const_cast<sf::Sprite&>(playerSprite_), offset_, size_);
}

/**
 * @brief Destructor
 */
Sword::~Sword()
{

}

/**
 * @brief Function that updates the player's position, size, ...
 * @param dt        Time since last frame
 */
void Sword::update(const float& dt)
{
    sprite_.setPosition((Vector(playerSprite_.getPosition()) + offset_).getAsVector2f());
    hitboxComponent_->update(dt);
}

/**
 * @brief Function that draws the player on the window
 * @param window    Window where the player will be drawn into
 */
void Sword::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(sprite_);
    //hitboxComponent_->render(target);
}

/**
 * @brief Function that adds a texture to the player (with the animations)
 * @param texture   Texture
 */
void Sword::addTexture(std::shared_ptr<sf::Texture> texture_)
{
    sprite_.setTexture(*texture_);
}

/**
 * @brief Function that changes the direction of the player
 * @param direction         New direction
 */
void Sword::setDirection(Direction direction)
{
    switch (direction)
    {
    case LEFT:
        sprite_.setScale(-1, 1);
        sprite_.setOrigin(sf::Vector2f(size_.getX() / 2.0f, 0.0f));
        break;
    case RIGHT:
        sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
        sprite_.setScale(1, 1);
        break;
    case UP:
        sprite_.setScale(-1, 1);
        sprite_.setOrigin(sf::Vector2f(size_.getX() - 4.0f, 6.0f));
        break;
    case DOWN:
        sprite_.setScale(1, 1);
        sprite_.setOrigin(sf::Vector2f(0.0f, 0.0f));
        break;
    default:
        break;
    }
}

/**
 * @brief Function that returns the attack damage of the sword
 * @return          Attack damage
 */
float Sword::getAttackDamage() const
{
    return attackDamage_;
}

