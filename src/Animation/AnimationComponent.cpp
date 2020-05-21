#include "../../include/headers.h"
#include "../../include/Animation/AnimationComponent.h"

/**
 * @brief Constructor
 * @param textureSheet  Texture sheet of the animation  
 */
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
    :   sprite_(sprite),
        textureSheet_(textureSheet)
{}

/**
 * @brief Method that plays the animation component
 * The current speed and the max speed are used to slow 
 * down the animation depending on the entity's speed
 * @param animationName Name of the animation to play
 * @param dt            Time since last frame
 * @param currentSpeed  Current speed of the entity
 * @param maxSpeed      Maximum speed of the entity
 */
void AnimationComponent::playAnimation(std::string animationName, const float& dt, const float& currentSpeed, const float& maxSpeed)
{
    if (lastAnimation_ != animations_[animationName])
    {
        if (lastAnimation_ != nullptr)
            lastAnimation_->reset();
        lastAnimation_ = std::make_unique<Animation>(*animations_[animationName]);
    }

    animations_[animationName]->play(dt, static_cast<float>(abs(static_cast<int>(currentSpeed))) / maxSpeed);
}

void AnimationComponent::addAnimation(const std::string& animationName, float animationTimer, sf::Vector2i startFrame, sf::Vector2i numbersOfFrames, sf::Vector2i size)
{
    animations_[animationName] = std::make_unique<Animation>(sprite_, textureSheet_, animationTimer, startFrame, numbersOfFrames, size);
}

/**
 * @brief Method that resets a certain animation
 * @param animationName Name of the animation to reset
 */
void AnimationComponent::resetAnimation(const std::string& animationName)
{
    animations_[animationName]->reset();
}

