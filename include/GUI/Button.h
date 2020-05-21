#ifndef BUTTON_H
#define BUTTON_H

#include "../State/State.h"
#include "../Drawable.h"
#include "ColorButtonHandler.h"

namespace gui 
{
    enum Button_State
    {
        NORMAL,
        HOVER,
        CLICKED,
        OFF
    };

    class Button
        : public Drawable
    {
    public:
        static const float BUTTON_SIZE_X, BUTTON_SIZE_Y;

        // Constructor and Destructor
        Button(Vector position, Vector size, 
                sf::Font* font, 
                ColorButtonHandler colorButtonHandler,
                std::string title = "Button", 
                unsigned int characterSize = 30
                );
        Button(const Button& button);
        virtual ~Button();

        // Functions
        virtual void updateMousePosition(const Vector& mousePosition);
        virtual void update(const float& dt);
        virtual void render(std::shared_ptr<sf::RenderWindow> target);
        virtual void addTexture(std::shared_ptr<sf::Texture> texture);

        // Getters
        Button_State getButtonState() const;
        Vector getPosition() const;
        Vector getSize() const;
        const std::string& getTitle() const;

        // Setters
        void setButtonState(const Button_State& state);
        void setPosition(const Vector& position);
        void setSize(const Vector& size);
        void setTitle(const std::string& title);

    private:
    
        virtual void updateText();

        // Variables
        Button_State buttonState_;

        Vector position_;
        Vector size_;
        ColorButtonHandler colorButtonHandler_;

        std::string title_;
        unsigned int characterSize_;

        sf::RectangleShape rect_;
        sf::Font* font_;
        sf::Text text_;
        sf::Text shadowText_;
        sf::Sprite sprite_;
        std::shared_ptr<sf::Texture> texture_;

    };
}

#endif