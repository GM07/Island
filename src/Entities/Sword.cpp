#include "../headers.h"
#include "Sword.h"

const float Sword::RADIUS = 32.0f;
const float Sword::HIT_SIZE = 32.0f;

/**
 * @brief Constructor
 * @param position          Position of the sword
 * @param size              Size of the sword
 * @param attackDamage      Attack of the sword
 * @param offset            Where to draw the sword relative to the player's sprite
 * @param playerSprite      Player's sprite
 */
Sword::Sword(const Vector& position, const Vector& size, float attackDamage, std::map<Direction, Vector> offsets, const sf::Sprite& playerSprite)
    :   Entity(position, size)
    ,   attackDamage_(attackDamage)
    ,   offsets_(offsets)
    ,   playerSprite_(playerSprite)
    ,   hitboxActivated_(false)
    ,   currentDirection_(Direction::NOT_MOVING)
{
    sprite_.setOrigin(0.0f, size_.getY());
    sprite_.setPosition((Vector(playerSprite_.getPosition()) + offsets_.at(currentDirection_)).getAsVector2f());

    createHitboxComponent(const_cast<sf::Sprite&>(playerSprite_), offsets_.at(currentDirection_), Vector(size_.getX() * 0.5f, size_.getY()));

    attackHitbox_ = std::make_unique<HitboxComponent>(const_cast<sf::Sprite&>(playerSprite_), (size_ * 0.0f).getAsVector2f(), Vector(HIT_SIZE, HIT_SIZE));

    attackSprite_.setPosition(attackHitbox_->getPosition());
    attackSprite_.setOrigin(attackHitbox_->getSize() * 0.5f);

    hitboxComponent_->setRotation(30.0f);
    hitboxComponent_->setOrigin(0.0f, size_.getY());
    hitboxComponent_->setPosition((Vector(playerSprite_.getPosition()) + offsets_.at(currentDirection_)).getAsVector2f());

}

/**
 * @brief Destructor
 */
Sword::~Sword()
{

}

/**
 * @brief Function that updates the player's position, size, ...
 * @param dt        Time since last frame
 */
void Sword::update(const float& dt)
{
    position_ = ((Vector(playerSprite_.getPosition()) + offsets_.at(currentDirection_)).getAsVector2f());
    center_ = position_ + (size_ * 0.5f);

    sprite_.setPosition(position_.getAsVector2f());
    hitboxComponent_->setPosition(position_.getAsVector2f());

    attackSprite_.setPosition(attackHitbox_->getPosition());

    updateAnimations(dt);
}

/**
 * @brief Function that draws the player on the window
 * @param window    Window where the player will be drawn into
 */
void Sword::render(std::shared_ptr<sf::RenderTarget> target)
{
    target->draw(sprite_);
    target->draw(attackSprite_);
    // hitboxComponent_->render(target);
    
    // if (hitboxActivated_)
       // attackHitbox_->render(target);

}

/**
 * @brief Function that adds a texture to the player (with the animations)
 * @param texture   Texture
 */
void Sword::addTexture(std::shared_ptr<sf::Texture> texture_)
{
    Entity::addTexture(texture_);

    createAnimationComponent(*texture_);

    // Adding swoosh animation
    if (!attackTexture_.loadFromFile("resources/game/player/attack_sprite_sheet.png"))
        throw("Attack texture not loaded");

    attackAnimation_ = std::make_unique<AnimationComponent>(attackSprite_, attackTexture_);

}

/**
 * @brief Function that handles mouse events
 * @param mousePosition     Mouse position
 */
void Sword::handleMouseEvents(const Vector& mousePosition)
{
    mouseDirection_ = (mousePosition - position_).normalize();
    
    float angle = (atan2((mouseDirection_.getY()), mouseDirection_.getX()) + M_PI_2) * 180 / M_PI;
    Vector scale(1.0f, 1.0f);

    if (currentDirection_ == RIGHT) 
    {
        // Player can't hit behind him
        if (angle < 0)
        {
            angle = 0;
        }
        if (angle > 180)
        {
            angle = 180;
        }
        
        scale = Vector(1.0f, 1.0f);
    }

    else if (currentDirection_ == LEFT) 
    {
        // Player can't hit behind him
        if (angle > 0 && angle <= 90)
            angle = 0;
        if (angle < 180 && angle > 90)
            angle = 180;

        scale = Vector(-1.0f, 1.0f);
    }
    else if (currentDirection_ == DOWN || currentDirection_ == NOT_MOVING)
    {
        scale = Vector(1.0f, 1.0f);
    }
    else 
    {
        scale = Vector(-1.0f, 1.0f);
    }

    sprite_.setScale(scale.getAsVector2f());
    hitboxComponent_->setScale(scale.getAsVector2f());

    sprite_.setRotation(angle);
    hitboxComponent_->setRotation(angle);
    
    float angleRad = (angle - 90) * M_PI / 180.0f;
    Vector attackHitboxPosition = position_ + Vector((float) cos(angleRad), (float) sin(angleRad)) * RADIUS;
    attackHitbox_->setPosition((attackHitboxPosition - size_ * 0.5f).getAsVector2f());

    attackSprite_.setPosition(attackHitboxPosition.getAsVector2f());
    //attackSprite_.setScale(scale.getAsVector2f());
    attackSprite_.setRotation(angle);


}

/**
 * @brief Method that generates every animation needed the player
 */
void Sword::initializeAnimations(float attackSpeed)
{
    animationComponent_->addAnimation(
        "ATTACK",                   // Animation name
        10.0f * attackSpeed,                     // Animation speed
        sf::Vector2i(0, 0),         // First of frame's position on texture sheet
        sf::Vector2i(4, 0),         // Number of frames to parcour
        sf::Vector2i(32, 32)        // size
    );

    animationComponent_->addAnimation(
        "IDLE",               // Animation name
        10.0f,                  // Animation speed
        sf::Vector2i(0, 0),     // First of frame's position on texture sheet
        sf::Vector2i(0, 0),     // Number of frames to parcour
        sf::Vector2i(32, 32)    // size
    );

    attackAnimation_->addAnimation(
        "ATTACK",
        10.0f * attackSpeed,
        sf::Vector2i(1, 0),         // First of frame's position on texture sheet
        sf::Vector2i(5, 0),         // Number of frames to parcour
        sf::Vector2i(32, 32) 
    );

    attackAnimation_->addAnimation(
        "IDLE",
        10.0f,
        sf::Vector2i(0, 0),         // First of frame's position on texture sheet
        sf::Vector2i(0, 0),         // Number of frames to parcour
        sf::Vector2i(32, 32) 
    );
}

/**
 * @brief Method that updates the animation according to the velocity
 * @param dt    Time since last frame
 */
void Sword::updateAnimations(const float& dt)
{
    if (hitboxActivated_)
    {
        animationComponent_->playAnimation("ATTACK", dt);
        attackAnimation_->playAnimation("ATTACK", dt);
    }
    else
    {
        animationComponent_->playAnimation("IDLE", dt);
        attackAnimation_->playAnimation("IDLE", dt);
    }
    

}