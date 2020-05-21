#include "../../include/headers.h"
#include "../../include/Map/Chunk.h"

const float Chunk::DEFAULT_SIZE = 16.0f;

/**
 * @brief Constructor
 * @param perlinNoise           Perlin noise object for tile generation
 * @param position              Chunk's position
 * @param size                  Chunk's size (in number of tiles)
 * @param tileSize              Size of each tile
 */
Chunk::Chunk(std::shared_ptr<sf::Texture> textureSheet, TerrainGenerator& terrainGenerator, const Vector& position, const Vector& size, const Vector& tileSize)
    :   terrainGenerator_(terrainGenerator)
    ,   position_(position)
    ,   size_(size)
    ,   tileSize_(tileSize)
    ,   textureSheet_(textureSheet)
{
    initTerrain();
}

/**
 * @brief Destructor
 */
Chunk::~Chunk()
{
    
}

/**
 * @brief Function that updates the tile
 * @param dt            Time since last frame
 */
void Chunk::update(const float& dt)
{
    
}

/**
 * @brief Function that renders the tile
 * @param target        Where to draw the tile
 */
void Chunk::render(std::shared_ptr<sf::RenderWindow> target)
{

    // Rendering tiles
    for (const auto& tile : tiles_)
    {
        sf::Sprite s = TileHandler::getSpriteFromChar(tile.second, textureSheet_);
        s.setPosition(tile.first.getAsVector2f());
        target->draw(s);
    }

}

/**
 * @brief Function that renders the tile on top
 * @param target        Where to draw the tile
 */
void Chunk::renderOnTop(std::shared_ptr<sf::RenderWindow> target)
{
    // Rendering tiles
    for (const auto& tile : nature_)
    {
        sf::Sprite s = TileHandler::getSpriteFromChar(tile.second, textureSheet_);
        s.setPosition(tile.first.getAsVector2f());
        target->draw(s);
    }

}

/**
 * @brief Function that collides a hitbox with the chunk
 * @param hitbox        Hitbox
 * @return              Push that must be applied to the hitbox
 */
std::vector<Vector> Chunk::collide(const HitboxComponent& hitbox) const
{
    std::unordered_map<Vector, std::string, VectorHasher> tiles = tilesColliding(hitbox);
    std::vector<Vector> offsets;
    for (const auto& tile : tiles)
    {
        if (TileHandler::isBlockSolid(tile.second))
        {
            offsets.push_back(CollisionHandler::collide(hitbox, sf::FloatRect(tile.first.getAsVector2f(), tileSize_.getAsVector2f())));
        }
    }

    return offsets;
}

/**
 * brief Function that returns the global position of a certain tile
 * @param x             X coordinate in the chunk (in tiles)
 * @param y             Y coordinate in the chunk (in tiles)
 */
Vector Chunk::getPositionOfTile(std::size_t x, std::size_t y) const
{
    float i = position_.getX() + static_cast<float>(x) * tileSize_.getX();
    float j = position_.getY() + static_cast<float>(y) * tileSize_.getY();
    return Vector(i, j);
}

/**
 * @brief Function that returns the tile at a certain position
 * @param globalPosition    Position of the tile
 * @return                  Tile
 */
std::string Chunk::getTile(const Vector& globalPosition) const
{
    Vector localPosition = globalPosition - position_;
    return tiles_.find(localPosition)->second;
}

/**
 * @brief Function that returns the position of the chunk
 * @return              Chunk's position
 */
Vector Chunk::getPosition() const
{
    return position_;
}

/**
 * @brief Function that returns a rectangle containing the chunk
 * @return Rectangle
 */
sf::FloatRect Chunk::getRectangle() const
{
    return sf::FloatRect(
        position_.getAsVector2f(),
        sf::Vector2f(size_.getX() * tileSize_.getX(), size_.getY() * tileSize_.getY()));
}

/**
 * @brief Function that returns every tiles colliding with a hitbox if the tiles are solid
 * @param hitbox        Hitbox
 * @return              Tiles colliding
 */
std::unordered_map<Vector, std::string, VectorHasher> Chunk::tilesColliding(const HitboxComponent& hitbox) const
{   
    std::unordered_map<Vector, std::string, VectorHasher> tilesColliding;
    for (const auto& tile : tiles_)
    {
        sf::FloatRect tileRect(tile.first.getAsVector2f(), tileSize_.getAsVector2f());
        if (hitbox.isIntersecting(tileRect))
        {
            tilesColliding.emplace(tile.first, tile.second);
        }
    }

    return tilesColliding;
}

/**
 * @brief Function that generates the chunk with perlin noise
 */
void Chunk::initTerrain()
{
    tiles_.reserve(size_.getX() * size_.getY());

    for (std::size_t i = 0; static_cast<float>(i) < size_.getX(); ++i)
    {
        for (std::size_t j = 0; static_cast<float>(j) < size_.getY(); ++j)
        {
            Vector pos = getPositionOfTile(i, j);

            float value = terrainGenerator_.getMapGenerator().noise(
                pos.getX() / (tileSize_.getX() * 50.0f), 
                pos.getY() / (tileSize_.getY() * 50.0f), 
                0);
            
            addTile(pos, value);
            generateTrees(pos, value);
        }
    }
}

/**
 * @brief Function that adds a tile to the chunk at a certain position
 * @param position      Position of the tile
 * @param height        Height used to determine the tile's type
 */
void Chunk::addTile(const Vector& position, const float& height)
{

    if (height <= -0.1f)
        tiles_.emplace(position, "WATER");
    else if (height <= 0.05f)
        tiles_.emplace(position, "sand");
    else if (height <= 1.0f)
        tiles_.emplace(position, "grass");
    else 
        tiles_.emplace(position, "grass");
}

/**
 * @brief Funciont that generates trees at a depending on a certain height
 * @param position      Position of the tree
 * @param height         Height used to determine if a tree can be added or not
 */
void Chunk::generateTrees(const Vector& position, const float& height)
{
    if (height > 0.2f && static_cast<int>(height * 20.0f) % 2 == 0)
    {
        // Generate the tree
        Vector bottomPos = position + Vector(0.0f, tileSize_.getY());
        Vector topPos = position - Vector(0.0f, tileSize_.getY());

        if (nature_.find(bottomPos) == nature_.end() &&
            nature_.find(topPos) == nature_.end())
        {
            nature_.emplace(position, "big_tree");
        }
    }
}


