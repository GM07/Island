#ifndef PLAYER_H
#define PLAYER_H

#include "MovableEntity.h"
#include "Sword.h"
#include "../HUD/ExperienceBar.h"

class Player
    : public MovableEntity
{

public:

    Player(const Vector& position, const Vector& size, MovementComponents movementComponents);
    virtual ~Player();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target);
    virtual void addTexture(std::shared_ptr<sf::Texture> texture_);
    virtual void addSwordTexture(std::shared_ptr<sf::Texture> texture_);
    virtual void handleMouseEvents(const Vector& mousPosition);
    virtual void applyForce(const Vector& force);
    virtual void addExperienceBar(HUD::ExperienceBar* experienceBar);

    // Getters
    virtual const Sword& getSword() 
        { return sword_; };

    virtual float getAttackSpeed() 
        { return attackSpeed_; };

    virtual bool isAttacking()
        { return attacking_; };

    // Setters
    virtual void addExperience(float value)
        { experienceBar_->addExperience(value); };

private:

    virtual bool attack() 
        { return attacking_ = true; }

    virtual void initializeAnimations();
    virtual void updateAnimations(const float& dt);

    bool attacking_ = false;
    Sword sword_;
    sf::Clock damageClock_;
    float attackSpeed_ = 0.5f;

    HUD::ExperienceBar* experienceBar_;
};

#endif