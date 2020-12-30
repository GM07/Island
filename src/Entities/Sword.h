#ifndef SWORD_H
#define SWORD_H

#include "Entity.h"
#include "MovableEntity.h"

class Sword
    :   public Entity
{
public:

    static const float RADIUS;
    static const float HIT_SIZE;

    Sword(const Vector& position, const Vector& size, float attackDamage, std::map<Direction, Vector> offsets, const sf::Sprite& playerSprite);
    virtual ~Sword();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target);
    virtual void addTexture(std::shared_ptr<sf::Texture> texture_);
    virtual void handleMouseEvents(const Vector& mousePosition);
    virtual void initializeAnimations(float attackSpeed);
    virtual void updateAnimations(const float& dt);

    virtual bool isIntersecting(const HitboxComponent&& rect) const
        { return attackHitbox_->isIntersecting(rect.getHitbox()); };

    virtual bool isIntersecting(const HitboxComponent& rect) const
        { return attackHitbox_->isIntersecting(rect.getHitbox()); };

    virtual const HitboxComponent& getHitbox() const
        { return *attackHitbox_; }; 

    virtual void setDirection(Direction direction) 
        { currentDirection_ = direction; };

    virtual float getAttackDamage() const
        { return attackDamage_; };

    virtual bool& isActivated()
        { return hitboxActivated_; };

    virtual const Vector& getMouseDirection() const
        { return mouseDirection_; };

private:

    bool hitboxActivated_;
    float attackDamage_;

    sf::Texture attackTexture_;
    sf::Sprite attackSprite_;
    std::unique_ptr<AnimationComponent> attackAnimation_;

    const sf::Sprite& playerSprite_;
    const std::map<Direction, Vector> offsets_;
    std::unique_ptr<HitboxComponent> attackHitbox_;

    Vector mouseDirection_;
    Direction currentDirection_;

};

#endif