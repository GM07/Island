#include "../headers.h"
#include "MovableEntity.h"


/**
 * @brief Constructor with parameters
 * @param position              Position
 * @param size                  Size
 * @param movementComponents    Movememnt component of the entity containing all its movement information
 * @param life                  Entity's life points
 */
MovableEntity::MovableEntity(Vector position, Vector size, MovementComponents movementComponents, float life)
    :   Entity(position, size)
    ,   movementComponents_(movementComponents)
    ,   velocity_(0, 0)
    ,   acceleration_(0, 0)
    ,   availableDirections({true, true, true, true})
    ,   damaged_(false)
    ,   life_(life)
{}

/**
 * @brief Destructor
 */
MovableEntity::~MovableEntity()
{}

/**
 * @brief Method that updates everything related to the movement of the entity
 * @param dt    Time since last frame
 */
void MovableEntity::updateMovement(const float& dt)
{   
    // Updating variables
    validateMaxSpeed(velocity_);
    applyDeceleration(velocity_);
    
    position_ += velocity_ * dt;
    center_ = position_ + size_ * 0.5f;

    // Updating objects on screen
    rect_.setPosition(position_.getAsVector2f());
    sprite_.setPosition(position_.getAsVector2f()); 

}

/**
 * @brief Method that moves the entity in a certain diretion according to it's movement speed
 * @param dx            Movement in the x direction
 * @param dy            Movement in the y direction
 */
void MovableEntity::move(const float& dx, const float& dy)
{
    Vector movement(dx, dy);

    acceleration_ = Vector(dx, dy) * movementComponents_.movementAcceleration_;
    velocity_ += acceleration_;

    updateDirection(movement);

}

/**
 * @brief Method that checks whether
 * the maximum velocity has been reached
 * @param   velocity    Velocity
 */
void MovableEntity::validateMaxSpeed(Vector& velocity)
{
    float x = velocity.getX();
    float y = velocity.getY();

    // X Component
    if (x > movementComponents_.maxSpeed_)
        velocity.setX(movementComponents_.maxSpeed_);
    else if (x < -movementComponents_.maxSpeed_)
        velocity.setX(-movementComponents_.maxSpeed_);

    // Y Component
    if (y > movementComponents_.maxSpeed_)
        velocity.setY(movementComponents_.maxSpeed_);
    else if (y < -movementComponents_.maxSpeed_)
        velocity.setY(-movementComponents_.maxSpeed_);

}

/**
 * @brief Method that applies a deceleration on the velocity given
 * @param velocity  velocity
 */
void MovableEntity::applyDeceleration(Vector& velocity)
{
    if (velocity.getX() > 0)
    {
        velocity += Vector(-movementComponents_.movementDeceleration_, 0.0f);
        if (velocity_.getX() < 0)
            velocity_.setX(0);
    }
    else if (velocity_.getX() < 0)
    {
        velocity += Vector(movementComponents_.movementDeceleration_, 0.0f);
        if (velocity_.getX() > 0)
            velocity_.setX(0);
    }
    
    if (velocity.getY() > 0)
    {
        velocity += Vector(0.0f, -movementComponents_.movementDeceleration_);
        if (velocity_.getY() < 0)
            velocity_.setY(0);
    }
    else if (velocity_.getY() < 0)
    {
        velocity += Vector(0.0f, movementComponents_.movementDeceleration_ );
        if (velocity_.getY() > 0)
            velocity_.setY(0);
    }
}

/**
 * @brief Function that updates the damage value
 */
void MovableEntity::updateDamage() 
{

    if (damaged_ && damageClock_.getElapsedTime().asSeconds() > 2.0f)
    {
        damageClock_.restart();
        damaged_ = false;
    }
}

/**
 * @brief Method that returns the direction of the player according to its acceleration
 * @return      Direction
 */
Direction MovableEntity::getDirection() const
{
    if (velocity_.getX() > 0)
        return RIGHT;

    if (velocity_.getX() < 0)
        return LEFT;

    else if (velocity_.getY() > 0)
        return DOWN;

    else if (velocity_.getY() < 0)
        return UP;

    return NOT_MOVING;
    
}

/**
 * @brief Function that returns whether a direction is available
 * @param direction         Direction
 * @return available or not
 */
bool MovableEntity::isDirectionAvailable(Direction direction) const
{
    return availableDirections[direction];
}

/**
 * @brief Function that updates the direction based on the movement
 * @param movement      Movement
 */
void MovableEntity::updateDirection(const Vector& movement)
{
    setDirectionAvailable(LEFT);
    setDirectionAvailable(RIGHT);
    setDirectionAvailable(UP);
    setDirectionAvailable(DOWN);
}