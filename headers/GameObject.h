#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "SDL.h"
#include "SDL_image.h"
/**
 * Say something about the game object class boi
 */

class GameObject 
{
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void Update();
    void Render();

private:
    // SDL_Renderer* renderer_;
    SDL_Rect srcRect_, destRect_;
    SDL_Texture* objectTexture_;
    int xPos_;
    int yPos_;
};

#endif