#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include "SDL.h"
#include "Globals.h"
#include <vector>
#include <string>

// using vec = std::vector;
// using globals::SCREEN_WIDTH/globals::PIXEL_SIZE = width;
// using globals::SCREEN_HEIGHT/globals::PIXEL_SIZE = height;

class Tilemap
{
public:
    Tilemap();
    ~Tilemap();

    static void LoadTileMap(std::string path, int mapSizeX, int mapSizeY);

};

#endif