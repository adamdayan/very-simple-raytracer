#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere : public Hittable {
  public:
    Sphere(const Point3& center, double radius, std::shared_ptr<Material> mat) : center(center), radius(radius), mat(mat) {}
    ~Sphere() = default;

    bool hit(const Ray &r, const Interval& t_interval, HitRecord& rec) const override {
      Vec3 a_minus_c = r.origin() - center;
      // building up the quadratic formula
      double a = r.direction().length_squared();     // vector dot-producted with itself == vector's length squared
      double half_b = dot(a_minus_c, r.direction()); // because b is a multiple of 2 we can re-arrange the quadratic formula to be simpler
      double c = a_minus_c.length_squared() - radius * radius;

      double discriminant = half_b * half_b - a * c;
      // if discrim > 0 then there are 2 real solutions for t, if discrim == 0 then there is 1 real solutions for t else there are none
      if (discriminant < 0) {
        return false;
      }

      double possible_t = (-half_b - sqrt(discriminant)) / a;
      // check that t doesn't exceed min and max values
      if (!t_interval.surrounds(possible_t)) {
        possible_t = (-half_b + sqrt(discriminant)) / a;
        if (!t_interval.surrounds(possible_t)) {
          return false;
        }
      }

      rec.t = possible_t; 
      rec.p = r.at(rec.t);
      rec.set_face_normal(r, (rec.p - center) / radius); // dividing by radius to make normal a unit vector
      rec.mat = mat;

      return true;
    }

  private:
    Point3 center;
    double radius;
    std::shared_ptr<Material> mat;
};


#endif // SPHERE_H