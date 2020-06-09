#include "../../include/headers.h"
#include "../../include/State/GameState.h"

/**
 * @brief Constructor with parameters
 * @param states    Stack of the states in the game
 * @param window    Window where the state will be drawn into
 * @param keys      Keys supported by the game
 */
GameState::GameState(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys)
    :   State(states, window, keys)
    
    ,   player_(
            std::make_shared<Player>(Vector(0, 0),      // Position
            Vector(PLAYER_SIZE),                        // Size
            MovementComponents(400.0f, 29.0f, 5.0f))    // Max velocity, acceleration, deceleration
        )   
    
    ,   view_(
            (player_->getPosition() - player_->getSize() * 0.5f).getAsVector2f(),   // Center at the player's position
            sf::Vector2f(window_->getSize().x, window_->getSize().y)                // Size of the window
        )  
    
    ,   map_(view_, *player_, player_->getPosition())   // Center of the map
    ,   pauseMenu_(window)
    ,   inventoryBar_(
            Vector(static_cast<float>(window_->getSize().x) / 2.0f - 16 * TileHandler::DEFAULT_SIZE / 2.0f, static_cast<float>(window_->getSize().y) - 4 * TileHandler::DEFAULT_SIZE).getAsVector2f(),
            Vector(16 * TileHandler::DEFAULT_SIZE, 2 * TileHandler::DEFAULT_SIZE)
        )
    ,   demonSpawner_(
            player_->getCenter(), 32 * TileHandler::DEFAULT_SIZE, Demon(
                Vector(0.0f, 0.0f),
                Vector(PLAYER_SIZE),
                player_->getCenter(),
                MovementComponents(300.0f, 29.0f, 5.0f)
            ), 5
        )
    ,   lastView_(window_->getView())
{

    std::cout << "Game State created\n";

    player_->setPosition(Vector(0, 32));

    initView();    
    loadTextures();
    initPauseMenu();
    initEntities();
    initKeybinds();
}

/**
 *  @brief Destructor
 */
GameState::~GameState()
{
    window_->setView(lastView_);
    std::cout << "Game State deleted" << std::endl;
}

/**
 * @brief Method that handles keyboard inputs for that specific state
 */
void GameState::handleKeyboardInputs()
{
    // Pause
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("PAUSE"))) && getKeyTime())
        pause();

    // Player movement
    if (player_->isDirectionAvailable(LEFT) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_LEFT"))))
    {
        player_->move(-1.0f, 0.0f);
    }
    if (player_->isDirectionAvailable(RIGHT) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_RIGHT"))))
    {
        player_->move(1.0f, 0.0f);
    }
    if (player_->isDirectionAvailable(DOWN) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_DOWN"))))
    {
        player_->move(0.0f, 1.0f);
    }
    if (player_->isDirectionAvailable(UP) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("MOVE_UP"))))
    {
        player_->move(0.0f, -1.0f);
    }
}

/**
 * @brief Function that updates the inputs when game state is paused
 */
void GameState::handlePausedKeyboardInputs()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds_.at("PAUSE"))) && getKeyTime())
    {
        unpause();  
        view_.setCenter(player_->getPosition().getAsVector2f());
        window_->setView(view_);
    }
}

/**
 * @brief Function that handles the button's events
 */
void GameState::handleButtonEvents()
{
    if (pauseMenu_.isButtonPressed("QUIT"))
    {
        endState();
    }
}

/**
 * @brief Function that updates the game state
 * @param dt    time since last frame
 */
void GameState::update(const float& dt)
{
    updateMousePosition();
    updateKeyTime(dt);

    if (!paused_)
    {
        view_.setCenter(player_->getPosition().getAsVector2f());
        player_->update(dt);


        if (!(player_->getVelocity() == Vector(0.0f)))
            map_.update(dt);

        inventoryBar_.update(dt);

        handleKeyboardInputs();

        demonSpawner_.update(dt);
    }
    else
    {
        handlePausedKeyboardInputs();
        handleButtonEvents();
        pauseMenu_.update(dt);
        pauseMenu_.updateMousePosition(mousePositionView);
    }
    
}

/**
 *  @brief Function that renders the game state
 *  @param target   RenderWindow where the state will be drawn
 */
void GameState::render(std::shared_ptr<sf::RenderWindow> target)
{
    if (!target)
        target = window_;

    window_->setView(view_);
    map_.render(target);

    // Rendering entities

    player_->render(target);

    demonSpawner_.render(target);

    // End of entities render

    map_.renderOnTop(target);

    window_->setView(lastView_);
    inventoryBar_.render(target);

    if (paused_)
    {
        pauseMenu_.render(target);
    }
    
}

/**
 * @brief Function that loads the textures needed by the state
 */
void GameState::loadTextures()
{
    map_.loadTextures();
    loadPlayerTextures();
    loadEntitiesTexture();
    loadPauseMenuTextures();
}

/**
 * @brief Function that loads the textures needed by the player
 */
void GameState::loadPlayerTextures() 
{
    sf::Texture texture;

    // Player texture
    if (!texture.loadFromFile("resources/game/player/player_sprite_sheet.png"))
        throw("Error : Could not load player's sprite sheet texture");

    textures_["PLAYER_SPRITE_SHEET"] = std::make_shared<sf::Texture>(texture);

    if (!texture.loadFromFile("resources/game/player/sword.png"))
        throw("Error : Could not load player's sprite sheet texture");

    textures_["SWORD"] = std::make_shared<sf::Texture>(texture);

}

/**
 * @brief Function that loads the textures needed by the player
 */
void GameState::loadEntitiesTexture() 
{
    sf::Texture texture;

    // Player texture
    if (!texture.loadFromFile("resources/game/enemy_sprite_sheet.png"))
        throw("Error : Could not load player's sprite sheet texture");

    textures_["DEMON"] = std::make_shared<sf::Texture>(texture);

}

/**
 * @brief Function that loads the textures needed by the pause menu
 */
void GameState::loadPauseMenuTextures()
{
    sf::Texture texture;

    if (!texture.loadFromFile("resources/menu/default_button.png"))
        throw("Error : Could not load quit button texture");

    textures_["DEFAULT_BUTTON"] = std::make_shared<sf::Texture>(texture);
}

/**
 * @brief Function that initializes the entities
 */
void GameState::initEntities()
{
    player_->addTexture(textures_["PLAYER_SPRITE_SHEET"]);
    player_->addSwordTexture(textures_["SWORD"]);

    demonSpawner_.addTexture(textures_["DEMON"]);
}

/**
 * @brief Function that initializes the keybinds of the state
 */
void GameState::initKeybinds()
{
    if (keys_)
    {
        std::ifstream config_file("config/game_state_keybinds.ini");
        
        if (!config_file)
            throw("Config file not found : game_state_keybinds.ini");

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
 * @brief Function that initializes the pause menu
 */
void GameState::initPauseMenu()
{
    gui::ColorButtonHandler handler(
        sf::Color(255, 255, 255), // Normal
        sf::Color(200, 200, 200), // Hover
        sf::Color(51, 51, 51), // Clicked
        sf::Color(100, 100, 100) // Off
    );

    pauseMenu_.addButton(
        "QUIT",
        Vector(
            static_cast<float>(window_->getSize().x) / 2.0f - gui::Button::BUTTON_SIZE_X / 2.0f,
            static_cast<float>(window_->getSize().y) - gui::Button::BUTTON_SIZE_Y - 32
        ), // Position
        handler,
        "Quit"
    );
    pauseMenu_.addTextureToButton("QUIT", textures_.at("DEFAULT_BUTTON"));
}

/**
 * @brief Function that initializes the view
 */
void GameState::initView()
{
    view_.zoom(1.0f);
    window_->setView(view_);
}



