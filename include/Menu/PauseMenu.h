#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "../Drawable.h"
#include "../GUI/Button.h"

class PauseMenu
    :   public Drawable
{
public:

    PauseMenu(std::shared_ptr<sf::RenderWindow> window);
    virtual ~PauseMenu();

    // Functions
    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderWindow> window);
    virtual void updateMousePosition(Vector mousePosition);

    virtual void addButton(const std::string& key, Vector position, gui::ColorButtonHandler handler, const std::string& title);
    virtual const gui::Button& getButton(const std::string& key) const;
    virtual void addTextureToButton(const std::string& key, std::shared_ptr<sf::Texture> texture);
    virtual bool isButtonPressed(const std::string& key);

private:

    void initFonts();
    void initPausedText();

    // Variables
    std::shared_ptr<sf::RenderWindow> window_;
    sf::RectangleShape background_;
    sf::Font font_;
    sf::Text pausedText_;
    std::unordered_map<std::string, std::unique_ptr<gui::Button>> buttons_;
};

#endif