#include "../../include/headers.h"
#include "../../include/HUD/InventoryBar.h"


/**
 * @brief Constructor
 * @param position      Position of the bar
 * @param size          Size of the bar
 */
HUD::InventoryBar::InventoryBar(const Vector& position, const Vector& size)
    :   position_(position)
    ,   size_(size)
    ,   offset_(0.02f * size.getX())
    ,   background_(size.getAsVector2f())
{
    initBackground();
    initItemSlots();
}

/**
 * @brief Destructor
 */
HUD::InventoryBar::~InventoryBar()
{

}

/**
 * @brief Function that updates the bar
 * @param dt        Time since last frame
 */
void HUD::InventoryBar::update(const float& dt)
{

}

/**
 * @brief Function that renders the bar
 * @param target    Where to draw the bar
 */
void HUD::InventoryBar::render(std::shared_ptr<sf::RenderWindow> target)
{
    target->draw(background_);
    
    for (std::size_t i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        target->draw(itemSlots_[i]);
    }
}


/**
 * @brief Function that initializes the background
 */
void HUD::InventoryBar::initBackground()
{
    background_.setFillColor(sf::Color(51, 51, 51, 200));
    background_.setPosition(position_.getAsVector2f());
    background_.setOutlineColor(sf::Color::Black);
    background_.setOutlineThickness(0.5);
}

/**
 * @brief Function that initializes the item holders
 */
void HUD::InventoryBar::initItemSlots()
{
    float sizeX = (size_.getX() - ((NUMBER_OF_ITEMS + 1) * offset_)) / static_cast<float>(NUMBER_OF_ITEMS);
    float sizeY = size_.getY() - (2 * offset_);

    for (std::size_t i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        sf::RectangleShape rect(sf::Vector2f(sizeX, sizeY));
        rect.setPosition(sf::Vector2f(position_.getX() + (i + 1) * offset_ + i * sizeX, position_.getY() + offset_));
        rect.setFillColor(sf::Color(51, 51, 51));
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(1.0f);

        std::cout << rect.getPosition().x << " - " << rect.getPosition().y << "\n";
        itemSlots_[i] = rect;
    }
}



