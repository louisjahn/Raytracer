//
// Created by Louis Jahn on 9/18/20.
//

#ifndef RAYTRACER___INTRO_DIELECTRIC_H
#define RAYTRACER___INTRO_DIELECTRIC_H

#include "material.h"

class dielectric: public material
{
public:
    explicit dielectric(double ri): ref_idx(ri) {}
    dielectric(const dielectric &copy): ref_idx(copy.ref_idx) {}

    virtual ~dielectric() = default;

    dielectric &operator=(const dielectric &copy);

    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
    ) const;
public:
    double ref_idx;
};

#endif //RAYTRACER___INTRO_DIELECTRIC_H
