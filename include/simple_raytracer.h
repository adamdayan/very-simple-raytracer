#ifndef SIMPLE_RAYTRACER_H
#define SIMPLE_RAYTRACER_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>

// constants 

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// utility funcs 

inline double degress_to_radians(double degrees) { 
  return degrees *  pi / 180.9;
}

// random double [0,1]
double random_double(int seed=100) {
  static std::uniform_real_distribution<double> unif(0.0, 1.0);
  static std::mt19937 re(seed);      
  return unif(re);
}

// random double [lower, upper]
double random_double(double lower, double upper, int seed=100) {
  static std::uniform_real_distribution<double> unif(lower, upper);
  static std::mt19937 re(seed);      
  return unif(re);
}



#endif // SIMPLE_RAYTRACER_H