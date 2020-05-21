#include "../../include/headers.h"
#include "../../include/State/EditorState.h"


/**
 * @brief Constructor with parameters
 * @param states    Stack of the states in the game
 * @param window    Window where the state will be drawn into
 * @param keys      Keys supported by the game
 */
EditorState::EditorState(
    std::stack<std::unique_ptr<State>>& states, 
    std::shared_ptr<sf::RenderWindow> window, 
    std::map<std::string, int>* keys
)
    :   State(states, window, keys)
{
    std::cout << "Editor State created" << std::endl;

    loadTextures();
    initButtons();
    initKeybinds();
    initFonts();

}

/**
 * @brief Destructor
 */
EditorState::~EditorState()
{
    std::cout << "Editor State deleted" << std::endl;
}

/**
 * @brief Method that handles keyboard inputs for that specific state
 */
void EditorState::handleKeyboardInputs()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("CLOSE"))))
    {
        endState();
    }
}

/**
 * @brief Function that updates the game state
 * @param dt    time since last frame
 */
void EditorState::update(const float& dt)
{
    updateMousePosition();
    updateButtons(dt);
    handleKeyboardInputs();
    handleButtonEvents();
}

/**
 *  @brief Function that renders the game state
 *  @param target   RenderWindow where the state will be drawn
 */
void EditorState::render(std::shared_ptr<sf::RenderWindow> target)
{
    if (!target)
        target = window_;

    renderButtons(target);
}

/**
 * @brief Function that loads the textures needed for the state
 */
void EditorState::loadTextures()
{
    sf::Texture texture;

}

/**
 * @brief Function that initializes the keybinds of the state
 */
void EditorState::initKeybinds()
{
    if (keys_)
    {
        std::ifstream config_file("config/editor_state.ini");
        
        if (!config_file)
            throw("Config file not found : editor_state.ini");

        std::string keybind = "", key = "";

        while (config_file >> keybind >> key)
        {
            keybinds_[keybind] = keys_->at(key);
        }

        config_file.close();

    }
    else 
    {
        throw("Key map was not initialized");
    }

}

/**
 * @brief Function that initializes the state's fonts
 */
void EditorState::initFonts()
{
    if (!font_.loadFromFile("fonts/basic_font.ttf"))
    {
        throw("Error : Could not load font : basic_font.ttf");
    }
    
}

/**
 * @brief Function that initializes the buttons
 */
void EditorState::initButtons()
{

    gui::ColorButtonHandler handler(
        sf::Color(255, 255, 255), // Normal
        sf::Color(200, 200, 200), // Hover
        sf::Color(51, 51, 51), // Clicked
        sf::Color(100, 100, 100) // Off
    );

}

/**
 * @brief Function that updates the buttons of the state
 * @param dt    Time since last frame
 */
void EditorState::updateButtons(const float& dt)
{
    for (auto& button : buttons_)
    {
        button.second->update(dt);
        button.second->updateMousePosition(mousePositionView);
    }   
}

/**
 * @brief Function that renders the buttons of the state
 */
void EditorState::renderButtons(std::shared_ptr<sf::RenderWindow> target)
{

    for (auto& button : buttons_)
    {
        button.second->render(target);
    }
}

/**
 * @brief Function that handles when a button is clicked and changes states
 */
void EditorState::handleButtonEvents()
{
    //
}

