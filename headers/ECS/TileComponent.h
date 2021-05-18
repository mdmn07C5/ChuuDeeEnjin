#ifndef _TILECOMPONENT_H_
#define _TILECOMPONENT_H_

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include "Globals.h"
#include <string>

class TileComponent : public Component
{
public:
    SDL_Texture *texture_;
    SDL_Rect srcRect_, destRect_;
    Vector2D position_;

    TileComponent() = default;

    TileComponent(int srcX, int srcY, int xPos, int yPos, const char* path) 
    {
        texture_ = TextureManager::LoadTexture(path);

        position_.x_ = xPos;
        position_.y_ = yPos;
        
        srcRect_.x = srcX;
        srcRect_.y = srcY;
        srcRect_.w = srcRect_.h = globals::PIXEL_SIZE;

        destRect_.x = xPos;
        destRect_.y = yPos;
        destRect_.w = destRect_.h = globals::PIXEL_SIZE * globals::SPRITE_SCALE;
    }

    void Update() override
    {
        destRect_.x = position_.x_ - Game::camera.x;
        destRect_.y = position_.y_ - Game::camera.y;
    }

    void Draw() override
    {
        TextureManager::Draw(texture_, srcRect_, destRect_, SDL_FLIP_NONE);
    }

    ~TileComponent()
    {
        SDL_DestroyTexture(texture_);
    }

};

#endif