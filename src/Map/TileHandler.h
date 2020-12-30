#ifndef TILE_HANDLER_H
#define TILE_HANDLER_H

#include "../Drawable.h"
#include "../Exception/TileNotFound.h"

enum Type {
    AIR,
    SOLID
};

// Singleton class
class TileHandler
{
public:

    static const float DEFAULT_SIZE;
    static const float TEXTURE_SIZE;
    static float SCALE_FACTOR_TEXTURE_SPRITE;
    static const std::size_t NUMBER_OF_TEXTURES;

    TileHandler(const TileHandler&) = delete;
    void operator=(const TileHandler&) = delete;

    static sf::Sprite getSpriteFromChar(const std::string& blockID, std::shared_ptr<sf::Texture> texture, const Vector& tileSize = Vector(TileHandler::DEFAULT_SIZE))
    {
        return getInstance().I_getSpriteFromChar(blockID, texture, tileSize);
    }

    static bool isBlockSolid(const std::string& blockID)
    {
        return getInstance().I_isBlockSolid(blockID);
    }

    static TileHandler& getInstance();
    virtual ~TileHandler();

private:

    TileHandler();

    void loadCoordinates();
    sf::Sprite I_getSpriteFromChar(const std::string& blockID, std::shared_ptr<sf::Texture> texture, const Vector& tileSize = Vector(TileHandler::DEFAULT_SIZE)) const;
    bool I_isBlockSolid(const std::string& blockID) const ;
    Vector getTextureSize(const std::string& blockID) const;
    Vector getTextureCoordinates(const std::string& blockID) const;

    static std::unordered_map<std::string, Vector> coordinates_;
};

#endif