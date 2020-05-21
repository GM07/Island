#include "../../include/headers.h"
#include "../../include/Map/Map.h"

const float Map::CHUNK_RADIUS = 3.0f;

/**
 * @brief Constructor
 * @param view          View of the player
 * @param player        Player
 * @param center        Center of the map (coordinates of the topleft of the center chunk)
 * @param chunkSize     Size of a single chunk in tiles
 * @param tileSize      Size of a single tile in pixel
 */
Map::Map(const sf::View& view, Player& player, const Vector& center, const Vector& chunkSize, const Vector& tileSize)
    :   view_(view)
    ,   player_(player)
    ,   center_(center)
    ,   chunkSize_(chunkSize)
    ,   tileSize_(tileSize)
    ,   terrainGenerator_(rand())
{

    loadTextures();

    chunks_.emplace(center, std::make_unique<Chunk>(textures_["MAP"], terrainGenerator_, center, chunkSize_, tileSize_));
    centerChunk_ = chunks_.at(center).get();
}

/**
 * @brief Destructor
 */
Map::~Map()
{

}

/**
 * @brief Function that updates the tile
 * @param dt            Time since last frame
 */
void Map::update(const float& dt)
{
    collide();
    updateChunks();
    for (const auto& chunk : chunks_)
    {
        chunk.second->update(dt);
    }
}

/**
 * @brief Function that renders the tilea on top
 * @param target        Where to draw the tile
 */
void Map::render(std::shared_ptr<sf::RenderWindow> target)
{

    for (const auto& chunk : chunks_)
    {
        if (getViewRect().intersects(chunk.second->getRectangle()))
        {
            chunk.second->render(target);
        }
    }
}

/**
 * @brief Function that renders the tiles on top
 * @param target        Where to draw the tile
 */
void Map::renderOnTop(std::shared_ptr<sf::RenderWindow> target)
{

    for (const auto& chunk : chunks_)
    {
        if (getViewRect().intersects(chunk.second->getRectangle()))
        {
            chunk.second->renderOnTop(target);
        }
    }
}


/**
 * @brief Function that loads the textures needed by the tiles
 */
void Map::loadTextures()
{
    sf::Texture texture;

    // Player texture
    if (!texture.loadFromFile("resources/game/map/sprite_sheet.png"))
        throw("Error : Could not load player's sprite sheet texture");

    textures_["MAP"] = std::make_shared<sf::Texture>(texture);
}

/**
 * @brief Function that updates the chunks
 */
void Map::updateChunks()
{
    generateChunks();
    removeChunks();
}

/**
 * @brief Function that returns a tile at a certain position
 * @param position          Position of the tile
 * @return                  Tile
 */
const std::string& Map::getTile(const Vector& globalPosition) const
{
    Vector position(
        static_cast<int>(globalPosition.getX()) % static_cast<int>(chunkSize_.getX() * tileSize_.getX()),
        static_cast<int>(globalPosition.getY()) % static_cast<int>(chunkSize_.getY() * tileSize_.getY())
    );

    return chunks_.at(position)->getTile(globalPosition);
}

/**
 * @brief Function that returns teh view's rectangle
 * @return view's rectangle
 */
sf::FloatRect Map::getViewRect() const
{
    return sf::FloatRect(
        view_.getCenter().x - view_.getSize().x / 2.0f,
        view_.getCenter().y - view_.getSize().y / 2.0f,
        view_.getSize().x,
        view_.getSize().y
    );
}

/**
 * @brief Function that collides the player with the map
 */
void Map::collide()
{
    const HitboxComponent& hitbox = player_.getHitbox();
    std::unordered_set<const Chunk*> chunks = chunksColliding(hitbox);

    for (const Chunk* chunk : chunks)
    {
        std::vector<Vector> offsets = chunk->collide(hitbox);
        
        for (const Vector& offset : offsets) 
        {
            player_.applyForce(offset);
        }

    }
}

/**
 * @brief Function that returns a map of every chunk colliding with a rectangle
 * @param hibox             Rectangle
 * Could be improved by only calling this function when the player moves
 */
std::unordered_set<const Chunk*> Map::chunksColliding(const HitboxComponent& hitbox)
{
    // Getting the corners of the hitbox
    std::array<Vector, 4> positions = Vector::getCorners(hitbox.getHitbox());

    // Getting the position of the chunk
    for (Vector& v : positions)
    {
        v = Vector(
            (chunkSize_.getX() * tileSize_.getX()) * static_cast<float>(floor(v.getX() / (chunkSize_.getX() * tileSize_.getX()))),
            (chunkSize_.getY() * tileSize_.getY()) * static_cast<float>(floor(v.getY() / (chunkSize_.getY() * tileSize_.getY())))
        );
    }


    // Getting the chunks colliding
    std::unordered_set<const Chunk*> chunksColliding;
    std::for_each(positions.begin(), positions.end(), [&] (const Vector& pos) {
        const auto& chunk = chunks_.find(pos);

        if (chunk != chunks_.end() &&
            hitbox.isIntersecting(chunk->second->getRectangle()))
            {
                chunksColliding.emplace(chunk->second.get());
            }
    });

    return chunksColliding;
}


/**
 * @brief Function that generates the chunks around the player
 * @param playerPosition    Position of the player
 */
void Map::generateChunks()
{
    std::vector<Vector> currentPositions;
    for (const auto& i : chunks_)
        currentPositions.push_back(i.first);

    for (const auto& position : currentPositions)
    {
        std::vector<Vector> positions;
        
        // Left
        positions.push_back(position - Vector(chunkSize_.getX() * tileSize_.getX(), 0.0f));
        
        // Right
        positions.push_back(position + Vector(chunkSize_.getX() * tileSize_.getX(), 0.0f));
        
        // Top
        positions.push_back(position - Vector(0.0f, chunkSize_.getY() * tileSize_.getY()));
        
        // Bottom
        positions.push_back(position + Vector(0.0f, chunkSize_.getY() * tileSize_.getY()));

        for (const Vector& pos : positions)
        {
            if ((player_.getPosition() - pos).norm() < CHUNK_RADIUS * chunkSize_.norm() * tileSize_.norm() &&
                !isChunkGenerated(pos))
            {
                // Chunk must be added
                generateChunk(pos);
            }
        }

    }

}


/**
 * @brief Function that generates a chunk at a certain position using perlin noise
 * @param position      Position where to generate chunk
 */
void Map::generateChunk(const Vector& position)
{
    chunks_.emplace(position, std::make_unique<Chunk>(textures_["MAP"], terrainGenerator_, position, chunkSize_, tileSize_));
}

/**
 * @brief Function that returns whether a chunk was already generated at a certain position
 * @param position      Position to look for chunk
 * @return              Chunk already generated or not
 */
bool Map::isChunkGenerated(const Vector& position) const
{
    return chunks_.find(position) != chunks_.end();
}

/**
 * @brief Function that removes the chunks too far away
 * @param playerPosition    Position of the player
 */
void Map::removeChunks()
{
    std::vector<Vector> deletedChunks;
    for (const auto& chunk : chunks_)
    {
        if ((player_.getPosition() - chunk.first).norm() > CHUNK_RADIUS * chunkSize_.norm() * tileSize_.norm())
        {
            deletedChunks.push_back(chunk.first);
        }
    }

    for (const auto& c : deletedChunks)
        chunks_.erase(c);
}

