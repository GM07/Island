#ifndef TERRAIN_GENERATOR_H
#define TERRAIN_GENERATOR_H

#include "../Math/PerlinNoise.h"
#include "../Math/Vector.h"

class TerrainGenerator
{
public:

    static constexpr float WATER_HEIGHT = -0.1f;
    static constexpr float SAND_HEIGHT = 0.05f;
    static constexpr float GRASS_HEIGHT = 0.3f;

    TerrainGenerator(int seed);
    virtual ~TerrainGenerator();

    // Getters
    float mapValue(const Vector& position) const;
    int generateNaturalElement(const Vector& position) const;

private:

    unsigned int hash(const Vector& position) const;

    PerlinNoise mapGenerator_;
    PerlinNoise treeGenerator_;
};



#endif