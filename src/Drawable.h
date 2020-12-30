#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Math/Vector.h"

class Drawable
{
public:
    virtual void update(const float& dt) = 0;
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr) = 0;
};

#endif