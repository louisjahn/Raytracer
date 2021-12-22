//
// Created by Louis Jahn on 8/28/20.
//

#ifndef RAYTRACER___INTRO_RAY_H
#define RAYTRACER___INTRO_RAY_H

#include "vec3.h"

class ray {
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction, double time = 0.0)
        : orig(origin), dir(direction), tm(time) {}

    ~ray() = default;

    point3 origin() const  { return orig; }
    vec3 direction() const { return dir; }
    double time() const { return tm; }

    point3 at(const double t) const { return orig + t * dir; }

public:
    point3 orig{0, 0, 0};
    vec3 dir{0, 0, 0};
    double tm = 0.0;
};

#endif //RAYTRACER___INTRO_RAY_H
