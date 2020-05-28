#include "../../include/headers.h"
#include "../../include/Map/TerrainGenerator.h"

/**
 * @brief Constructor
 * @param seed          Seed for the terrain
 */
TerrainGenerator::TerrainGenerator(int seed)
    :   mapGenerator_(seed)
    ,   treeGenerator_(seed ^ (seed + 1))
{

}

/**
 * @brief Destructor
 */
TerrainGenerator::~TerrainGenerator()
{

}

/**
 * @brief Function that generates the map
 * @param position      Position of the tile
 * @return value of the tile at a certain position
 */
float TerrainGenerator::mapValue(const Vector& position) const
{
    return mapGenerator_.noise(position.getX(), position.getY(), 0.0);
}

/**
 * @brief Function that returns the map generator
 * @return Map generator
 */
int TerrainGenerator::generateNaturalElement(const Vector& position) const
{
    srand(hash(position));
    int value = rand() % 80;
    
    return value;
}

/**
 * @brief Hashing function for pseudo-random number generator
 */
unsigned int TerrainGenerator::hash(const Vector& position) const
{
    return static_cast<unsigned int>(static_cast<int>(position.getX() * position.getY()) ^ (static_cast<int>(position.getY()) << 1));
}