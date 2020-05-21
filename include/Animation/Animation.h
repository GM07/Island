#ifndef ANIMATION_H
#define ANIMATION_H

#include "../Drawable.h"

class Animation
{
public:

    Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, sf::Vector2i startFrame, sf::Vector2i numbersOfFrames, sf::Vector2i size);
    
    void play(const float& dt, const float& percentageSpeed = 1.0f);
    void pause();
    void reset();
    bool isDone();

private:
    // Variables
    sf::Sprite& sprite_;
    sf::Texture& textureSheet_;
    sf::IntRect startRect_, endRect_, currentRect_;
    
    Vector size_;
    float animationTimer_;
    float timer_;
    bool done_;
};
#endif