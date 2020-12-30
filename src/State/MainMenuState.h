#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.h"
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "../GUI/Button.h"

class MainMenuState
    :   public State
{

public:

    // Constructor and Destructor
    MainMenuState(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys);
    virtual ~MainMenuState();

    // Functions
    virtual void handleKeyboardInputs();
    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
    virtual void loadTextures();

private:

    // Variables
    sf::Font font_;

    std::map<std::string, std::unique_ptr<gui::Button>> buttons_;

    // Functions
    virtual void initKeybinds();
    virtual void initButtons();
    virtual void initFonts();

    void updateButtons(const float& dt);
    void renderButtons(std::shared_ptr<sf::RenderTarget> target = nullptr);
    void handleButtonEvents();

};


#endif