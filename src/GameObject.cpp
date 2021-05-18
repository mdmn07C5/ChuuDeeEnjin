#include "GameObject.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Game.h"
#include <stdio.h>

GameObject::GameObject(const char *textureSheet, int x, int y) : objectTexture_{TextureManager::LoadTexture(textureSheet)}, xPos_{x}, yPos_{y}
{
    if (!objectTexture_)
    {
        printf("Game Object Texture creation failed: %s", IMG_GetError());
    }
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
    /* temp */
    // xPos_ = 0;
    // yPos_ = 0;

    srcRect_.h = globals::PIXEL_SIZE;
    srcRect_.w = globals::PIXEL_SIZE;
    srcRect_.x = 0;
    srcRect_.y = 0;

    destRect_.x = xPos_;
    destRect_.y = xPos_;
    destRect_.h = srcRect_.h * globals::SPRITE_SCALE;
    destRect_.w = srcRect_.w * globals::SPRITE_SCALE;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer_, objectTexture_, &srcRect_, &destRect_);
}