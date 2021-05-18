#ifndef _KEYBOARDCONTROLLER_H_
#define _KEYBOARDCONTROLLER_H_

#include "Game.h"
#include "SDL_events.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"


// TODO: normalize vector so we don't move faster diagonally
class KeyboardController : public Component
{
public:
    TransformComponent *transform_;
    SpriteComponent *sprite_;

    void Init() override
    {
        transform_ = &entity->GetComponent<TransformComponent>();
        sprite_ = &entity->GetComponent<SpriteComponent>();
    }

    void Update() override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform_->velocity_.y_ = -1;
                sprite_->Play("walk");
                break;
            
            case SDLK_a:
                transform_->velocity_.x_ = -1;
                sprite_->Play("walk");
                sprite_->spriteFlip_ = SDL_FLIP_HORIZONTAL;
                break;

            case SDLK_d:
                transform_->velocity_.x_ = 1;
                sprite_->Play("walk");
                break;

            case SDLK_s:
                transform_->velocity_.y_ = 1;
                sprite_->Play("walk");
                break;

            default:
                break;
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            switch (Game::event.key.keysym.sym)
            {
            case SDLK_w:
                transform_->velocity_.y_ = 0;
                sprite_->Play("idle");
                break;
            
            case SDLK_a:
                transform_->velocity_.x_ = 0;
                sprite_->Play("idle");
                sprite_->spriteFlip_ = SDL_FLIP_NONE;
                break;

            case SDLK_d:
                transform_->velocity_.x_ = 0;
                sprite_->Play("idle");
                break;

            case SDLK_s:
                transform_->velocity_.y_ = 0;
                sprite_->Play("idle");
                break;

            case SDLK_ESCAPE:
                Game::isRunning_ = false;
                break;

            default:
                break;
            }
        }
    }
};


#endif