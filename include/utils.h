//
// Created by Louis Jahn on 9/11/20.
//

#ifndef RAYTRACER___INTRO_UTILS_H
#define RAYTRACER___INTRO_UTILS_H

#include <cmath>
#include <cstdlib>

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

/**
 * Returns a random real in [0,1).
 * @return random double
 */
inline double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

/**
 * Returns a random real in [min,max).
 * @param min
 * @param max
 * @return random double
 */
inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

/**
 * Returns a double bordered between a min and a max value
 * @param x the value to clamp
 * @param min
 * @param max
 * @return double limited clamped between min and max
 */
inline double clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

#endif //RAYTRACER___INTRO_UTILS_H