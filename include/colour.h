#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"
#include "interval.h"

using Colour = Vec3;

void write_colour(std::ostream& out, const Colour& pixel_colour, int n_samples) {
    double r = pixel_colour.x() / n_samples;
    double g = pixel_colour.y() / n_samples;
    double b = pixel_colour.z() / n_samples;

    static const Interval intensity(0.0, 0.99);
    // print the translated [0,255] value of each colour component
    out << static_cast<int>(intensity.clamp(r) * 255.999) << " " 
        << static_cast<int>(intensity.clamp(g) * 255.999) << " " 
        << static_cast<int>(intensity.clamp(b) * 255.999) << std::endl;
}

#endif // COLOUR_H