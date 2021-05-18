#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

/**
 * TextureManager class
 * Handles loading images
 */


// #include "SDL_render.h"

// // forward declare
// struct SDL_Texture;
// struct SDL_Renderer;
// struct SDL_Rect;
// because I can't forward declare enums
#include "SDL.h"


class TextureManager {

public:
    /**
     * Loads an image into a temporary SDL_Surface to create a texture from it
     * @param filePath the directory where the image is located, if executable is not in root directory, append the path with "../"
     * @return pointer to the SDL_Texture created from the image
     */
    static SDL_Texture* LoadTexture(const char* filePath);
    static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

#endif