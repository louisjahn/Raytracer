//
// Created by Louis Jahn on 8/28/20.
//

#ifndef RAYTRACER___INTRO_RAY_H
#define RAYTRACER___INTRO_RAY_H

#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction) {}

    ~ray() = default;

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }

    point3 at(const double t) const { return orig + t * dir; }

public:
    point3 orig;
    vec3 dir;
};

#endif //RAYTRACER___INTRO_RAY_H
