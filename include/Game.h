#ifndef GAME_CLASS
#define GAME_CLASS

#include "State/State.h"
#include "State/GameState.h"
#include "State/MainMenuState.h"
#include "Window.h"

class Game
{
public:

    // Constructor/Destructor
    Game();
    ~Game();
    
    // Functions
    void endApplication();
    void handleEvents();
    void updateTime();
    void update();
    void render();
    void run();

private:

    // Init functions
    void initWindow();
    void initStates();
    void initKeyInputs();

    // Variables
    std::shared_ptr<Window> window_;
    sf::Event event_;
    std::vector<sf::VideoMode> videoModes_;

    float dt_;
    sf::Clock dtClock_;

    // States of the game
    std::stack<std::unique_ptr<State>> states;

    // Handle key inputs
    std::map<std::string, int> keys_;

};

#endif