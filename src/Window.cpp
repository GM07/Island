#include "headers.h"
#include "Window.h"

/**
 * @brief Constructor with parameters
 * @param width                 Width of the window
 * @param height                Height of the window
 * @param title                 Title on top of the window
 * @param frameRateLimit        Frame Rate limit
 * @param fullScreen            FullScreen mode or not
 * @param verticalSyncEnabled   Vertical Sync Enabled or not
 * @param antialiasing          Antialiasing level
 */
Window::Window(
    uint width, 
    uint height, 
    const std::string& title,
    unsigned int style,
    uint frameRateLimit,
    bool fullScreen,
    bool verticalSyncEnabled,
    unsigned int antialiasing
)
    :   RenderWindow(sf::VideoMode(width, height), title, style)
    ,   width_(width)
    ,   height_(height)
    ,   title_(title)
    ,   frameRateLimit_(frameRateLimit)
    ,   fullScreen_(fullScreen)
    ,   verticalSyncEnabled_(verticalSyncEnabled)
    ,   antialiasing_(antialiasing)

{
    contextSettings.antialiasingLevel = antialiasing;

    setFramerateLimit(frameRateLimit_);
    setVerticalSyncEnabled(verticalSyncEnabled_);
    setKeyRepeatEnabled(false);
}

/**
 * @brief Destructor
 */
Window::~Window()
{
    
}