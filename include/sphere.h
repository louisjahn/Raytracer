//
// Created by Louis Jahn on 9/1/20.
//

#ifndef RAYTRACER___INTRO_SPHERE_H
#define RAYTRACER___INTRO_SPHERE_H

#include "hittable.h"
#include "material.h"

class sphere: public hittable {
    public:
        sphere(): center(0, 0, 0), radius(1) {};
        sphere(const point3 &cen, double r, material *mat) : center(cen), radius(r), mat(mat) {};
        sphere(const sphere &copy) : center(copy.center), radius(copy.radius), mat(copy.mat) {};

        ~sphere() override;

        sphere &operator=(const sphere &copy);

    bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;
    public:
        point3 center;
        double radius;
        material *mat = nullptr;
};

#endif //RAYTRACER___INTRO_SPHERE_H
