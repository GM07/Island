#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "../Math/Vector.h"
#include "../Entities/HitboxComponent.h"

// Singleton class
class CollisionHandler
{

public:

    CollisionHandler(const CollisionHandler&) = delete;
    void operator=(const CollisionHandler&) = delete;

    static CollisionHandler& getInstance();

    static Vector collide(const HitboxComponent& hitbox, const sf::FloatRect& collider)
    {
        return getInstance().I_collide(hitbox, collider);
    }

private:

    Vector I_collide(const HitboxComponent& hitbox, const sf::FloatRect& collider);
    CollisionHandler();

};

#endif