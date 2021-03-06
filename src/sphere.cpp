//
// Created by Louis Jahn on 9/1/20.
//

#include "sphere.h"

sphere &sphere::operator=(const sphere &copy)
{
    if (this != &copy)
    {
        this->center = copy.center;
        this->radius = copy.radius;
    }
    return *this;
}

bool sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant > 0)
    {
        double root = sqrt(discriminant);
        double temp = (-half_b -root) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            // rec.normal = unit_vector(r.at(rec.t) - vec3(0, 0, -1)); // points outside ?
            rec.mat = mat;
            return true;
        }

        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            // rec.normal = unit_vector(r.at(rec.t) - vec3(0, 0, -1));
            rec.mat = mat;
            return true;
        }
    }
    return false;
}

sphere::~sphere()
{
    delete mat;
}
