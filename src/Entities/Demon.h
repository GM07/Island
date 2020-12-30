#ifndef DEMON_H
#define DEMON_H

#include "MovableEntity.h"

class Demon
    :   public MovableEntity
{

public:
    Demon(const Vector& position, const Vector& size, const Vector& attractor, MovementComponents movementComponents, std::shared_ptr<sf::Texture> texture = nullptr);
    Demon(const Demon& demon);
    virtual ~Demon();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target);
    virtual void addTexture(std::shared_ptr<sf::Texture> texture_);

    virtual float getExperience()
        { return 0.2f; };

private:

    virtual void attract();
    virtual void initializeAnimations();
    virtual void updateAnimations(const float& dt);

    const Vector& attractor_;
};

#endif