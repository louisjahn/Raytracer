//
// Created by Louis Jahn on 9/1/20.
//

#ifndef RAYTRACER___INTRO_HITTABLE_H
#define RAYTRACER___INTRO_HITTABLE_H

#include "ray.h"
#include "material.h"

struct hit_record {
    point3 p;
    vec3 normal;
    material *mat;
    double t;
    bool front_face;

    inline void set_face_normal(const ray &r, const vec3 &outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -1 * outward_normal;
    }
};

class hittable {
    public:
        virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const = 0;

        virtual ~hittable() = default;
};

#endif //RAYTRACER___INTRO_HITTABLE_H
