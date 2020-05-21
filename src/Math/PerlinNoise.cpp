#include "../../include/headers.h"
#include "../../include/Math/PerlinNoise.h"


/**
 * @brief Constructor
 * @param seed      Seed to create the perlin noise
 */
PerlinNoise::PerlinNoise(unsigned int seed)
    :   seed_(seed)
{
    permutation_.resize(256);

    std::iota(permutation_.begin(), permutation_.end(), 0);
    std::default_random_engine engine(seed);
    std::shuffle(permutation_.begin(), permutation_.end(), engine);
    permutation_.insert(permutation_.end(), permutation_.begin(), permutation_.end());
 
}

/**
 * @brief Destructor
 */
PerlinNoise::~PerlinNoise()
{

}

/**
 * @brief Function that generates values
 * @param x     x position
 * @param y     y position
 */
float PerlinNoise::noise(float x, float y, float z) const
{
    int X = (int) std::floor(x) & 255, Y = (int) std::floor(y) & 255, Z = (int) std::floor(z) & 255;
    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    double u = fade(x), v = fade(y), w = fade(z);
    int A = permutation_[X] + Y, 
        AA = permutation_[A] + Z, 
        AB = permutation_[A + 1] + Z, 
        B = permutation_[X + 1] + Y, 
        BA = permutation_[B] + Z, 
        BB = permutation_[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(permutation_[AA], x, y, z),
                grad(permutation_[BA], x - 1, y, z)),
                lerp(u, grad(permutation_[AB], x, y - 1, z),
                grad(permutation_[BB], x - 1, y - 1, z))),
                lerp(v, lerp(u, grad(permutation_[AA + 1], x, y, z - 1),
                grad(permutation_[BA + 1], x - 1, y, z - 1)),
                lerp(u, grad(permutation_[AB + 1], x, y - 1, z - 1),
                grad(permutation_[BB+1], x - 1, y - 1, z - 1))));  
}

/**
 * @brief Fade function
 */
float PerlinNoise::fade(float t) const
{
    return t * t * t * (t * (t * 6 - 15) + 10); 
}

/**
 * @brief Lerp function
 */
float PerlinNoise::lerp(float t, float a, float b) const
{ 
    return a + t * (b - a); 
}

/**
 * @brief Grad function
 */
float PerlinNoise::grad(int hash, float x, float y, float z) const
{
    int h = hash & 15;                      
    float u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}