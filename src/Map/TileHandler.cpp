#include "../../include/headers.h"
#include "../../include/Map/TileHandler.h"

const float TileHandler::DEFAULT_SIZE = 32.0f;
const float TileHandler::TEXTURE_SIZE = 128.0f;
float TileHandler::SCALE_FACTOR_TEXTURE_SPRITE = TileHandler::TEXTURE_SIZE / TileHandler::DEFAULT_SIZE;
const std::size_t TileHandler::NUMBER_OF_TEXTURES = 3;

std::unordered_map<std::string, Vector> TileHandler::coordinates_;

/**
 * @brief Function that returns the singleton
 * @return              Tile handler
 */
TileHandler& TileHandler::getInstance()
{
    static TileHandler instance;
    return instance;
}

/**
 * @brief Destructor
 */
TileHandler::~TileHandler()
{
    
}

/**
 * @brief Constructor
 */
TileHandler::TileHandler()
{
   loadCoordinates();
}

/**
 * @brief Function that loads the coordinates of specific tiles into the map
 */
void TileHandler::loadCoordinates()
{
    std::ifstream file("config/block_id.ini");
    std::string id;
    int x, y;
    
    while (file >> id >> x >> y)
    {
        TileHandler::coordinates_.emplace(id.data(), Vector(x, y));
    }

}

/**
 * @brief Function that returns a sprite of a certain block
 * @param blockID       ID of the block @see block_id.ini
 * @param texture       Pointer to texture
 * @param tileSize      Tile size
 */
sf::Sprite TileHandler::I_getSpriteFromChar(const std::string& blockID, std::shared_ptr<sf::Texture> texture, const Vector& tileSize) const
{
    sf::IntRect textureRect;
    sf::Sprite sprite;
    Vector textureSize = getTextureSize(blockID);

    sprite.setScale(1.0f / TileHandler::SCALE_FACTOR_TEXTURE_SPRITE, 1.0f / TileHandler::SCALE_FACTOR_TEXTURE_SPRITE);
    sprite.setTexture(*texture);
    try {
        Vector coordinate = getTextureCoordinates(blockID);
        textureRect = sf::IntRect(
            coordinate.getAsVector2i(),
            Vector(textureSize.getX() * tileSize.getX() * TileHandler::SCALE_FACTOR_TEXTURE_SPRITE,
                    textureSize.getY() * tileSize.getY() * TileHandler::SCALE_FACTOR_TEXTURE_SPRITE).getAsVector2i()
        );
    } catch (TileNotFound& e)
    {
        std::cout << e.what() << "\n";
    }

    sprite.setTextureRect(textureRect);

    return sprite;
}

/**
 * @brief Function that returns whether a certain block is solid or not
 * @param blockID       Block's id
 */
bool TileHandler::I_isBlockSolid(const std::string& blockID) const
{
    return blockID == "WATER" || blockID == "big_tree";
}

/**
 * @brief Function that returns the texture size based on the id
 * @param blockID       Block's id
 */
Vector TileHandler::getTextureSize(const std::string& blockID) const
{
    if (blockID == "big_tree")
    {
        return Vector(1, 2);    
    }

    return Vector(1, 1);
}

/**
 * @brief Function that returns the position of the texture in the tile texture sheet based on the ID
 */
Vector TileHandler::getTextureCoordinates(const std::string& blockID) const
{
    if (TileHandler::coordinates_.find(blockID) == coordinates_.end())
        throw TileNotFound("Texture not found");

    return TileHandler::coordinates_.at(blockID);
}
