#include "headers.h"
#include "Game.h"


/// Constructor
Game::Game()
    :   videoModes_(sf::VideoMode::getFullscreenModes())
{
    initWindow();
    initKeyInputs(); 
    initStates();
}

/// Destructor
Game::~Game()
{

}

/**
 * @brief Function called when the application is ending
 *          Used to save files needed by the application
 */
void Game::endApplication()
{
    std::cout << "Ending application" << std::endl;
}

/**
 * @brief Function that handles every sfml events
 */
void Game::handleEvents()
{
    while (window_->pollEvent(event_))
    {
        if (event_.type == sf::Event::Closed)
        {
            window_->close();
        }
    }
}

/**
 * @brief Function that updates the time between each frame
 */
void Game::updateTime()
{
    dt_ = dtClock_.restart().asSeconds();
}

/**
 * @brief Function that updates the application
 */
void Game::update() 
{
    if (fpsClock_.getElapsedTime().asSeconds() > 1.00)
    {
        std::cout << "FPS : " << (1.0f / (dt_)) << std::endl;
        fpsClock_.restart();
    }
    
    handleEvents();
    
    if (!states.empty())
    {
        states.top()->update(dt_);
        if (states.top()->getQuit())
        {
            states.top()->endState();
            states.pop();
        }
    }
    else
    {
        std::cout << "No more states - Application ending...\n";
        endApplication();
        window_->close();
    }

}

/**
 * @brief Function that renders every frame
 */
void Game::render()
{
    window_->clear();

    if (!states.empty())
    {
        states.top()->render(window_);
    }

    window_->display();
}

/**
 * @brief Function that starts the application
 */
void Game::run()
{
    while (window_->isOpen())
    {   
        updateTime();
        update();
        render();
    }
}

/**
 * @brief Function that initializes the window
 */
void Game::initWindow()
{

    std::ifstream config_file("config/window.ini");
    int width = 0, height = 0, frameRateLimit = 0, antialiasing = 0, style = 0;
    std::string title = "";
    bool fullscreen = false, verticalSyncEnabled = false;

    if (config_file 
        >> width >> height >> title
        >> frameRateLimit >> fullscreen
        >> verticalSyncEnabled >> antialiasing)
    {
        if (fullscreen)
            style = sf::Style::Fullscreen;
        else
            style = sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize;
        
        window_ = std::make_shared<Window>(
                width, height, title, style, 
                frameRateLimit, fullscreen, 
                verticalSyncEnabled, antialiasing);
    }
    else {
        throw("Error : Could not read correctly config/window.ini");
    }

    config_file.close();

}

/**
 * @brief Function that initializes the states of the game
 */
void Game::initStates()
{
    states.push(std::make_unique<MainMenuState>(states, window_, &keys_));
}

/**
 * @brief Function that initializes key inputs
 */
void Game::initKeyInputs()
{
    std::ifstream config_file("config/keys.ini");

    std::string key = "";
    int value = 0;

    while (config_file >> key >> value)
    {
        keys_[key] = value;
    }

    config_file.close();

}
