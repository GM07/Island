#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

class PerlinNoise
{
public:
    PerlinNoise(unsigned int seed);
    virtual ~PerlinNoise();

    float noise(float x, float y, float z);

private:

    float fade(float t);
    float lerp(float t, float a, float b);
    float grad(int hash, float x, float y, float z);

    unsigned int seed_;
    std::vector<int> permutation_;
};

#endif