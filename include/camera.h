//
// Created by Louis Jahn on 9/11/20.
//

#ifndef RAYTRACER___INTRO_CAMERA_H
#define RAYTRACER___INTRO_CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera
{
public:
    camera(const point3& lookfrom,
           const point3& lookat,
           const vec3&   vup,
           double        vfov, // vertical field-of-view in degrees
           double        aspect_ratio,
           double        aperture,
           double        focus_dist,
           double        _time0,
           double        _time1);

    camera(const camera &copy);
    camera &operator=(const camera &copy);

    ray get_ray(double s, double t) const;
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
    double time0, time1;
};


#endif //RAYTRACER___INTRO_CAMERA_H
