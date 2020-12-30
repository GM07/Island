#ifndef TILE_NOT_FOUND_H
#define TILE_NOT_FOUND_H


class TileNotFound
    :   public std::exception
{
public:
    TileNotFound(const std::string& message);
    virtual ~TileNotFound();

    virtual const char* what() const noexcept;

private:
    std::string message_;

};


#endif