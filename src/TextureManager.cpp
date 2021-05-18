#include "TextureManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Game.h"

#include "cstdio"
SDL_Texture* TextureManager::LoadTexture(const char* filePath)
{
    SDL_Surface* tempSurface = IMG_Load(filePath);
    // if (!tempSurface)
    // {
    //     printf("TEMP SURFACE IS KILL: %s", SDL_GetError());
    // }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer_, tempSurface);
    // if (!tex)
    // {
    //     printf("TEXTURE IS KILL: %s", SDL_GetError());
    // }
    SDL_FreeSurface(tempSurface);
    
    return tex;
}

void TextureManager::Draw(SDL_Texture*texture, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer_, texture, &src, &dest, 0.0, NULL, flip);
}