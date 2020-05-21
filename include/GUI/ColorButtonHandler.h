#ifndef COLOR_BUTTON_HANDLER_H
#define COLOR_BUTTON_HANDLER_H

#include "SFML/Graphics.hpp"

namespace gui
{
    class ColorButtonHandler
    {

    public:
        ColorButtonHandler(
            sf::Color color = sf::Color::Green,
            sf::Color hoverColor = sf::Color::Red,
            sf::Color clickedColor = sf::Color::Blue,
            sf::Color offColor = sf::Color::White,
            sf::Color textColor = sf::Color(51, 51, 51),
            sf::Color shadowTextColor = sf::Color(200, 200, 200),
            sf::Color outlineColor = sf::Color::Transparent,
            sf::Color outlineHoverColor = sf::Color::Transparent,
            sf::Color outlineClickedColor = sf::Color::Transparent,
            sf::Color outlineOffColor = sf::Color::Transparent
        );
        ~ColorButtonHandler();

        sf::Color getColor() const;
        sf::Color getHoverColor() const;
        sf::Color getClickedColor() const;
        sf::Color getOffColor() const;
        sf::Color getTextColor() const;
        sf::Color getShadowTextColor() const;
        sf::Color getOutlineColor() const;
        sf::Color getOutlineHoverColor() const;
        sf::Color getOutlineClickedColor() const;
        sf::Color getOutlineOffColor() const;
        ColorButtonHandler getWithoutOutline() const;

        void setColor(sf::Color color);
        void setHoverColor(sf::Color color);
        void setClickedColor(sf::Color color);
        void setOffColor(sf::Color color);
        void setTextColor(sf::Color color);
        void setShadowTextColor(sf::Color color);
        void setOutlineColor(sf::Color color);
        void setOutlineHoverColor(sf::Color color);
        void setOutlineClickedColor(sf::Color color);
        void setOutlineOffColor(sf::Color color);

    private:
        sf::Color color_;
        sf::Color hoverColor_;
        sf::Color clickedColor_;
        sf::Color offColor_;
        sf::Color textColor_;
        sf::Color shadowTextColor_;
        sf::Color outlineColor_;
        sf::Color outlineHoverColor_;
        sf::Color outlineClickedColor_;
        sf::Color outlineOffColor_;
    };
}
#endif