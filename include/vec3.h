//
// Created by Louis Jahn on 8/28/20.
//

#ifndef RAYTRACER___INTRO_VEC3_H
#define RAYTRACER___INTRO_VEC3_H

#include <cmath>
#include <iostream>

class vec3
{
    public:
        vec3(): e{0, 0, 0} {}
        vec3(double x, double y, double z): e{x, y, z} {}
        vec3(const vec3 &cpy): e{cpy.e[0], cpy.e[1], cpy.e[2]} {}

        ~vec3() = default;

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3 &operator=(const vec3 &cpy);
        vec3 &operator+=(const vec3 &v);
        vec3 &operator*=(double t);
        vec3 &operator/=(double t);
        double operator[](std::size_t i);

        double length() const;
        double length_squared() const;

        static vec3 random();
        static vec3 random(double min, double max);
    public:
        double e[3];
};

std::ostream &operator<<(std::ostream &out, vec3 &vec);

vec3 operator+(const vec3 &u, const vec3 &v);

vec3 operator-(const vec3 &u, const vec3 &v);

vec3 operator*(const vec3 &u, const vec3 &v);

vec3 operator*(double t, const vec3 &u);

vec3 operator*(const vec3 &u, double t);

vec3 operator/(const vec3 &u, double t);

double dot(const vec3 &u, const vec3 &v);

vec3 cross(const vec3 &u, const vec3 &v);

vec3 unit_vector(const vec3 &v);

vec3 random_in_unit_sphere();

vec3 random_in_hemisphere(const vec3 &normal);

vec3 random_unit_vector();

vec3 reflect(const vec3 &v, const vec3 &n);

vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat);

vec3 random_in_unit_disk();

// Type aliases for vec3
using point3 = vec3;   // 3D point
using color = vec3;    // RGB color

#endif //RAYTRACER___INTRO_VEC3_H
