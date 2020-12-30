#include "../headers.h"
#include "Vector.h"

// Constructors

Vector::Vector()
    :   x_(0),  y_(0)
{}

Vector::Vector(float x, float y)
    :   x_(x),  y_(y)
{}

Vector::Vector(float value)
    :   x_(value),  y_(value)
{}

Vector::Vector(int x, int y)
    :   x_(static_cast<float>(x))
    ,   y_(static_cast<float>(y))
{}

Vector::Vector(sf::Vector2f v)
    :   x_(v.x),    y_(v.y)
{}

Vector::Vector(sf::Vector2i v)
    : x_(static_cast<float>(v.x)), y_(static_cast<float>(v.y))
{}

// Destructor
Vector::~Vector()
{

}

/**
 * @brief Function that calculates the norm of the vector
 * @return norm
 */
float Vector::norm() const
{
    return static_cast<float>(sqrt(x_ * x_ + y_ * y_));
}

/**
 * @brief Function that normalizes the vector
 * @return Vector normalized
 */
Vector& Vector::normalize() 
{
    double n = norm();
    if (n == 0)
        throw ("Norm is null");
    
    x_ /= n;
    y_ /= n;

    return *this;
}


/**
 * @brief Function that returns the positions of the 4 corners of a rectangle
 * @param rect      Rectangle
 * @return          Position
 */
std::array<Vector, 4> Vector::getCorners(const sf::FloatRect& rect)
{
    std::array<Vector, 4> array;
    array[0] = Vector(rect.left, rect.top);
    array[1] = Vector(rect.left, rect.top + rect.height);
    array[2] = Vector(rect.left + rect.width, rect.top + rect.height);
    array[3] = Vector(rect.left + rect.width, rect.top);
    return array;
}

/**
 * @brief Operator =
 * @param v         Vector to compare
 */
bool Vector::operator==(const Vector& v) const
{
    return (x_ == v.x_) && (y_ == v.y_);
}

/**
 * @brief Operator <
 * @param v         Vector to compare
 */
bool Vector::operator<(const Vector& v) const
{
    if (x_ != v.x_)
        return x_ < v.x_;
    
    return y_ < v.y_;
}

/**
 * @brief Operator + that adds up two vectors
 * @param vector    Vector to add
 * @return          Sum of the two vectors
 */
Vector Vector::operator+(const Vector& vector) const
{
    Vector res;
    res.x_ = x_ + vector.x_;
    res.y_ = y_ + vector.y_;
    return res;
}

/**
 * @brief Operator - that substracts two vectors
 * @param vector    Vector to substract
 * @return          Difference of the two vectors
 */
Vector Vector::operator-(const Vector& vector) const
{
    Vector res;
    res.x_ = x_ - vector.x_;
    res.y_ = y_ - vector.y_;
    return res;
}

/**
 * @brief Operator * that mutiplies the vector by a constant
 * @param k         Constant
 * @return          Multiplied vector
 */
Vector Vector::operator*(const float& k) const
{
    Vector res;
    res.x_ = x_ * k;
    res.y_ = y_ * k;
    return res;
}

/**
 * @brief operator / that divides a vector by a constant
 * @param k     Constant
 * @return      Divided vector
 */
Vector Vector::operator/(const float& k) const
{
    if (k == 0)
        throw("Error : Division by zero");
    return (*this).operator*(1.0f / k);
}


/**
 * @brief operator += that add up to vectors
 * @param vector    Vector to add
 * @return          Added vector
 */
Vector& Vector::operator+=(const Vector& vector)
{
    (*this) = (*this).operator+(vector);
    return *this;
}

/**
 * @brief operator *= that multiplies the vecteur by a constant
 * @param k     Constant
 * @return      Multiplied vector
 */
Vector& Vector::operator*=(const float& k)
{
    (*this) = (*this).operator*(k);
    return *this;
}

/**
 * @brief operator << 
 * @param os    Stream
 * @param v     Vector to print
 * @return      Stream with vector inside
 */
std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << v.x_ << ", " << v.y_;
    return os;
}

/**
 * @brief Method that returns the vector as an sf::Vector2f
 * @return Vector
 */
sf::Vector2f Vector::getAsVector2f() const
{
    return sf::Vector2f(x_, y_);
}

/**
 * @brief Method that returns the vector as an sf::Vector2i
 * @return Vector
 */
sf::Vector2i Vector::getAsVector2i() const
{
    return sf::Vector2i(static_cast<int>(x_), static_cast<int>(y_));
}

/**
 * @brief Method that returns the x component of the vector
 * @return X component
 */
float Vector::getX() const
{
    return x_;
}

/**
 * @brief Method that returns the y component of the vector
 * @return Y component
 */
float Vector::getY() const
{
    return y_;
}

/**
 * @brief Method that changes the x component of the vector
 * @param x X component
 */
void Vector::setX(float x)
{
    x_ = x;
}

/**
 * @brief Method that changes the x component of the vector
 * @param y Y component
 */
void Vector::setY(float y)
{
    y_ = y;
}

