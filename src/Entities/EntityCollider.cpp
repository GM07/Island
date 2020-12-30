#include "../headers.h"
#include "EntityCollider.h"

// Knockback applied to entity when hit by player
float EntityCollider::knockbackCoefficientPE_ = 256.0f;

/**
 * @brief Function that handles the collision between 
 * @param   player      player
 * @param   collider    Entity colliding with player
 */
void EntityCollider::handleCollisionPE(Player* player, MovableEntity* collider)
{
    if (player->isAttacking() && player->getSword().isIntersecting(collider->getHitbox()) && !collider->isDamaged())
    {
        // Entities colliding
        collider->damage(player->getSword().getAttackDamage());

        Vector dp = (player->getSword().getMouseDirection() * knockbackCoefficientPE_);

        collider->setVelocity(dp);

        DamageRenderer::addDamage(player->getSword().getAttackDamage(), collider->getPosition());
        
        player->addExperience(collider->getExperience());
    }

}
