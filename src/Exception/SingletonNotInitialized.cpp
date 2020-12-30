#include "../headers.h"
#include "SingletonNotInitialized.h"


/**
 * @brief Constructor
 * @param message       Message to throw
 */
SingletonNotInitialized::SingletonNotInitialized(const std::string& message)
    :   message_(message)
{

}

/**
 * @brief Destructor
 */
SingletonNotInitialized::~SingletonNotInitialized()
{

}

/**
 * @brief Overloading method
 */
const char* SingletonNotInitialized::what() const noexcept
{
    return message_.data();
}