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
    MovableEntity(Vector position, Vector size, MovementComponents movementComponents);
    virtual ~MovableEntity();

    // Functions
    virtual void updateMovement(const float& dt);
    virtual void move(const float& dx, const float& dy);
    
    virtual void validateMaxSpeed(Vector& velocity);
    virtual void applyDeceleration(Vector& velocity);
    virtual void applyForce(const Vector& force);

    // Getters
    virtual float getMaxSpeed() const;
    virtual float getMovementAcceleration() const;
    virtual float getMovementDeceleration() const;    
    virtual Vector& getVelocity();        
    virtual Vector& getAcceleration();
    virtual Direction getDirection() const;
    virtual bool isDirectionAvailable(Direction direction) const;

    // Setters
    virtual void setMaxSpeed(const float& maxSpeed);
    virtual void setMovementAcceleration(const float& movementAcceleration);
    virtual void setMovementDeceleration(const float& movementDeceleration);
    virtual void setVelocity(const Vector& velocity);
    virtual void setAcceleration(const Vector& acceleration);
    virtual void setDirectionAvailable(Direction direction);

protected:

    virtual void updateDirection(const Vector& movement);

    // Variables
    MovementComponents movementComponents_;

    Vector velocity_;
    Vector acceleration_;
    Vector forceApplied_;

    bool availableDirections[4];
};

#endif