//
// Created by Louis Jahn on 9/18/20.
//

#include "dielectric.h"
#include "hittable.h"

dielectric &dielectric::operator=(const dielectric &copy)
{
    if (this != &copy)
    {
        ref_idx = copy.ref_idx;
    }
    return *this;
}

bool dielectric::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const
{
    attenuation = color(1.0, 1.0, 1.0);
    double etai_over_etat = rec.front_face ? (1.0 / ref_idx) : ref_idx;
    vec3 unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-1 * unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    // Reflect
    if (etai_over_etat * sin_theta > 1.0 )
    {
        vec3 reflected = reflect(unit_direction, rec.normal);
        scattered = ray(rec.p, reflected, r_in.time());
        return true;
    }

    // Sometimes reflects
    double reflect_prob = schlick(cos_theta, etai_over_etat);
    if (random_double() < reflect_prob)
    {
        vec3 reflected = reflect(unit_direction, rec.normal);
        scattered = ray(rec.p, reflected, r_in.time());
        return true;
    }

    // Refract
    vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
    scattered = ray(rec.p, refracted, r_in.time());
    return true;
}
