#include "../../include/headers.h"
#include "../../include/Entities/MovableEntity.h"


/**
 * @brief Constructor with parameters
 * @param position              Position
 * @param size                  Size
 * @param movementComponents    Movememnt component of the entity containing all its movement information
 */
MovableEntity::MovableEntity(Vector position, Vector size, MovementComponents movementComponents)
    :   Entity(position, size)
    ,   movementComponents_(movementComponents)
    ,   velocity_(0, 0)
    ,   acceleration_(0, 0)
    ,   availableDirections({true, true, true, true})
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

    // Updating things on screen
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
 * @brief Function that applies a force on the entity
 * @param force         Force (only the direction is taken into account)
 */
void MovableEntity::applyForce(const Vector& force)
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
 * @brief Method that returns the movement speed
 * @return movement speed
 */
float MovableEntity::getMaxSpeed() const
{
    return movementComponents_.maxSpeed_;
}

/**
 * @brief Method that returns the movement acceleration
 * @return movement acceleration
 */
float MovableEntity::getMovementAcceleration() const
{
    return movementComponents_.movementAcceleration_;
}

/**
 * @brief Method that returns the movement decceleration
 * @return movement decceleration
 */
float MovableEntity::getMovementDeceleration() const
{
    return movementComponents_.movementDeceleration_;
}

/**
 * @brief Method that returns the velocity
 * @return velocity
 */
Vector& MovableEntity::getVelocity() 
{
    return velocity_;
}

/**
 * @brief Method that returns the acceleration
 * @return acceleration
 */
Vector& MovableEntity::getAcceleration() 
{
    return acceleration_;
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
 * @brief Function that returns the center of the entity
 */

/**
 * @brief Method that changes the movement speed
 * @param maxSpeed New movement speed
 */
void MovableEntity::setMaxSpeed(const float& maxSpeed)
{
    movementComponents_.maxSpeed_ = maxSpeed;
}

/**
 * @brief Method that changes the movement acceleration
 * @param movementAcceleration New movement acceleration
 */
void MovableEntity::setMovementAcceleration(const float& movementAcceleration)
{
    movementComponents_.movementAcceleration_ = movementAcceleration;
}

/**
 * @brief Method that changes the movement decceleration
 * @param movementDeceleration New movement decceleration
 */
void MovableEntity::setMovementDeceleration(const float& movementDeceleration)
{
    movementComponents_.movementDeceleration_ = movementDeceleration;
}

/**
 * @brief Method that changes the velocity
 * @param velocity  New velocity
 */
void MovableEntity::setVelocity(const Vector& velocity)
{
    velocity_ = velocity;
}

/**
 * @brief Method that changes the velocity
 * @param velocity  New velocity
 */
void MovableEntity::setAcceleration(const Vector& acceleration)
{
    acceleration_ = acceleration;
}

void MovableEntity::setDirectionAvailable(Direction direction)
{
    availableDirections[direction] = true;
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