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
 * @brief Function that returns the map generator
 * @return Map generator
 */
const PerlinNoise& TerrainGenerator::getMapGenerator() const
{
    return mapGenerator_;
}

/**
 * @brief Function that returns the map generator
 * @return Map generator
 */
const PerlinNoise& TerrainGenerator::getTreeGenerator() const
{
    return treeGenerator_;
}
