#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "MainMenuState.h"
#include "../GUI/DropDownList.h"

class SettingsState
    :   public State
{
public:
    SettingsState(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys);
    virtual ~SettingsState();

    virtual void handleKeyboardInputs();
    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);
    virtual void loadTextures();

private:

    virtual void initKeybinds();
    virtual void initButtons();
    virtual void initDropDownLists();
    virtual void initFonts();

    void updateButtons(const float& dt);
    void renderButtons(std::shared_ptr<sf::RenderWindow> target = nullptr);
    void handleButtonEvents();

    void updateDropDownLists(const float& dt);
    void renderDropDownLists(std::shared_ptr<sf::RenderWindow> target = nullptr);

    // Variables
    sf::Font font_;
    std::map<std::string, std::unique_ptr<gui::Button>> buttons_;
    std::map<std::string, std::unique_ptr<gui::DropDownList>> dropDownLists_;
};


#endif