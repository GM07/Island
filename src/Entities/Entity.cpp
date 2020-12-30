#include "../headers.h"
#include "Entity.h"

/**
 * @brief Function that intializes the shape of the entity
 */
void Entity::initShape()
{
    rect_.setSize(size_.getAsVector2f());
    rect_.setFillColor(sf::Color::White);
    rect_.setPosition(position_.getAsVector2f());

    sprite_.setPosition(rect_.getPosition());
}

/**
 * @brief Constructor with parameters
 * @param position  Position
 * @param size      Size
 */
Entity::Entity(Vector position, Vector size)
    :   position_(position)
    ,   size_(size)
{
    center_ = position_ + size_ * 0.5f;
    initShape();
}

/**
 * @brief Destructor
 */
Entity::~Entity()
{
    
}

/**
 * @brief Function that adds a texture to the button (changes the sprite too)
 * @param texture   Shared pointer pointing to the texture
 */
void Entity::addTexture(std::shared_ptr<sf::Texture> texture)
{
    sprite_.setTexture(*texture);
}

/**
 * @brief Method that creates the animation component
 * @param textureSheet  Texture sheet to use for the animations
 */
void Entity::createAnimationComponent(sf::Texture& textureSheet)
{
    animationComponent_ = std::make_unique<AnimationComponent>(sprite_, textureSheet);
}

/**
 * @brief Method that creates the hitbox component
 * @param sprite    Sprite
 * @param offset    Offset of the hitbox in the sprite
 * @param size      Size of the hitbox
 */
void Entity::createHitboxComponent(sf::Sprite& sprite, const Vector& offset, const Vector& size)
{
    hitboxComponent_ = std::make_unique<HitboxComponent>(sprite, offset, size);
}

/**
 * @brief Function that returns the entity's position
 * @return position
 */
const Vector& Entity::getPosition() const
{
    return position_;
}

/**
 * @brief Function that returns the entity's size
 * @return size
 */
const Vector& Entity::getSize() const
{
    return size_;
}

/**
 * @brief Function that returns the entity's center
 */
const Vector& Entity::getCenter() const
{
    return center_;
}

/**
 * @brief Function that returns the hitbox of the player
 * @return hitbox
 */
const HitboxComponent& Entity::getHitbox() const
{
    return *hitboxComponent_;
}

/**
 * @brief Function that changes the entity's position
 * @param position      New position
 */
void Entity::setPosition(const Vector& position)
{
    position_ = position;
}

/**
 * @brief Function that changes the entity's size
 * @param size      New size
 */
void Entity::setSize(const Vector& size)
{
    size_ = size;
}