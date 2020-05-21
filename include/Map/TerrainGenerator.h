#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "../Math/PerlinNoise.h"

class TerrainGenerator
{
public:
    TerrainGenerator(int seed);
    virtual ~TerrainGenerator();

    // Getters
    const PerlinNoise& getMapGenerator() const;
    const PerlinNoise& getTreeGenerator() const;

private:
    PerlinNoise mapGenerator_;
    PerlinNoise treeGenerator_;
};



#endif