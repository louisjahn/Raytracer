//
// Created by Louis Jahn on 9/17/20.
//

#include "lambertian.h"
#include "hittable.h"
#include "vec3.h"

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    vec3 scatter_direction = rec.normal + random_unit_vector();
    scattered = ray(rec.p, scatter_direction, r_in.time());
    attenuation = albedo;
    return true;
}

lambertian &lambertian::operator=(const lambertian &copy)
{
    if (this != &copy)
    {
        albedo = copy.albedo;
    }
    return *this;
}
