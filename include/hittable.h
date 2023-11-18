#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
#include "interval.h"

// contains information about where a Ray hit a Hittable
class HitRecord {
  public:
    // where did hit take place
    Point3 p;
    // what's the normal from the hit point
    Vec3 normal;
    // at what point along the ray did the hit take place
    double t;
    // did the ray arrive from inside the Hittable or outside
    bool front_face = false;


    void set_face_normal(const Ray& r, const Vec3& r_normal) {
      if (dot(r.direction(), normal) > 0.0) {
        normal = -r_normal;
        front_face = false;
      } else {
        normal = r_normal;
        front_face = true;
      }
    }
};


// abstract class for all things that a Ray can hit
class Hittable {
  public:
    virtual ~Hittable() = default;
    virtual bool hit(const Ray &r, const Interval& t_interval, HitRecord& rec) const = 0;
};

#endif // HITTABLE_H