#ifndef BALLJUMP_COLLISION_H
#define BALLJUMP_COLLISION_H

#include "SDL.h"

class ColliderComponent;

class Collision {
public:
    static bool AABB(const SDL_Rect &recA, const SDL_Rect &recB);

    static bool AABB(const ColliderComponent &colA, const ColliderComponent &colB);


};


#endif //BALLJUMP_COLLISION_H
