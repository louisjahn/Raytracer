//
// Created by Louis Jahn on 9/17/20.
//

#include "metal.h"
#include "hittable.h"

metal &metal::operator=(const metal &copy)
{
    if (this != &copy)
    {
        albedo = copy.albedo;
        fuzzy = copy.fuzzy;
    }
    return *this;
}

bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzzy * random_in_unit_sphere(), r_in.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
}
