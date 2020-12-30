#ifndef INVENTORY_BAR_H
#define INVENTORY_BAR_H

#include "../Drawable.h"

namespace HUD 
{
    class InventoryBar 
        :   public Drawable
    {

    public:

        static constexpr int NUMBER_OF_ITEMS = 8;

        InventoryBar(const Vector& position, const Vector& size);
        virtual ~InventoryBar();

        virtual void update(const float& dt);
        virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

    private:

        void initBackground();
        void initItemSlots();

        Vector position_;
        Vector size_;
        
        // Size of each items
        Vector itemSize_;

        // Off set between each items (render)
        float offset_;

        sf::RectangleShape background_;
        sf::RectangleShape itemSlots_[NUMBER_OF_ITEMS];

    };

}

#endif