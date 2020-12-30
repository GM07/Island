#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include "../Drawable.h"
#include "Animation.h"


class AnimationComponent
{

public:
    AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);

    void addAnimation(const std::string& animationName, float animationTimer, sf::Vector2i startFrame, sf::Vector2i numbersOfFrames, sf::Vector2i size);
    void playAnimation(std::string animationName, const float& dt, const float& currentSpeed = 1.0f, const float& maxSpeed = 1.0f);
    void resetAnimation(const std::string& animationName);

private:

    std::map<std::string, std::unique_ptr<Animation>> animations_;
    std::unique_ptr<Animation> lastAnimation_;
    sf::Sprite& sprite_;
    sf::Texture& textureSheet_;

};

#endif