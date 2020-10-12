//
// Created by Louis Jahn on 9/17/20.
//

#ifndef RAYTRACER___INTRO_LAMBERTIAN_H
#define RAYTRACER___INTRO_LAMBERTIAN_H

#include <ostream>
#include "material.h"

class lambertian : public material
{
public:
    lambertian(): albedo(0, 0, 0) {}
    explicit lambertian(const color &a): albedo(a) {}
    lambertian(const lambertian &copy): albedo(copy.albedo) {}

    virtual ~lambertian() = default;

    lambertian &operator=(const lambertian &copy);

    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const;

public:
    color albedo;
};

#endif //RAYTRACER___INTRO_LAMBERTIAN_H
