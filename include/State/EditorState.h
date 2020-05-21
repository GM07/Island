#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.h"
#include "../GUI/Button.h"

class EditorState
    :   public State 
{
public:

    // Constructor and Destructor
    EditorState(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys);
    virtual ~EditorState();

    // Functions
    virtual void handleKeyboardInputs();
    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);
    virtual void loadTextures();

private:

    // Variables
    sf::Font font_;

    std::map<std::string, std::unique_ptr<gui::Button>> buttons_;

    static constexpr float BUTTON_SIZE_X = 200, BUTTON_SIZE_Y = 50;

    // Functions
    virtual void initKeybinds();
    virtual void initButtons();
    virtual void initFonts();

    void updateButtons(const float& dt);
    void renderButtons(std::shared_ptr<sf::RenderWindow> target = nullptr);
    void handleButtonEvents();

};


#endif