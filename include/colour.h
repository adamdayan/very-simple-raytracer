#ifndef COLOUR_H
#define COLOUR_H

#include "vec3.h"

using Colour = Vec3;

void write_colour(std::ostream& out, const Colour& pixel_colour) {
    // print the translated [0,255] value of each colour component
    out << pixel_colour.x() * 255.99 << " " << pixel_colour.y() * 255.99 << " " << pixel_colour.z() * 255.99 << std::endl;
}

#endif // COLOUR_H