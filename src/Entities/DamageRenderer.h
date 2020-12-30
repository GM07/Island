#ifndef DAMAGE_HANDLER_H
#define DAMAGE_HANDLER_H

#include "../Drawable.h"
#include "../Exception/SingletonNotInitialized.h"

struct DamageText
{
    sf::Text text;
    sf::Clock clock;

    static constexpr float MAX_LIFETIME = 1.0f; 

    /**
    * Maximum delta height of the damage text 
    * (after {LIFETIME} seconds, the text will be {MAX_DELTA_HEIGHT} 
    * pixels higher than its original position)
    **/
    static constexpr float MAX_DELTA_HEIGHT = 8.0f;
};

class DamageRenderer
{
public:

    static DamageRenderer& getInstance()
    {
        static DamageRenderer instance;
        return instance;
    }

    static void update(const float& dt)
        { getInstance().I_update(dt); };

    static void render(std::shared_ptr<sf::RenderTarget> target)
        { getInstance().I_render(target); };

    static void addDamage(float value, const Vector& position)
        { getInstance().I_addDamage(value, position); };

private:
    DamageRenderer() 
    {
        if (!font_.loadFromFile("fonts/basic_font.ttf"))
            throw SingletonNotInitialized("Damaged Renderer couln't not find file : fonts/basic_font.ttf");
    };

    virtual ~DamageRenderer() {};

    static void I_update(const float& dt);
    static void I_render(std::shared_ptr<sf::RenderTarget> target);
    static void I_addDamage(float value, const Vector& position);

    static sf::Font font_;
    static bool initialized;

    static std::vector<DamageText> damageTexts_;
};

#endif