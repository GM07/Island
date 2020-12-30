#ifndef HITBOX_COMPONENT_H
#define HITBOX_COMPONENT_H

#include "../Drawable.h"

class HitboxComponent
    :   public Drawable,
        public virtual sf::RectangleShape
{
public:
    HitboxComponent(sf::Sprite& sprite, Vector offset, Vector size);
    virtual ~HitboxComponent();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target);
    bool isIntersecting(const sf::FloatRect& rect) const;

    sf::FloatRect getHitbox() const; 

private:

    // Variables
    Vector offset_;
    sf::Sprite& sprite_;

};

#endif