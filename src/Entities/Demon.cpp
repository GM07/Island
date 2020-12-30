#include "../headers.h"
#include "Demon.h"

/**
 * @brief Constructor with parameters
 * @param position              Position
 * @param size                  Size
 * @param attractor             Reference to position to follow
 * @param movementComponents    Movement component of the Demon containing its acceleration and all
 * @param texture               Texture of the demon
 */
Demon::Demon(const Vector& position, const Vector& size, const Vector& attractor, MovementComponents movementComponents, std::shared_ptr<sf::Texture> texture)
    :   MovableEntity(position, size, movementComponents, 50.0f)
    ,   attractor_(attractor)
{

    // Creating the hitbox component with an offset and a different size than the sprite
    createHitboxComponent(sprite_, Vector(0, 0), Vector(32, 32));

    if (texture != nullptr)
        addTexture(texture);
}

/**
 * @brief Copy Constructor
 * @param demon     Demon to copy
 */
Demon::Demon(const Demon& demon)
    :   MovableEntity(demon.position_, demon.size_, demon.movementComponents_)
    ,   attractor_(demon.attractor_)
{
    sprite_ = demon.sprite_;

    // Creating the hitbox component with an offset and a different size than the sprite
    createHitboxComponent(sprite_, Vector(0, 0), Vector(32, 32));
}

/**
 * @brief Destructor
 */
Demon::~Demon()
{

}

/**
 * @brief Function that updates the Demon's position, size, ...
 * @param dt        Time since last frame
 */
void Demon::update(const float& dt)
{
    if (!damaged_)
    {
        attract();
    }
    
    updateMovement(dt);
    updateDamage();
    hitboxComponent_->update(dt); 
 
    updateAnimations(dt);
}

/**
 * @brief Function that draws the Demon on the window
 * @param window    Window where the Demon will be drawn into
 */
void Demon::render(std::shared_ptr<sf::RenderTarget> target)
{
    if (damaged_)
    {
        sprite_.setColor(sf::Color::Red);
        hitboxComponent_->setOutlineColor(sf::Color::Yellow);
    }
    else
    {
        sprite_.setColor(sf::Color::White);
        hitboxComponent_->setOutlineColor(sf::Color::Red);
    }
    
    target->draw(sprite_);
    hitboxComponent_->render(target);
}

/**
 * @brief Function that adds a texture to the Demon (with the animations)
 * @param texture   Texture
 */
void Demon::addTexture(std::shared_ptr<sf::Texture> texture_)
{

    // Adding the texture to the sprite
    Entity::addTexture(texture_);

    createAnimationComponent(*texture_);
    
    // Adding the animations
    initializeAnimations();

}

/**
 * @brief Function that attracts the demon to the attractor
 */
void Demon::attract()
{
    Vector dp = attractor_ - (position_) - size_ * 0.25f;
    if (dp.norm() > 1.0f)
        velocity_ = (dp / (dp.norm())) * movementComponents_.maxSpeed_;
    else
        velocity_ = 0;
}

/**
 * @brief Method that generates every animation needed the player
 */
void Demon::initializeAnimations()
{
    animationComponent_->addAnimation(
        "MOVE",
        10.0f,
        sf::Vector2i(0, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(32, 32)
    );
}

/**
 * @brief Method that updates the animation according to the velocity
 * @param dt    Time since last frame
 */
void Demon::updateAnimations(const float& dt)
{
    animationComponent_->playAnimation("MOVE", dt);
}