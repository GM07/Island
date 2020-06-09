#include "../../include/headers.h"
#include "../../include/Entities/Player.h"

/**
 * @brief Constructor with parameters
 * @param position              Position
 * @param size                  Size
 * @param movementComponents    Movement component of the player containing its acceleration and all
 */
Player::Player(const Vector& position, const Vector& size, MovementComponents movementComponents)
    :   MovableEntity(position, size, movementComponents)
    ,   attacking_(false)
    ,   sword_(position, Vector(size / 2.0f), 40.0f, Vector(18.0f, 22.0f), sprite_)
{

    // Creating the hitbox component with an offset and a different size than the sprite
    createHitboxComponent(sprite_, Vector(16, 12), Vector(32, 32));
}

/**
 * @brief Destructor
 */
Player::~Player()
{

}

/**
 * @brief Function that updates the player's position, size, ...
 * @param dt        Time since last frame
 */
void Player::update(const float& dt)
{
    // Movement
    updateMovement(dt);
    updateAnimations(dt);

    // Collisions
    hitboxComponent_->update(dt);    

    // Sword
    sword_.setPosition(position_);
    sword_.update(dt);
}

/**
 * @brief Function that draws the player on the window
 * @param window    Window where the player will be drawn into
 */
void Player::render(std::shared_ptr<sf::RenderWindow> target)
{
    Direction direction = getDirection();
    if (direction == DOWN || direction == RIGHT)
    {
        target->draw(sprite_);
        sword_.render(target);
    } else
    {
        sword_.render(target);
        target->draw(sprite_);
    }
    


    //hitboxComponent_->render(target);

}

/**
 * @brief Function that adds a texture to the player (with the animations)
 * @param texture   Texture
 */
void Player::addTexture(std::shared_ptr<sf::Texture> texture_)
{
    // Adding the texture to the sprite
    Entity::addTexture(texture_);

    createAnimationComponent(*texture_);
    
    // Adding the animations (walk, stand, ...)
    initializeAnimations();

}

/**
 * @brief Function that adds a texture to the sword
 * @param texture   Texture
 */
void Player::addSwordTexture(std::shared_ptr<sf::Texture> texture_)
{
    sword_.addTexture(texture_);
}

/**
 * @brief Function that initializes the player's components
 */
void Player::initComponents()
{
}

/**
 * @brief Method that generates every animation needed the player
 */
void Player::initializeAnimations()
{
    animationComponent_->addAnimation(
        "MOVE_LEFT",            // Animation name
        10.0f,                  // Animation speed
        sf::Vector2i(0, 9),     // First of frame's position on texture sheet
        sf::Vector2i(8, 0),     // Number of frames to parcour
        sf::Vector2i(64, 64)
    );

    animationComponent_->addAnimation(
        "MOVE_RIGHT",           // Animation name
        10.0f,                  // Animation speed
        sf::Vector2i(0, 11),    // First of frame's position on texture sheet
        sf::Vector2i(8, 0),    // Number of frames to parcour
        sf::Vector2i(64, 64)
    );

    animationComponent_->addAnimation(
        "MOVE_UP",              // Animation name
        10.0f,                  // Animation speed
        sf::Vector2i(0, 8),     // First of frame's position on texture sheet
        sf::Vector2i(8, 0),     // Number of frames to parcour
        sf::Vector2i(64, 64)
    );

    animationComponent_->addAnimation(
        "MOVE_DOWN",            // Animation name
        10.0f,                  // Animation speed
        sf::Vector2i(0, 10),    // First of frame's position on texture sheet
        sf::Vector2i(8, 0),     // Number of frames to parcour
        sf::Vector2i(64, 64)
    );

    animationComponent_->addAnimation(
        "IDLE",
        10.0f,
        sf::Vector2i(0, 10),
        sf::Vector2i(0, 0),
        sf::Vector2i(64, 64)
    );
}

/**
 * @brief Method that updates the animation according to the velocity
 * @param dt    Time since last frame
 */
void Player::updateAnimations(const float& dt)
{
    Direction direction = getDirection();
    sword_.setDirection(direction);

    // Priority animations
    if (attacking_)
    {
        
    }
    else {
    switch (direction)
        {
            case LEFT:
                animationComponent_->playAnimation("MOVE_LEFT", dt, velocity_.getX(), movementComponents_.maxSpeed_);
                break;
            case RIGHT:
                animationComponent_->playAnimation("MOVE_RIGHT", dt, velocity_.getX(), movementComponents_.maxSpeed_);
                break;
            case UP:
                animationComponent_->playAnimation("MOVE_UP", dt, velocity_.getY(), movementComponents_.maxSpeed_);
                break;
            case DOWN:
                animationComponent_->playAnimation("MOVE_DOWN", dt, velocity_.getY(), movementComponents_.maxSpeed_);
                break;
            default:
                animationComponent_->playAnimation("IDLE", dt);
                break;
        }
    }
}
