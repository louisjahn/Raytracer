//
// Created by Louis Jahn on 9/11/20.
//

#include "camera.h"
#include "utils.h"

camera::camera(const point3 &lookfrom,
               const point3 &lookat,
               const vec3   &vup,
               double       vfov, // vertical field-of-view in degrees
               double       aspect_ratio,
               double       aperture,
               double       focus_dist)
{
    double theta = degrees_to_radians(vfov);
    double h = tan(theta / 2);
    double viewport_height = 2.0 * h;
    double viewport_width = aspect_ratio * viewport_height;

    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * w;

    lens_radius = aperture / 2;
}

camera::camera(const camera &copy)
{
    origin = copy.origin;
    lower_left_corner = copy.lower_left_corner;
    horizontal = copy.horizontal;
    vertical = copy.vertical;
    u = copy.u;
    v = copy.v;
    w = copy.w;
    lens_radius = copy.lens_radius;
}

camera &camera::operator=(const camera &copy)
{
    if (this != &copy)
    {
        origin = copy.origin;
        lower_left_corner = copy.lower_left_corner;
        horizontal = copy.horizontal;
        vertical = copy.vertical;
        u = copy.u;
        v = copy.v;
        w = copy.w;
        lens_radius = copy.lens_radius;
    }
    return *this;
}

ray camera::get_ray(double s, double t) const
{
    vec3 rd = lens_radius * random_in_unit_disk();
    vec3 offset = u * rd.x() + v * rd.y();
    return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}