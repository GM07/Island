#ifndef WINDOW_CLASS
#define WINDOW_CLASS

#include "SFML/Graphics.hpp"

class Window : public sf::RenderWindow
{
public:

    Window(uint width, uint height, 
        const std::string& title = "",
        unsigned int style = sf::Style::Default,
        uint frameRateLimit = 120,
        bool fullScreen = false,
        bool verticalSyncEnabled = false,
        unsigned int antialiasing = 0);
    virtual ~Window();

private:
    uint width_;
    uint height_;
    std::string title_;
    uint frameRateLimit_;
    bool fullScreen_;
    bool verticalSyncEnabled_;
    unsigned int antialiasing_;

    sf::ContextSettings contextSettings;

};

#endif