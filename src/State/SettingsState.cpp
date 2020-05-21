#include "../../include/headers.h"
#include "../../include/State/SettingsState.h"

/**
 * @brief Constructor with parameters
 * @param states    Stack of the states in the game
 * @param window    Window where the state will be drawn into
 * @param keys      Keys supported by the game
 */
SettingsState::SettingsState(
    std::stack<std::unique_ptr<State>>& states, 
    std::shared_ptr<sf::RenderWindow> window, 
    std::map<std::string, int>* keys
)
    :   State(states, window, keys)
{
    std::cout << "Settings State created \n";
    loadTextures();
    initFonts();
    initKeybinds();

    initButtons();
    initDropDownLists();
}

/**
 * @brief Destructor
 */
SettingsState::~SettingsState()
{
    std::cout << "Settings State deleted \n";
}

/**
 * @brief Method that handles keyboard inputs for that specific state
 */
void SettingsState::handleKeyboardInputs()
{
    //
}

/**
 * @brief Function that updates the game state
 * @param dt    time since last frame
 */
void SettingsState::update(const float& dt)
{
    updateMousePosition();

    updateButtons(dt);
    updateDropDownLists(dt);

    handleKeyboardInputs();
    handleButtonEvents();
}

/**
 *  @brief Function that renders the game state
 *  @param target   RenderWindow where the state will be drawn
 */
void SettingsState::render(std::shared_ptr<sf::RenderWindow> target)
{
    if (!target)
        target = window_;

    renderButtons(target);
    renderDropDownLists(target);
}


/**
 * @brief Function that loads the textures needed for the state
 */
void SettingsState::loadTextures()
{
    sf::Texture texture;

    // Quit button texture
    if (!texture.loadFromFile("resources/menu/default_button.png"))
        throw("Error : Could not load quit button texture");

    textures_["DEFAULT_BUTTON"] = std::make_shared<sf::Texture>(texture);

}

/**
 * @brief Function that initializes the keybinds of the state
 */
void SettingsState::initKeybinds()
{
    if (keys_)
    {
        std::ifstream config_file("config/settings_state_keybinds.ini");
        
        if (!config_file)
            throw("Config file not found : settings_state_keybinds.ini");

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
 * @brief Function that initializes the buttons
 */
void SettingsState::initButtons()
{

    gui::ColorButtonHandler handler(
        sf::Color(255, 255, 255),   // Normal
        sf::Color(200, 200, 200),   // Hover
        sf::Color(51, 51, 51),      // Clicked
        sf::Color(100, 100, 100)    // Off
    );

    // Back button
    buttons_["BACK"] = std::make_unique<gui::Button>(
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f + 50,
            static_cast<float>(window_->getSize().y) - gui::Button::BUTTON_SIZE_Y - 32.0f
        ), // Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y), // Size
        &font_,
        handler,
        "Back"
    );
    buttons_.at("BACK")->addTexture(textures_["DEFAULT_BUTTON"]);

    // Apply button
    buttons_["APPLY"] = std::make_unique<gui::Button>(
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f - gui::Button::BUTTON_SIZE_X - 50,
            static_cast<float>(window_->getSize().y) - gui::Button::BUTTON_SIZE_Y - 32.0f
        ), // Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y), // Size
        &font_,
        handler,
        "Apply"
    );
    buttons_.at("APPLY")->addTexture(textures_["DEFAULT_BUTTON"]);
}

/**
 * @brief Function that initializes the drop down lists
 */
void SettingsState::initDropDownLists()
{
    gui::ColorButtonHandler colorButtonHandler(
        sf::Color(50, 50, 50),
        sf::Color(75, 75, 75),
        sf::Color(25, 25, 25),
        sf::Color(10, 10, 10),
        sf::Color::White,
        sf::Color::Transparent,
        sf::Color::White
    );

    std::vector<std::string> s = {"1920x1080", "800x600", "640x480"};

    dropDownLists_["RESOLUTION"] = std::make_unique<gui::DropDownList>(
        font_, 
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f - gui::Button::BUTTON_SIZE_X / 2.0f, 
            static_cast<float>(window_->getSize().y) / 2.0f - gui::Button::BUTTON_SIZE_Y / 2.0f
        ), // Position
        Vector(gui::Button::BUTTON_SIZE_X, gui::Button::BUTTON_SIZE_Y), // Size
        colorButtonHandler, 30, // Character size
        "1920x1080",
        s
    );
}

/**
 * @brief Function that initializes the state's fonts
 */
void SettingsState::initFonts()
{
    if (!font_.loadFromFile("fonts/basic_font.ttf"))
    {
        throw("Error : Could not load font : basic_font.ttf");
    }
    
}


/**
 * @brief Function that updates the buttons of the state
 * @param dt    Time since last frame
 */
void SettingsState::updateButtons(const float& dt)
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
void SettingsState::renderButtons(std::shared_ptr<sf::RenderWindow> target)
{

    for (auto& button : buttons_)
    {
        button.second->render(target);
    }
}


/**
 * @brief Function that handles when a button is clicked
 */
void SettingsState::handleButtonEvents()
{
    if (buttons_.at("BACK")->getButtonState() == gui::CLICKED)
    {
        endState();
    }   

    if (buttons_.at("APPLY")->getButtonState() == gui::CLICKED)
    {
        
    }
}

/**
 * @brief Function that updates the drop down lists of the state
 * @param dt    Time since last frame
 */
void SettingsState::updateDropDownLists(const float& dt)
{
    for (const auto& list : dropDownLists_)
    {
        list.second->update(dt);
        list.second->updateMousePosition(mousePositionView);
    }   
}

/**
 * @brief Function that renders the drop down lists of the state
 */
void SettingsState::renderDropDownLists(std::shared_ptr<sf::RenderWindow> target)
{

    for (const auto& list : dropDownLists_)
    {
        list.second->render(target);
    }
}

