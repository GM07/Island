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
    virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);
    virtual void renderOnTop(std::shared_ptr<sf::RenderWindow> target = nullptr);

    std::vector<Vector> collide(const HitboxComponent& hitbox) const;

    Vector getPositionOfTile(std::size_t x, std::size_t y) const;
    std::string getTile(const Vector& globalPosition) const ;
    Vector getPosition() const;
    sf::FloatRect getRectangle() const;

private:

    std::unordered_map<Vector, std::string, VectorHasher> tilesColliding(const HitboxComponent& hitbox) const;
    void initTerrain();
    void addTile(const Vector& position, const float& height);
    void generateTrees(const Vector& position, const float& height);

    TerrainGenerator& terrainGenerator_;
    Vector position_;
    Vector size_;
    Vector tileSize_;
    std::shared_ptr<sf::Texture> textureSheet_;

    std::unordered_multimap<Vector, std::string, VectorHasher> tiles_;
    std::unordered_multimap<Vector, std::string, VectorHasher> nature_;

};


#endif