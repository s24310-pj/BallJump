#ifndef BALLJUMP_COLLISION_H
#define BALLJUMP_COLLISION_H

#include "SDL.h"
#include "Vector2D.h"
#include <cmath>

class ColliderComponent;

class Collision {
public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);
};


#endif //BALLJUMP_COLLISION_H
