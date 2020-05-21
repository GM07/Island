#include "../../include/headers.h"
#include "../../include/GUI/DropDownList.h"

/**
 * @brief Constructor
 * @param font                  Font to use for the list
 * @param position              Position of the list
 * @param elementSize           Size of each element of the list
 * @param colorButtonHandler    ColorButtonHandler of each element
 * @param characterSize         Character size
 * @param mainElement           Main element of the list (first one to show up)
 * @param elements              List of elements
 */
gui::DropDownList::DropDownList(
    sf::Font& font, 
    Vector position, Vector elementSize, 
    ColorButtonHandler colorButtonHandler,
    unsigned int characterSize,
    const std::string& mainElement, const std::vector<std::string>& elements
)
    :   font_(font)
    ,   position_(position)
    ,   elementSize_(elementSize)
    ,   colorButtonHandler_(colorButtonHandler)
    ,   characterSize_(characterSize)
    ,   dropDown_(false)
    ,   clickTime_(0.0f)
{
    // Active element
    activeElement_ = new Button(position, elementSize, &font, colorButtonHandler, mainElement, characterSize_);

    // Other elements
    // Creating color button handler without an outline
    ColorButtonHandler c = colorButtonHandler.getWithoutOutline();
    for (std::size_t i = 0; i < elements.size(); i++)
    {
        Button b(
            position + Vector(0.0f, elementSize.getY() * static_cast<float>(i + 1)), elementSize, 
            &font, c, elements[i], characterSize_
        );
        
        elements_.emplace(elements[i], std::make_unique<Button>(b));
        elements_[elements[i]]->update(0);
    }

}

/**
 * @brief Destructor
 */
gui::DropDownList::~DropDownList()
{

}

/**
 * @brief Function that updates the drop down list
 * @param dt                Time since last frame
 */
void gui::DropDownList::update(const float& dt)
{
    updateClickTime(dt);
    activeElement_->update(dt);

    if (dropDown_)
    {
        for (const auto& element : elements_)
        {
            element.second->update(dt);
        }
    }
    
    handleClick();
}

/**
 * @brief Function that renders the drop down list
 * @param target            Where to draw the list
 */
void gui::DropDownList::render(std::shared_ptr<sf::RenderWindow> target)
{
    if (dropDown_)
    {
        for (const auto& element : elements_)
        {
            element.second->render(target);
        }
    }
    
    activeElement_->render(target);

}

/**
 * @brief Function that updates the mouse position of the elements
 * @param mousePosition     Mouse position
 */
void gui::DropDownList::updateMousePosition(Vector mousePosition)
{
    activeElement_->updateMousePosition(mousePosition);

    if (dropDown_)
    {
        for (const auto& element : elements_)
        {
            element.second->updateMousePosition(mousePosition);
        }
    }
    
}

/**
 * @brief Function to add an element to the list
 * @param name      Name of the element
 */
void gui::DropDownList::addElement(const std::string& name)
{
    // TO DO
    std::string n = name + "S";
}


/**
 * @brief Function that adds a texture to every element of the list
 * @param texture   Texture to add
 */
void gui::DropDownList::addTexture(std::shared_ptr<sf::Texture> texture)
{
    for (const auto& element : elements_)
    {
        element.second->addTexture(texture);
    }
    activeElement_->addTexture(texture);

}

/**
 * @brief Function that handles the click on a drop down list
 */
void gui::DropDownList::handleClick()
{
    if (activeElement_->getButtonState() == CLICKED && getClickTime())
    {
        dropDown_ = !dropDown_;
    }

    if (dropDown_)
    {
        // Handles the click when list is shown
        for (const auto& element : elements_)
        {
            if (element.second->getButtonState() == CLICKED && getClickTime())
            {
                activeElement_->setTitle(element.second->getTitle());
                dropDown_ = false;
            }
        }
    }
}

/**
 * @brief Function that returns if the click is authorized
 * @return Can click or not
 */
bool gui::DropDownList::getClickTime()
{
    if (clickTime_ >= maxClickTime_)
    {
        clickTime_ = 0;
        return true;
    }

    return false;
}

/**
 * @brief Function that updates the click time
 * @param dt        Time since last frame
 */
void gui::DropDownList::updateClickTime(const float& dt)
{
    if (clickTime_ < maxClickTime_)
        clickTime_ += 5 * dt;
}