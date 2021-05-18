#include "Collision.h"
#include "ColliderComponent.h"
#include "SDL.h"
#include "iostream"

bool Collision::AABB(const SDL_Rect &rectA, const SDL_Rect &rectB)
{
    return (rectA.x + rectA.w >= rectB.x &&
            rectB.x + rectB.w >= rectA.x &&
            rectA.y + rectA.h >= rectB.y &&
            rectB.y + rectB.h >= rectA.y);
}

bool Collision::AABB(const ColliderComponent &colA, const ColliderComponent &colB)
{
    if(AABB(colA.collider_, colB.collider_))
    {
        std::cout << "Collision between " << colA.tag_ << " and " << colB.tag_ << std::endl;
        return true;
    }
    return false;
}