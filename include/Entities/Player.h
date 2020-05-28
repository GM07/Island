#ifndef PLAYER_H
#define PLAYER_H

#include "MovableEntity.h"

class Player
    : public MovableEntity
{

public:

    Player(const Vector& position, const Vector& size, MovementComponents movementComponents);
    virtual ~Player();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderWindow> target);
    virtual void addTexture(std::shared_ptr<sf::Texture> texture_);
    
private:

    virtual void initComponents();
    virtual void initializeAnimations();
    virtual void updateAnimations(const float& dt);

    bool attacking_;
};

#endif