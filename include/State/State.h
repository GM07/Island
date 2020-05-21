#ifndef STATE_H
#define STATE_H

#include "../Entities/Entity.h"
#include "../Window.h"
#include "../Math/Vector.h"
#include "../Drawable.h"

class State
    : public Drawable
{
public:

    // Constructor and Destructor
    State(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys);
    virtual ~State();

    // Functions
    void endState();
    virtual void updateMousePosition();
    virtual void updateKeyTime(const float& dt);
    virtual void handleKeyboardInputs() = 0;
    virtual void loadTextures() = 0;
    
    virtual void pause();
    virtual void unpause();

    // Getters
    const bool& getQuit() const;
    bool getKeyTime();  

protected:

    // Variables
    std::shared_ptr<sf::RenderWindow> window_;
    std::stack<std::unique_ptr<State>>& states_;

    std::map<std::string, int>* keys_;
    std::map<std::string, int> keybinds_;
    float keyTime_;
    float keyTimeMax_;

    Vector mousePositionScreen;
    Vector mousePositionWindow;
    Vector mousePositionView;

    std::map<std::string, std::shared_ptr<sf::Texture>> textures_;

    bool paused_;

    // Functions
    virtual void initKeybinds() = 0;

private:

    // Variables
    bool quit_;
};

#endif