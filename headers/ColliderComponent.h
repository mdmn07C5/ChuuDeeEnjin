#ifndef _COLLIDERCOMPONENT_H_
#define _COLLIDERCOMPONENT_H_

#include <string>
#include "SDL.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"

class ColliderComponent : public Component
{
public:
    SDL_Rect collider_;
    std::string tag_;

    TransformComponent* transform;

    ColliderComponent(std::string tag) 
        : tag_{tag}
    {

    }

    void Init() override
    {
        if (!entity->hasComponent<TransformComponent>())
        {
            entity->AddComponent<TransformComponent>();
        }   
        transform = &entity->GetComponent<TransformComponent>();

        Game::colliders.push_back(this);
    }

    void Update() override
    {
        collider_.x = static_cast<int>(transform->position_.x_);
        collider_.y = static_cast<int>(transform->position_.y_);
        collider_.w = transform->width_ * transform->scale_;
        collider_.h = transform->height_ * transform->scale_;
    }
};

#endif