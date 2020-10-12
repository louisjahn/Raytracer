//
// Created by Louis Jahn on 9/17/20.
//

#ifndef RAYTRACER___INTRO_MATERIAL_H
#define RAYTRACER___INTRO_MATERIAL_H

#include "utils.h"
#include "ray.h"

struct hit_record;

class material
{
public:
    virtual ~material() = default;
    virtual bool scatter(
            const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered
            ) const = 0;
};

inline double schlick(double cosine, double ref_idx)
{
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

#endif //RAYTRACER___INTRO_MATERIAL_H
