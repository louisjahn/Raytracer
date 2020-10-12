//
// Created by Louis Jahn on 9/1/20.
//

#include "vec3.h"
#include "utils.h"

vec3 &vec3::operator=(const vec3 &cpy)
{
    if (this != &cpy) {
        this->e[0] = cpy.e[0];
        this->e[1] = cpy.e[1];
        this->e[2] = cpy.e[2];
    }
    return *this;
}


vec3 &vec3::operator+=(const vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

vec3 &vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3 &vec3::operator/=(const double t)
{
    return *this *= 1 / t;
}

double vec3::operator[](const std::size_t i)
{
    return this->e[i];
}

double vec3::length() const
{
    return sqrt(length_squared());
}

double vec3::length_squared() const
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

vec3 vec3::random(double min, double max)
{
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

vec3 vec3::random()
{
    return vec3(random_double(), random_double(), random_double());
}

std::ostream &operator<<(std::ostream &out, vec3 &vec)
{
    return out << "x: " << vec[0] << " y: " << vec[1] << " z: " << vec[2];
}

vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator*(const double t, const vec3 &u)
{
    return vec3(u.e[0] * t, u.e[1] * t, u.e[2] * t);
}

vec3 operator*(const vec3 &u, const double t)
{
    return t * u;
}

vec3 operator/(const vec3 &u, const double t)
{
    return (1 / t) * u;
}

double dot(const vec3 &u, const vec3 &v)
{
    return  u.e[0] * v.e[0]
            + u.e[1] * v.e[1]
            + u.e[2] * v.e[2];
}

vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 unit_vector(const vec3 &v)
{
    return v / v.length();
}

vec3 random_in_unit_sphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1,1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

vec3 random_in_hemisphere(const vec3 &normal)
{
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -1 * in_unit_sphere;
}

vec3 random_unit_vector()
{
    double a = random_double(0, 2 * pi);
    double z = random_double(-1, 1);
    double r = sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat)
{
    float cos_theta = dot(-1 * uv, n);
    vec3 r_out_perp =  etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

vec3 random_in_unit_disk()
{
    while (true) {
        vec3 p = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() < 1)
            return p;
    }
}