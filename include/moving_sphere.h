//
// Created by Louis Jahn on 22/10/2021.
//

#ifndef RAYTRACER___INTRO_MOVING_SPHERE_H
#define RAYTRACER___INTRO_MOVING_SPHERE_H

#include "hittable.h"
#include "material.h"

class moving_sphere: public hittable {
public:
    moving_sphere(): radius(1), time0(0), time1(1), center0(0, 0, 0), center1(0, 0, 0) {};

    moving_sphere(const point3& cen0, const point3& cen1, double _time0, double _time1, double r, material *mat)
    : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat(mat) {};

    moving_sphere(const moving_sphere& copy)
    : center0(copy.center0), center1(copy.center1), time0(copy.time0), time1(copy.time1), radius(copy.radius), mat(copy.mat) {};

    ~moving_sphere() override;

    moving_sphere& operator=(const moving_sphere& copy);

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    point3 center(double time) const;
public:
    double radius;
    double time0, time1;
    point3 center0, center1;
    material* mat = nullptr;
private:
    bool isCopy = false;
};

#endif //RAYTRACER___INTRO_MOVING_SPHERE_H
