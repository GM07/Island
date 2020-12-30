#ifndef EXPERIENCE_BAR_H
#define EXPERIENCE_BAR_H

#include "../Drawable.h"

namespace HUD {
    
    class ExperienceBar 
        :   public Drawable
    {
    public:
        ExperienceBar(sf::Font& font, const Vector& size, const Vector& position);
        virtual ~ExperienceBar() {};


        virtual void update(const float& dt);
        virtual void render(std::shared_ptr<sf::RenderTarget> target);

        // Getters
        virtual float getExperience()
            { return experience_; };

        // Setters
        virtual void setExperience(float value)
            { experience_ = value; };
        
        virtual void addExperience(float value)
            { experience_ += value; };

    private:

        float experience_;

        sf::RectangleShape bar_;
        sf::RectangleShape insideBar_;
        sf::Text experienceNumber_;

    };
}

#endif