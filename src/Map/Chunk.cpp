#include "../headers.h"
#include "Chunk.h"

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
    //generateSmoothTextures();
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
void Chunk::render(std::shared_ptr<sf::RenderTarget> target)
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
void Chunk::renderOnTop(std::shared_ptr<sf::RenderTarget> target)
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
std::vector<Vector> Chunk::collide(const HitboxComponent& hitbox)
{
    // Collisions with solid blocks
    std::unordered_map<Vector, sf::FloatRect, VectorHasher> blocks = blocksColliding(hitbox);
    std::vector<Vector> offsets;
    for (const auto& block : blocks)
    {
        offsets.push_back(CollisionHandler::collide(hitbox, block.second));
    }

    // Collisions with tiles
    std::unordered_map<Vector, std::string, VectorHasher> tiles = naturalElementsColliding(hitbox);
    for (const auto& tile : tiles)
    {
        if (tile.second == "bush")
        {
            nature_.erase(tile.first);
        }
    }

    return offsets;
}

/**
 * @brief Function that returns the neighbours of a tile (order : b-t-r-l)
 * @param position      Position of the tile
 * @return              Array containing the neighbouring tiles
 */
std::array<Vector, 4> Chunk::getNeighbours(const Vector& position) const
{
    Vector bottom = position + Vector(0.0f, tileSize_.getY());
    Vector top = position - Vector(0.0f, tileSize_.getY());
    Vector right = position + Vector(tileSize_.getX(), 0.0f);
    Vector left = position - Vector(tileSize_.getX(), 0.0f);

    return { bottom, top, right, left };
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
const std::string& Chunk::getTile(const Vector& globalPosition) const
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
 * @brief Function that returns the size of a chunk
 * @return Size of a chunk
 */
const Vector& Chunk::getSize() const
{
    return size_;
}

/**
 * @brief Function that returns the number of tiles in a chunk
 * @return Number of tiles in a chunk
 */
const Vector& Chunk::getTileSize() const
{
    return tileSize_;
}

/**
 * @brief Function that returns every tiles colliding with a hitbox
 * @param hitbox        Hitbox
 * @return              Tiles colliding
 */
std::unordered_map<Vector, sf::FloatRect, VectorHasher> Chunk::blocksColliding(const HitboxComponent& hitbox) const
{   
    std::unordered_map<Vector, sf::FloatRect, VectorHasher> tilesColliding;
    for (const auto& tile : blocks_)
    {
        if (hitbox.isIntersecting(tile.second))
        {
            tilesColliding.emplace(tile.first, tile.second);
        }
    }

    return tilesColliding;
}

/**
 * @brief Function that returns every tiles colliding with a hitbox
 * @param hitbox        Hitbox
 * @return              Tiles colliding
 */
std::unordered_map<Vector, std::string, VectorHasher> Chunk::naturalElementsColliding(const HitboxComponent& hitbox) const
{   
    std::unordered_map<Vector, std::string, VectorHasher> tilesColliding;
    for (const auto& tile : nature_)
    {
        if (hitbox.isIntersecting(sf::FloatRect(tile.first.getAsVector2f(), tileSize_.getAsVector2f())))
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
            
            Vector terrainPosition = Vector(pos.getX() / (tileSize_.getX() * 64.0f), pos.getY() / (tileSize_.getY() * 64.0f));

            float value = terrainGenerator_.mapValue(terrainPosition);

            addTile(pos, value);   

            if (value >= TerrainGenerator::GRASS_HEIGHT)
                generateNaturalElements(pos, terrainGenerator_.generateNaturalElement(pos));
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

    if (height <= TerrainGenerator::WATER_HEIGHT)
    {
        tiles_.emplace(position, "water");
        blocks_.emplace(position, sf::FloatRect(position.getAsVector2f(), tileSize_.getAsVector2f()));
    }
    else if (height <= TerrainGenerator::SAND_HEIGHT)
    {
        tiles_.emplace(position, "sand");
    }
    else if (height <= TerrainGenerator::GRASS_HEIGHT)
    {
        // Normal grass
        tiles_.emplace(position, "grass_" + std::to_string(terrainGenerator_.generateGrass(position)));
    }
    else 
        tiles_.emplace(position, "grass_" + std::to_string(terrainGenerator_.generateGrass(position)));
}

/**
 * @brief Funciont that generates trees at a depending on a certain height
 * @param position      Position of the tree
 * @param height         Height used to determine if a tree can be added or not
 */
void Chunk::generateNaturalElements(const Vector& position, int type)
{
    switch (type) 
    {
        case 1:
            nature_.try_emplace(position, "bush");
            break;
        
        case 2:
            nature_.emplace(position, "tree");
            blocks_.emplace(position, sf::FloatRect((position + Vector(0.0f, tileSize_.getY())).getAsVector2f(), tileSize_.getAsVector2f()));
            break;

        case 3:
            nature_.emplace(position, "big_tree");
            blocks_.emplace(position, sf::FloatRect((position + Vector(0.5f * tileSize_.getX(), 2.0f * tileSize_.getY())).getAsVector2f(), tileSize_.getAsVector2f()));
            break;

        default:
            break;
    }

}

/**
 * @brief Function that generates smooth transitions between tiles
 */
void Chunk::generateSmoothTextures() 
{
    for (auto& tile : tiles_)
    {
        if (tile.second == "sand")
        {
            std::array<Vector, 4> neighbours = getNeighbours(tile.first);
            std::array<std::string, 4> tiles;

            std::transform(neighbours.begin(), neighbours.end(), tiles.begin(), [&] (const Vector& v) {
                const auto& tile = tiles_.find(v);
                if (tile != tiles_.end())
                {
                    return tile->second; 
                }
                return std::string("INVALID");
            });

            std::string newTile = "sand";

            if (tiles[0] == "water")
            {
                // Bottom tile
                newTile += "_down";
            }
            else if (tiles[1] == "water")
            {
                // Top tile
                newTile += "_up";
            }

            if (tiles[2] == "water")
            {
                // Right tile
                newTile += "_right";
            }
            else if (tiles[3] == "water")
            {
                // Left tile
                newTile += "_left";
            }

            tiles_[tile.first] = newTile;
        }
    }

}
