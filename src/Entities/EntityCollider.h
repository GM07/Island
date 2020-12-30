#ifndef ENTITY_COLLIDER_H
#define ENTITY_COLLIDER_H

#include "Player.h"
#include "DamageRenderer.h"
#include "../HUD/ExperienceBar.h"

class EntityCollider
{
public:
    static void handleCollisionPE(Player* player, MovableEntity* collider);

private:
    static bool detectCollision();

    static float knockbackCoefficientPE_;
    static HUD::ExperienceBar* experienceBar_;

};


#endif