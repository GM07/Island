#include "../../include/headers.h"
#include "../../include/Animation/Animation.h"

/**
 * @brief Constructor with parameters
 * @param sprite            Sprite where the animation will be applied
 * @param textureSheet      Texture sheet of the animation
 * @param animationTimer    Animation timer (speed of the animation)
 * @param startFrame        Start position in the texture sheet (in frameSize -> first frame = 0, 0)
 * @param size              Size of a rectangle 
 */
Animation::Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, sf::Vector2i startFrame, sf::Vector2i numbersOfFrames, sf::Vector2i size)
    :   sprite_(sprite),
        textureSheet_(textureSheet),
        startRect_(startFrame.x * size.x, startFrame.y * size.y, size.x, size.y),
        endRect_((startFrame.x + numbersOfFrames.x) * size.x, (startFrame.y + numbersOfFrames.y) * size.y, size.x, size.y),
        currentRect_(startRect_),
        size_(static_cast<float>(size.x), static_cast<float>(size.y)),
        animationTimer_(animationTimer),
        timer_(0.0f),
        done_(false)
{
    sprite.setTexture(textureSheet, true);
    sprite.setTextureRect(startRect_);
}

/**
 * @brief Method that plays the animation according
 * to the entity's speed
 * @param dt                Time since last frame
 * @param percentageSpeed   Percentage of the max speed
 */
void Animation::play(const float& dt, const float& percentageSpeed)
{
    done_ = false;
    timer_ += percentageSpeed * 100.0f * dt;
    if (timer_ >= animationTimer_)
    {   
        // Resetting timer
        timer_ = 0;
        if (currentRect_ != endRect_)
        {
            // Animation has not ended
            currentRect_.left += currentRect_.width;
        }
        else
        {
            // Animation has ended
            currentRect_.left = startRect_.left;
            done_ = true;
        }

        sprite_.setTextureRect(currentRect_);
    }

}

/**
 * @brief Method that resets the animation
 */
void Animation::reset()
{
    currentRect_ = startRect_;
    timer_ = animationTimer_;

}

/**
 * @brief Method that returns whether the animation is done or not
 * @return      Done or not
 */
bool Animation::isDone()
{
    return done_;
}