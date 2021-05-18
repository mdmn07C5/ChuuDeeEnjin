#ifndef _SPRITECOMPONENT_H_
#define _SPRITECOMPONENT_H_

#include "Components.h"
#include "SDL.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Animation.h"
#include "Game.h"
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform_;
    SDL_Texture *texture_;
    SDL_Rect srcRect_, destRect_;

    bool animated_{false};
    int frames_{0};
    int delay_{100};

public:

    int animIndex_{0};
    std::map<const char*, Animation> animations_;
    SDL_RendererFlip spriteFlip_ = SDL_FLIP_NONE;


    SpriteComponent() = default;
    SpriteComponent(const char *path)
    {
        SetTexture(path);
    }

    SpriteComponent(const char *path, bool animated) : animated_{animated}
    {
        SetTexture(path);
        Animation idle = Animation(3, 3, 100);
        animations_.emplace("idle", idle);
        Animation walk = Animation(1, 3, 100);
        animations_.emplace("walk", walk);

        Play("idle");
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture_);
    }

    void SetTexture(const char *path)
    {
        texture_ = TextureManager::LoadTexture(path);
    }

    void Init() override
    {
        transform_ = &entity->GetComponent<TransformComponent>();

        srcRect_.x = srcRect_.y = 0;
        srcRect_.w = srcRect_.h = transform_->height_;
        destRect_.w = destRect_.h = transform_->height_ * transform_->scale_;
    }

    void Update() override
    {
        if (animated_)
        {
            srcRect_.x = srcRect_.w * static_cast<int>((SDL_GetTicks()/delay_) % frames_ );
        }

        srcRect_.y = animIndex_ * transform_->height_;

        destRect_.x = static_cast<int>(transform_->position_.x_) - Game::camera.x;
        destRect_.y = static_cast<int>(transform_->position_.y_) - Game::camera.y;

        destRect_.w = transform_->width_ * transform_->scale_;
        destRect_.h = transform_->height_ * transform_->scale_;
    }

    void Draw() override
    {
        TextureManager::Draw(texture_, srcRect_, destRect_, spriteFlip_);
    }

    void Play(const char* animName)
    {
        frames_ = animations_[animName].frames_;
        animIndex_ = animations_[animName].index_;
        delay_ = animations_[animName].delay_;
    }
};

#endif