#ifndef MOVABLE_ENTITY_H
#define MOVABLE_ENTITY_H

#include "Entity.h"

struct MovementComponents
{
    MovementComponents(float speed, float acceleration, float deceleration)
        :   maxSpeed_(speed)
        ,   movementAcceleration_(acceleration)
        ,   movementDeceleration_(deceleration)
    {};

    float maxSpeed_;
    float movementAcceleration_;
    float movementDeceleration_;   
};

enum Direction
{
    LEFT, RIGHT, UP, DOWN, NOT_MOVING
};

class MovableEntity
    :   public Entity
{
public:

    // Constructor / Destructor
    MovableEntity(Vector position, Vector size, MovementComponents movementComponents, float life = 100.0f);
    virtual ~MovableEntity();

    // Functions
    virtual void updateMovement(const float& dt);
    virtual void move(const float& dx, const float& dy);
    
    virtual void validateMaxSpeed(Vector& velocity);
    virtual void applyDeceleration(Vector& velocity);
    virtual void updateDamage();

    // Getters
    virtual float getMaxSpeed() const 
        { return movementComponents_.maxSpeed_; };

    virtual float getMovementAcceleration() const 
        { return movementComponents_.movementAcceleration_; };

    virtual float getMovementDeceleration() const 
        { return movementComponents_.movementDeceleration_; };  

    virtual Vector& getVelocity() 
        { return velocity_; };        

    virtual Vector& getAcceleration() 
        { return acceleration_; };

    virtual bool isDamaged() 
        { return damaged_; };

    virtual float getLife() const 
        { return life_; }

    virtual float getExperience()
        { return 0.5f; };

    virtual Direction getDirection() const;
    virtual bool isDirectionAvailable(Direction direction) const;

    // Setters
    virtual void setMaxSpeed(const float& maxSpeed) 
        { movementComponents_.maxSpeed_ = maxSpeed; };

    virtual void setMovementAcceleration(const float& movementAcceleration) 
        { movementComponents_.movementAcceleration_ = movementAcceleration; };

    virtual void setMovementDeceleration(const float& movementDeceleration) 
        { movementComponents_.movementDeceleration_ = movementDeceleration; };

    virtual void setVelocity(const Vector& velocity) 
        { velocity_ = velocity; };

    virtual void setAcceleration(const Vector& acceleration) 
        { acceleration_ = acceleration; };

    virtual void setDirectionAvailable(Direction direction) 
        { availableDirections[direction] = true; };

    virtual void damage(float value) 
        { damaged_ = true; life_ -= value; };

protected:

    virtual void updateDirection(const Vector& movement);

    // Variables
    MovementComponents movementComponents_;

    Vector velocity_;
    Vector acceleration_;
    Vector forceApplied_;

    bool availableDirections[4];
    bool damaged_;
    float life_;

    sf::Clock damageClock_;
};

#endif