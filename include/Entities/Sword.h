#ifndef SWORD_H
#define SWORD_H

#include "Entity.h"
#include "MovableEntity.h"

class Sword
    :   public Entity
{
public:
    Sword(const Vector& position, const Vector& size, float attackDamage, const Vector& offset, const sf::Sprite& playerSprite);
    virtual ~Sword();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderWindow> target);
    virtual void addTexture(std::shared_ptr<sf::Texture> texture_);
    
    virtual void setDirection(Direction direction);
    virtual float getAttackDamage() const;

private:

    float attackDamage_;
    const Vector offset_;
    const sf::Sprite& playerSprite_;
};

#endif