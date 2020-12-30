#include "../headers.h"
#include "MainMenuState.h"

/**
 * @brief Constructor with parameters
 * @param states    Stack of the states in the game
 * @param window    Window where the state will be drawn into
 * @param keys      Keys supported by the game
 */
MainMenuState::MainMenuState(std::stack<std::unique_ptr<State>>& states,  std::shared_ptr<sf::RenderWindow> window,  std::map<std::string, int>* keys
)
    :   State(states, window, keys)
{
    std::cout << "Main Menu State created" << std::endl;
    loadTextures();
    initButtons();
    initKeybinds();
    initFonts();
}

/**
 * @brief Destructor
 */
MainMenuState::~MainMenuState()
{
    std::cout << "Main menu State deleted" << std::endl;
}

/**
 * @brief Method that handles keyboard inputs for that specific state
 */
void MainMenuState::handleKeyboardInputs()
{
    //
}

/**
 * @brief Function that updates the game state
 * @param dt    time since last frame
 */
void MainMenuState::update(const float& dt)
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
void MainMenuState::render(std::shared_ptr<sf::RenderTarget> target)
{
    if (!target)
        target = window_;

    renderButtons(target);
}

/**
 * @brief Function that loads the textures needed for the state
 */
void MainMenuState::loadTextures()
{
    sf::Texture texture;

    // Play button texture
    if (!texture.loadFromFile("resources/menu/default_button.png"))
        throw("Error : Could not load default button texture");

    textures_["DEFAULT_BUTTON"] = std::make_shared<sf::Texture>(texture);
}

/**
 * @brief Function that initializes the keybinds of the state
 */
void MainMenuState::initKeybinds()
{
    if (keys_)
    {
        std::ifstream config_file("config/main_menu_state_keybinds.ini");
        
        if (!config_file)
            throw("Config file not found : main_menu_state_keybinds.ini");

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
void MainMenuState::initFonts()
{
    if (!font_.loadFromFile("fonts/basic_font.ttf"))
    {
        throw("Error : Could not load font : basic_font.ttf");
    }
    
}

/**
 * @brief Function that initializes the buttons
 */
void MainMenuState::initButtons()
{

    gui::ColorButtonHandler handler(
        sf::Color(255, 255, 255), // Normal
        sf::Color(200, 200, 200), // Hover
        sf::Color(51, 51, 51), // Clicked
        sf::Color(100, 100, 100) // Off
    );

    // Play button
    buttons_["PLAY"] = std::make_unique<gui::Button>(
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f - gui::Button::BUTTON_SIZE_X / 2.0f,
            static_cast<float>(window_->getSize().y) / 2.0f - gui::Button::BUTTON_SIZE_Y / 2.0f
        ), // Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y),
        &font_,
        handler,
        "PLAY"
    );
    buttons_.at("PLAY")->addTexture(textures_["DEFAULT_BUTTON"]);

    // Exit button
    buttons_["QUIT"] = std::make_unique<gui::Button>(
        Vector(
            static_cast<float>(window_->getSize().x) - gui::Button::BUTTON_SIZE_X,
            static_cast<float>(window_->getSize().y) - gui::Button::BUTTON_SIZE_Y
        ), // Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y), // Size
        &font_,
        handler,
        "QUIT"
    );
    buttons_.at("QUIT")->addTexture(textures_["DEFAULT_BUTTON"]);


    // Settings button
    buttons_["SETTINGS"] = std::make_unique<gui::Button>(
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f - gui::Button::BUTTON_SIZE_X / 2.0f, // X Position
            static_cast<float>(window_->getSize().y) / 2.0f - gui::Button::BUTTON_SIZE_Y / 2.0f + 2 * gui::Button::BUTTON_SIZE_Y
        ), // Y Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y), // Size
        &font_,
        handler,
        "SETTINGS"
    );
    buttons_.at("SETTINGS")->addTexture(textures_["DEFAULT_BUTTON"]);
    
    // Settings button
    buttons_["EDITOR"] = std::make_unique<gui::Button>(
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f - gui::Button::BUTTON_SIZE_X / 2.0f,
            static_cast<float>(window_->getSize().y) / 2.0f - gui::Button::BUTTON_SIZE_Y / 2.0f + 4 * gui::Button::BUTTON_SIZE_Y
        ), // Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y), // Size
        &font_,
        handler,
        "EDITOR"
    );
    buttons_.at("EDITOR")->addTexture(textures_["DEFAULT_BUTTON"]);


}

/**
 * @brief Function that updates the buttons of the state
 * @param dt    Time since last frame
 */
void MainMenuState::updateButtons(const float& dt)
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
void MainMenuState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{

    for (auto& button : buttons_)
    {
        button.second->render(target);
    }
}

/**
 * @brief Function that handles when a button is clicked 
 */
void MainMenuState::handleButtonEvents()
{
    
    if (buttons_["QUIT"]->getButtonState() == gui::CLICKED)
    {
        endState();
    } 
    else if (buttons_["PLAY"]->getButtonState() == gui::CLICKED)
    {
        states_.push(std::make_unique<GameState>(states_, window_, keys_));
    }
    else if (buttons_["SETTINGS"]->getButtonState() == gui::CLICKED)
    {
        states_.push(std::make_unique<SettingsState>(states_, window_, keys_));
    }
    else if (buttons_["EDITOR"]->getButtonState() == gui::CLICKED)
    {
        states_.push(std::make_unique<EditorState>(states_, window_, keys_));
    }
}