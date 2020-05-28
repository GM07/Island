#ifndef ENTITY_H
#define ENTITY_H

#include "../Drawable.h"
#include "HitboxComponent.h"
#include "../Animation/AnimationComponent.h"

class Entity
    : public Drawable
{
public:

    static constexpr float DEFAULT_SIZE = 32.0f;

    Entity(Vector position, Vector size);
    virtual ~Entity();

    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderWindow> window) = 0;
    virtual void addTexture(std::shared_ptr<sf::Texture> texture_);
    virtual void createAnimationComponent(sf::Texture& textureSheet);
    virtual void createHitboxComponent(sf::Sprite& sprite, const Vector& offset, const Vector& size);

    // Getters
    const Vector& getPosition() const;
    const Vector& getSize() const;
    const HitboxComponent& getHitbox() const;
    const Vector& getCenter() const;

    // Setters
    void setPosition(const Vector& position);
    void setSize(const Vector& size);

protected:

    Vector position_;
    Vector size_;
    Vector center_;

    // Components
    std::unique_ptr<AnimationComponent> animationComponent_;
    std::unique_ptr<HitboxComponent> hitboxComponent_;

    // Drawable
    sf::RectangleShape rect_;
    sf::Sprite sprite_;

private:
    
    void initShape();

};

#endif