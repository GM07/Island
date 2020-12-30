#include "../headers.h"
#include "TileNotFound.h"


/**
 * @brief Constructor
 * @param message       Message to throw
 */
TileNotFound::TileNotFound(const std::string& message)
    :   message_(message)
{

}

/**
 * @brief Destructor
 */
TileNotFound::~TileNotFound()
{

}

/**
 * @brief Overloading method
 */
const char* TileNotFound::what() const noexcept
{
    return message_.data();
}