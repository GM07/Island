#ifndef MAP_H
#define MAP_H

#include "../Drawable.h"

#include "../Entities/Player.h"

#include "Chunk.h"
#include "TerrainGenerator.h"

class Map
    :   public Drawable
{

public:

    static const float CHUNK_RADIUS;

    Map(const sf::View& view, Player& player,
        const Vector& center,
        const Vector& chunkSize = Vector(Chunk::DEFAULT_SIZE),
        const Vector& tileSize = Vector(TileHandler::DEFAULT_SIZE));
    virtual ~Map();

    virtual void update(const float& dt);
    virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);
    virtual void renderOnTop(std::shared_ptr<sf::RenderWindow> target = nullptr);
    virtual void loadTextures();

    void updateChunks();

    const std::string& getTile(const Vector& globalPosition) const;
    sf::FloatRect getViewRect() const;

private:

    void collide();
    std::unordered_set<const Chunk*> chunksColliding(const HitboxComponent& hitbox);
    void generateChunks();
    void generateChunk(const Vector& position);
    bool isChunkGenerated(const Vector& position) const;

    void removeChunks();

    const sf::View& view_;
    Player& player_;
    Vector center_;
    Vector chunkSize_;
    Vector tileSize_;

    const Chunk* centerChunk_;
    std::unordered_map<Vector, std::unique_ptr<Chunk>, VectorHasher> chunks_;

    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures_;

    TerrainGenerator terrainGenerator_;

};


#endif