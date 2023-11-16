#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
  public:
    Ray(const Point3& orig, const Point3& dir) : orig(orig), dir(dir) {}

    Point3 origin() const { return orig; }
    Point3 direction() const { return dir; }

    Point3 at(double t) { return orig + (t * dir); }

  private:
    Point3 orig;
    Point3 dir;
};

#endif // RAY_H