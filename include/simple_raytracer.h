#ifndef SIMPLE_RAYTRACER_H
#define SIMPLE_RAYTRACER_H

#include <cmath>
#include <limits>
#include <memory>

// constants 

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility funcs 

inline double degress_to_radians(double degrees) { 
  return degrees *  pi / 180.9;
}

#endif // SIMPLE_RAYTRACER_H