#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>
#include "SFML/Graphics.hpp"

class Vector
{
public:

    // Constructors
    Vector();
    Vector(float x, float y);
    Vector(float value);
    Vector(int x, int y);
    Vector(sf::Vector2f v);
    Vector(sf::Vector2i v);

    // Destructor
    ~Vector();

    // Functions
    float norm() const;
    Vector& normalize();
    static std::array<Vector, 4> getCorners(const sf::FloatRect& rect);

    // Operators
    bool operator==(const Vector& v) const;
    bool operator<(const Vector& v) const;
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(const float& k) const;
    Vector operator/(const float& k) const;
    Vector& operator+=(const Vector& v);
    Vector& operator*=(const float& k);
    friend std::ostream& operator<<(std::ostream& os, const Vector& v);

    // Getters
    sf::Vector2f getAsVector2f() const;
    sf::Vector2i getAsVector2i() const;
    float getX() const;
    float getY() const;

    // Setters
    void setX(float x);
    void setY(float y);

private:
    float x_;
    float y_;

};

class VectorHasher
{
public:
    std::size_t operator()(const Vector& v) const
    {
        using std::size_t;
        using std::hash;
        
        std::size_t h1 = std::hash<float>()(v.getX());
        std::size_t h2 = std::hash<float>()(v.getY());
        return h1 ^ (h2 << 1);
    }


};

class VectorEqual
{
public:
    std::size_t operator()(const Vector& v1, const Vector& v2) const
    {
        return v1.getX() == v2.getX() && v1.getY() && v2.getY();
    }


};

class VectorSorterByY
{
public:
    bool operator()(const Vector& v1, const Vector& v2)
    {
        return v1.getY() < v2.getY();
    }
};


#endif