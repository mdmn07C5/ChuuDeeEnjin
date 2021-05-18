#ifndef _COLLISION_H_
#define _COLLISION_H_

// #include "SDL.h"
// fwd decl
class ColliderComponent;
struct SDL_Rect;

class Collision
{
public:
    // static because we don't want to have to intantiate a collision each time
    // Axis-Aligned Bounding-Box
    static bool AABB(const SDL_Rect &rectA, const SDL_Rect &rectB);
    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);
};

#endif