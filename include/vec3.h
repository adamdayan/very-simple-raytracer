#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

#include "simple_raytracer.h"

class Vec3 {
  // class to hold sets of related 3 nums - will usually be 3d coordinates or colours
  public:
    Vec3(): nums{0,0,0} {}
    Vec3(double x, double y, double z) : nums{x, y, z} {}

    double x() const {
        return nums[0];
    }

    double y() const {
        return nums[1];
    }
    
    double z() const {
        return nums[2];
    }

    bool near_zero() const {
      double e = 1e-8;
      return (fabs(x()) < e) && (fabs(y()) < e) && (fabs(z() < e));
    }

    Vec3 operator-() const { return Vec3(-nums[0], -nums[1], -nums[2]); }

    double operator[](int i) const { return nums[i]; }
    double& operator[](int i) { return nums[i]; }

    Vec3& operator+=(const Vec3 v) {
      nums[0] += v.x();
      nums[1] += v.y();
      nums[2] += v.z();

      return *this;
    }

    Vec3& operator*=(double m) {
      nums[0] *= m;
      nums[1] *= m;
      nums[2] *= m;

      return *this;
    }

    Vec3& operator/=(double d) {
      nums[0] /= d;
      nums[1] /= d;
      nums[2] /= d;

      return *this;
    }

    double length() const {
      return sqrt(length_squared());
    }

    double length_squared() const {
      return x()*x() + y()*y() + z()*z();
    }

    static Vec3 random() {
      return Vec3(random_double(), random_double(), random_double());
    }

    static Vec3 random(double min, double max) {
      return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }


  private:
    double nums[3];
};

using Point3 = Vec3;

// various utility functions for the Vec3 class

inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  return out << v.x() << " " << v.y() << " " << v.z();
}

inline Vec3 operator+(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline Vec3 operator+(const Vec3& v, const double a) {
  return Vec3(v.x() + a, v.y() + a, v.z() + a);
}

inline Vec3 operator+(const double a, const Vec3& v) {
  return v + a;
}

inline Vec3 operator-(const Vec3& v1, const Vec3& v2) {
  return Vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline Vec3 operator*(const Vec3& v1, const Vec3& v2)  {
  return Vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline Vec3 operator*(const Vec3& v, const double m) {
  return Vec3(v.x() * m, v.y() * m, v.z() * m);
}

inline Vec3 operator*(const double m, const Vec3& v) {
  return v * m;
}

inline Vec3 operator/(const Vec3& v, const double d) {
  return 1/d * v;
}

// make vector's length 1
inline Vec3 unit_vector(const Vec3& v) {
  return v / v.length();
}

inline double dot(const Vec3& v1, const Vec3& v2) {
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
  return Vec3(
    v1.y() * v2.z() - v1.z() * v2.y(),
    v1.z() * v2.x() - v1.x() * v2.z(),
    v1.x() * v2.y() - v1.y() * v2.x()
  );
}

inline Vec3 random_in_unit_sphere() {
  while (true) {
    Vec3 rv = Vec3::random(-1, 1);
    // NOTE: don't understand why below isn't be rv.length()?? The radius of the sphere should be 1 - don't we want the vector's length
    // NOTE: possible answer - it doesn't matter, anything with length() <= 1 will have a length()**2 <= 1
    if (rv.length_squared() < 1.0) { 
      return rv;
    }
  }
}

inline Vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

inline Vec3 random_unit_vector_in_hemisphere(const Vec3& normal) {
  Vec3 ruv = random_unit_vector();
  if (dot(ruv, normal) < 0.0)
    return -ruv;
  return ruv;
}

inline Vec3 compute_reflection(const Vec3& v, const Vec3& normal) {
  // NOTE: I think the final multiplication by n is just normalise but not 100% sure
  return v - 2*dot(v, normal)*normal;
}

inline Vec3 compute_refraction(const Vec3& r_in, const Vec3& normal_in, double refraction_ratio) {
  double cos_theta = std::min(dot(-r_in, normal_in), 1.0);
  Vec3 r_perp = refraction_ratio * (r_in + cos_theta * normal_in);
  Vec3 r_parr = -sqrt(std::abs(1.0-r_perp.length_squared())) * normal_in;
  return r_perp + r_parr;
}

#endif // VEC3_H
