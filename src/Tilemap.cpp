#include "Tilemap.h"
#include "Globals.h"
#include "Game.h"
#include "SDL.h"
#include "stdio.h"
#include <fstream>

Tilemap::Tilemap() = default;

Tilemap::~Tilemap()
{
}

void Tilemap::LoadTileMap(std::string path, int mapSizeX, int mapSizeY)
{
    char c;
    std::fstream mapFile;
    mapFile.open(path);

    int srcX{0};
    int srcY{0};

    for (int y{0}; y < mapSizeY; y++)
    {
        for (int x{0}; x < mapSizeX; x++)
        {
            // first character will be y val
            mapFile.get(c);
            srcY = atoi(&c) * globals::PIXEL_SIZE;
            // second second will be x val
            mapFile.get(c);
            srcX = atoi(&c) * globals::PIXEL_SIZE;
            Game::AddTile(srcX, srcY, x * globals::PIXEL_SIZE * globals::SPRITE_SCALE, y * globals::PIXEL_SIZE * globals::SPRITE_SCALE);
            // ignore the comma or whitespace char
            mapFile.ignore();
        }
    }

    mapFile.close();
}

// void Tilemap::DrawTileMap()
// {
//     for (size_t row{0}; row < map_.size(); row++)
//     {
//         for (size_t col{0}; col < map_[0].size(); col++)
//         {
//             dest_.y = row * globals::PIXEL_SIZE;
//             dest_.x = col * globals::PIXEL_SIZE;
//             // Temp, just fill map with fucking water
//             TextureManager::Draw(water_, src_, dest_);
//         }
//     }
// }