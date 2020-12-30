#ifndef CHUNK_H
#define CHUNK_H

#include "../Drawable.h"

#include "TileHandler.h"
#include "CollisionHandler.h"
#include "../Entities/HitboxComponent.h"
#include "TerrainGenerator.h"

class Chunk
    :   public Drawable
{

public:

    static const float DEFAULT_SIZE;

    Chunk(std::shared_ptr<sf::Texture> textureSheet, 
            TerrainGenerator& terrainGenerator, 
            const Vector& position, const Vector& size = Vector(DEFAULT_SIZE), 
            const Vector& tileSize = Vector(TileHandler::DEFAULT_SIZE));
    virtual ~Chunk();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
    virtual void renderOnTop(std::shared_ptr<sf::RenderTarget> target = nullptr);

    std::vector<Vector> collide(const HitboxComponent& hitbox);

    std::array<Vector, 4> getNeighbours(const Vector& position) const;
    Vector getPositionOfTile(std::size_t x, std::size_t y) const;
    const std::string& getTile(const Vector& globalPosition) const ;
    Vector getPosition() const;
    sf::FloatRect getRectangle() const;
    const Vector& getSize() const;
    const Vector& getTileSize() const;

private:

    std::unordered_map<Vector, sf::FloatRect, VectorHasher> blocksColliding(const HitboxComponent& hitbox) const;
    std::unordered_map<Vector, std::string, VectorHasher> naturalElementsColliding(const HitboxComponent& hitbox) const;
    void initTerrain();
    void addTile(const Vector& position, const float& height);
    void generateNaturalElements(const Vector& position, const int height);
    void generateSmoothTextures();

    TerrainGenerator& terrainGenerator_;
    Vector position_;
    Vector size_;
    Vector tileSize_;
    std::shared_ptr<sf::Texture> textureSheet_;

    std::unordered_map<Vector, std::string, VectorHasher, VectorEqual> tiles_;
    std::unordered_map<Vector, std::string, VectorHasher, VectorEqual> nature_;
    std::unordered_map<Vector, sf::FloatRect, VectorHasher, VectorEqual> blocks_;
};


#endif