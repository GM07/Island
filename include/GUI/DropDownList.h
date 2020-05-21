#ifndef DROP_DOWN_LIST_H
#define DROP_DOWN_LIST_H

#include "../Drawable.h"
#include "Button.h"

namespace gui
{
    class DropDownList
        :   public Drawable
    {
        public:
            DropDownList(
                sf::Font& font, 
                Vector position, Vector elementSize, 
                ColorButtonHandler colorButtonHandler, unsigned int characterSize, 
                const std::string& mainElement, const std::vector<std::string>& elements = std::vector<std::string>(0)
            );
            virtual ~DropDownList();

            virtual void update(const float& dt);
            virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);     
            virtual void updateMousePosition(Vector mousePosition);

            virtual void addElement(const std::string& name);
            virtual void addTexture(std::shared_ptr<sf::Texture> texture);

            virtual void handleClick();

        private:

            virtual bool getClickTime();
            virtual void updateClickTime(const float& dt);

            gui::Button* activeElement_;
            std::unordered_map<std::string, std::unique_ptr<gui::Button>> elements_;

            sf::Font& font_;
            Vector position_;
            Vector elementSize_;
            ColorButtonHandler colorButtonHandler_;
            unsigned int characterSize_;
            bool dropDown_;

            float clickTime_;
            const float maxClickTime_ = 1.0f;
    };

}


#endif