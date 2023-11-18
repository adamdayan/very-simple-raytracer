#ifndef INTERVAL_H
#define INTERVAL_H

#include "simple_raytracer.h"

class Interval {
  public:
    Interval(double min, double max) : min(min), max(max) {}
    Interval() : min(+infinity), max(-infinity) {}

    bool contains(double val) const {
      return min <= val && val <= max;
    }

    bool surrounds(double val) const {
      return min < val && val < max;
    }

    double clamp(double val) const {
      if (val < min) return min;
      if (val > max) return max;
      return val;
    }

    static const Interval empty, universe;

    double min;
    double max;
};

const static Interval empty(+infinity,-infinity); // NOTE: don't fully understand why these should be initialised here but declared inside Interval. Also how does the namespacing work?
const static Interval universe(-infinity,+infinity);

#endif // INTERVAL_H