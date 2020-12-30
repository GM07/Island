#ifndef DEMON_SPAWNER_H
#define DEMON_SPAWNER_H

#include "Demon.h"
#include "EntityCollider.h"
#include "Player.h"
#include "../Math/Vector.h"

class DemonSpawner
    :   public Drawable
{
public:
    DemonSpawner(const Vector& position, const float spawningRadius, const Demon& demon, const int maxEntities = -1);
    ~DemonSpawner();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
    virtual void addTexture(std::shared_ptr<sf::Texture>& texture);
    virtual void collide(Player& player);

private:

    virtual void spawn();

    const float spawningRadius_;
    const Vector& position_;
    Demon m_Demon;
    const int maxEntities_;
    
    sf::Clock spawningClock_;

    std::vector<std::unique_ptr<Demon>> entities_;
    std::shared_ptr<sf::Texture> texture_;
};

#endif