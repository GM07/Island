#include "../../include/headers.h"
#include "../../include/Map/CollisionHandler.h"


/**
 * @brief Constructor
 */
CollisionHandler::CollisionHandler()
{

}

/**
 * @brief Function that returns the instance
 */
CollisionHandler& CollisionHandler::getInstance()
{
    static CollisionHandler instance;
    return instance;
}

/**
 * @brief Function that collides to objects
 * @param hitbox        Hitbox component
 * @param collider      Collider
 * @return              Offset to applX to the hitbox
 */
Vector CollisionHandler::I_collide(const HitboxComponent& hitbox, const sf::FloatRect& collider)
{
    Vector dp;
    Vector hitboxPosition = Vector(hitbox.getHitbox().left, hitbox.getHitbox().top);
    Vector colliderPosition = Vector(collider.left, collider.top);
    Vector hitboxSize = Vector(hitbox.getHitbox().width, hitbox.getHitbox().height);
    Vector colliderSize = Vector(collider.width, collider.height);

    if (hitboxPosition.getY() > colliderPosition.getY())
    {
        dp.setY(colliderPosition.getY() + colliderSize.getY() - hitboxPosition.getY());
    } else
    {
        dp.setY(colliderPosition.getY() - hitboxPosition.getY() - hitboxSize.getY());
    }

    if (hitboxPosition.getX() > colliderPosition.getX())
    {
        dp.setX(colliderPosition.getX() + colliderSize.getX() - hitboxPosition.getX());
    } else
    {
        dp.setX(colliderPosition.getX() - hitboxPosition.getX() - hitboxSize.getX());
    }

    if (abs(dp.getX()) < abs(dp.getY()))
        return Vector(dp.getX(), 0.0f);
    return Vector(0.0f, dp.getY());

}
