#include "../headers.h"
#include "Player.h"

/**
 * @brief Constructor with parameters
 * @param position              Position
 * @param size                  Size
 * @param movementComponents    Movement component of the player containing its acceleration and all
 */
Player::Player(const Vector& position, const Vector& size, MovementComponents movementComponents)
    :   MovableEntity(position, size, movementComponents)
    ,   attacking_(false)
    ,   sword_(position, Vector(size / 2.0f), 40.0f, 
            {   
                { LEFT, Vector(28.0f, 48.0f)  }, 
                { RIGHT, Vector(24.0f, 48.0f)  }, 
                { UP, Vector(44.0f, 48.0f)   }, 
                { DOWN, Vector(21.0f, 48.0f) },
                { NOT_MOVING, Vector(21.0f, 48.0f)} 
            },
            sprite_)
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
void Player::render(std::shared_ptr<sf::RenderTarget> target)
{
    Direction direction = getDirection();
    if (direction == DOWN || direction == RIGHT || direction == NOT_MOVING)
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
    sword_.initializeAnimations(attackSpeed_);
}

/**
 * @brief Function that handles mouse events
 * @param mousePosition     Mouse position
 */
void Player::handleMouseEvents(const Vector& mousePosition)
{
    sword_.handleMouseEvents(mousePosition);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && damageClock_.getElapsedTime().asSeconds() >= attackSpeed_ * 2)
    {
        damageClock_.restart();
        attack();
    }

    sword_.isActivated() = attacking_ = damageClock_.getElapsedTime().asSeconds() < attackSpeed_;

}

/**
 * @brief Function that applies a force on the entity
 * @param force         Force (only the direction is taken into account)
 */
void Player::applyForce(const Vector& force)
{
    if (force.getX() > 0)
    {
        availableDirections[LEFT] = false;
    } else if (force.getX() < 0)
    {
        availableDirections[RIGHT] = false;
    }

    if (force.getY() > 0)
    {
        availableDirections[UP] = false;
    } else if (force.getY() < 0)
    {
        availableDirections[DOWN] = false;
    }

    position_ += force;

    if (force.getX() != 0)
        velocity_.setX(0);

    if (force.getY() != 0)
        velocity_.setY(0);
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

    sword_.setDirection(direction);

}

void Player::addExperienceBar(HUD::ExperienceBar* experienceBar)
{
    experienceBar_ = experienceBar;
}
