#include "../../include/headers.h"
#include "../../include/Map/TerrainGenerator.h"

/**
 * @brief Constructor
 * @param seed          Seed for the terrain
 */
TerrainGenerator::TerrainGenerator(int seed)
    :   mapGenerator_(seed)
    ,   treeGenerator_(seed)
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
float TerrainGenerator::treeValue(const Vector& position) const
{
    float terrainCoefficient = mapValue(position);

    if (terrainCoefficient < GRASS_HEIGHT)
    {
        return 0.0f;
    }

    return terrainCoefficient + treeGenerator_.noise(position.getX(), position.getY(), 0.0);
}