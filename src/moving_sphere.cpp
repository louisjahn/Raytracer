//
// Created by Louis Jahn on 22/10/2021.
//

#include "moving_sphere.h"


moving_sphere &moving_sphere::operator=(const moving_sphere &copy)
{
    if (this != &copy)
    {
        this->center0 = copy.center0;
        this->center1 = copy.center1;
        this->radius = copy.radius;
    }
    return *this;
}

bool moving_sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center(r.time());
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
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
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
            vec3 outward_normal = (rec.p - center(r.time())) / radius;
            rec.set_face_normal(r, outward_normal);
            // rec.normal = unit_vector(r.at(rec.t) - vec3(0, 0, -1));
            rec.mat = mat;
            return true;
        }
    }
    return false;
}

moving_sphere::~moving_sphere()
{
    delete mat;
}

point3 moving_sphere::center(double time) const {
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}
