#ifndef _TRANSFORMCOMPONENT_H_
#define _TRANSFORMCOMPONENT_H_

#include "ECS.h"
#include "Vector2D.h"
#include "Globals.h"

struct TransformComponent : public Component
{
public:
    Vector2D position_;
    Vector2D velocity_;
    float speed_{3};

    int height_{static_cast<int>(globals::PIXEL_SIZE)};
    int width_{static_cast<int>(globals::PIXEL_SIZE)};
    int scale_{static_cast<int>(globals::SPRITE_SCALE)};

    TransformComponent()
        : TransformComponent(0, 0)
    {
        // TransformComponent(0, 0);
        // position_.x_{0};
        // position_.y_{0};
        // TransformComponent(0, 0);
    }

    TransformComponent(int scale) : position_{globals::SCREEN_WIDTH/2, globals::SCREEN_HEIGHT/2}, scale_{scale}
    {
        
    }

    TransformComponent(float x, float y) : position_{x, y}
    {
        scale_ = globals::SPRITE_SCALE;
    }

    TransformComponent(float x, float y, int h, int w, int scale)
        : position_{x, y}, height_{h}, width_{w}, scale_{scale}
    {
        
    }

    void ResetPosition()
    {
        position_.Zero();
    }

    void Init() override
    {
        velocity_.Zero();
    }

    void Update() override
    {
        // for moving shit around the map
        position_.x_ += velocity_.x_ * speed_;
        position_.y_ += velocity_.y_ * speed_;

        
    }
};

#endif