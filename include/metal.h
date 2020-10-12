//
// Created by Louis Jahn on 9/17/20.
//

#ifndef RAYTRACER___INTRO_METAL_H
#define RAYTRACER___INTRO_METAL_H

#include "material.h"

class metal: public material
{
public:
    metal(const color &a, double f): albedo(a), fuzzy(f > 1 ? 1 : f) {}
    metal(const metal &copy): albedo(copy.albedo), fuzzy(copy.fuzzy) {}

    virtual ~metal() = default;

    metal &operator=(const metal &copy);

    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const;

public:
    color albedo;
    double fuzzy;
};

#endif //RAYTRACER___INTRO_METAL_H
