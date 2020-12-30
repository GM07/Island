#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "../Entities/Player.h"
#include "../Entities/Demon.h"
#include "../Entities/DemonSpawner.h"
#include "../Menu/PauseMenu.h"
#include "../Map/Map.h"
#include "../HUD/InventoryBar.h"
#include "../Entities/DamageRenderer.h"
#include "../HUD/ExperienceBar.h"

class GameState
    : public State
{
public:

    static constexpr float PLAYER_SIZE = 64.f;

    GameState(std::stack<std::unique_ptr<State>>& states, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* keys);
    virtual ~GameState();

    virtual void handleKeyboardInputs();
    virtual void handlePausedKeyboardInputs();
    virtual void handleButtonEvents();
    
    virtual void updateMousePosition();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

    virtual void loadTextures();

private:

    virtual void loadPlayerTextures();
    virtual void loadEntitiesTexture();
    virtual void loadPauseMenuTextures();

    virtual void initEntities();
    virtual void initKeybinds();
    virtual void initPauseMenu();
    virtual void initView();
    virtual void initExperienceBar();

    std::shared_ptr<Player> player_;
    sf::View view_;
    Map map_;
    PauseMenu pauseMenu_;
    HUD::InventoryBar inventoryBar_;
    DemonSpawner demonSpawner_;
    std::shared_ptr<sf::RenderTexture> renderTexture_;
    sf::Sprite renderSprite_;
    sf::View lastView_;
    sf::Font font_;
    std::unique_ptr<HUD::ExperienceBar> experienceBar_;

    Vector mousePositionMap_;

};

#endif