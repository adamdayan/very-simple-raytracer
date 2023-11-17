#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

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

    Vec3 operator-() const { return Vec3(-nums[0], -nums[1], -nums[2]); }

    double operator[](int i) const { return nums[i]; }
    double& operator[](int i) { return nums[i]; }

    Vec3 operator*(Vec3 m) const {
      return Vec3(x() * m.x(), y() * m.y(), z() * m.z());
    };

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


// scale vector between [-1, 1]
inline Vec3 unit_vector(const Vec3& v) {
  return v / v.length();
}

inline double dot(const Vec3& v1, const Vec3& v2) {
  return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() + v2.z();
}

inline Vec3 cross(const Vec3& v1, const Vec3& v2) {
  return Vec3(
    v1.y() * v2.z() - v1.z() * v2.y(),
    v1.z() * v2.x() - v1.x() * v2.z(),
    v1.x() * v2.y() - v1.y() * v2.x()
  );
}

#endif // VEC3_H
