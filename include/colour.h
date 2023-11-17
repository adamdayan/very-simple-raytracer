#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

using Colour = Vec3;

void write_colour(std::ostream& out, const Colour& pixel_colour) {
    // print the translated [0,255] value of each colour component
    out << static_cast<int>(pixel_colour.x() * 255.999) << " " 
        << static_cast<int>(pixel_colour.y() * 255.999) << " " 
        << static_cast<int>(pixel_colour.z() * 255.999) << std::endl;
}

#endif // COLOUR_H