#include "../headers.h"
#include "DamageRenderer.h"

sf::Font DamageRenderer::font_;
bool DamageRenderer::initialized = false;
std::vector<DamageText> DamageRenderer::damageTexts_;

/**
 * @brief Function that updates the damage handler
 * @param dt        Time since last frame
 */
void DamageRenderer::I_update(const float& dt)
{
    for (auto it = damageTexts_.begin(); it < damageTexts_.end(); it++)
    {
        it->text.setPosition(it->text.getPosition() - sf::Vector2f(0.0f, it->clock.getElapsedTime().asSeconds() * DamageText::MAX_DELTA_HEIGHT / DamageText::MAX_LIFETIME));
        it->text.setFillColor(it->text.getColor() - sf::Color(0, 0, 0, (int) (it->clock.getElapsedTime().asSeconds() * 255)));

        if (it->clock.getElapsedTime().asSeconds() > DamageText::MAX_LIFETIME)
        {
            damageTexts_.erase(it);
        }
    }
}

/**
 * @brief Function that draws every damage number on the window
 * @param window    Window where the numbers will be drawn
 */
void DamageRenderer::I_render(std::shared_ptr<sf::RenderTarget> target)
{
    for (const auto& damageText : damageTexts_)
    {
        target->draw(damageText.text);
    }

}

/**
 * @brief Functoin that adds a text damage to the screen
 * @param value         Damage value
 * @param position      Position of the text
 */
void DamageRenderer::I_addDamage(float value, const Vector& position)
{
    // Only show 1 decimal of number
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << value;

    // Create text
    sf::Text text;
    text.setFont(font_);
    text.setColor(sf::Color::Red);
    text.setString(stream.str());
    text.setPosition(position.getAsVector2f());

    // Add text to array with associeted clock
    damageTexts_.push_back( DamageText { text, sf::Clock() } );
}