//
// Created by Louis Jahn on 8/28/20.
//

#ifndef RAYTRACER___INTRO_COLOR_H
#define RAYTRACER___INTRO_COLOR_H

#include "vec3.h"
#include "utils.h"

/**
 * Writes i
 * @param out stream to write to
 * @param pixel_color the color values
 * @param samples_per_pixel the number of samples for each pixel (anti-aliasing)
 */
inline void write_color(color &pixel, const color &pixel_color, size_t samples_per_pixel)
{
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    // If images are not gamma-encoded, they allocate too many bits or too
    // much bandwidth to highlights that humans cannot differentiate, and
    // too few bits or too little bandwidth to shadow values that humans are
    // sensitive to and would require more bits/bandwidth to maintain the same
    // visual quality.

    // Why not just divide members directly? Is it faster by doing so?
    double scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
//    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
//        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
//        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    pixel.e[0] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    pixel.e[1] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    pixel.e[2] = static_cast<int>(256 * clamp(b, 0.0, 0.999));
}

#endif //RAYTRACER___INTRO_COLOR_H
