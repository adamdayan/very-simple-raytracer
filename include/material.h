#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "colour.h"
#include "hittable.h"

class Material {
  public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& hit, Colour& colour, Ray& r_out) const = 0;
};

class Lambertian : public Material {
  public:
    Lambertian(const Colour& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Colour& colour, Ray& r_out) const override {
      Vec3 ruv = random_unit_vector();
      Vec3 scatter_direction = rec.normal + ruv;

      if (ruv.near_zero()) {
        scatter_direction = rec.normal;
      }       

      r_out = Ray(rec.p, scatter_direction);
      colour = albedo;
      return true;
    }

  private:
    // NOTE: don't fully understand what albedo is - is it the colour reflected from this surface?
    Colour albedo;
};

class Metal : public Material { 
  public:
    Metal(const Colour& albedo, double fuzz) : albedo(albedo), fuzz(fuzz) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Colour& colour, Ray& r_out) const override {
      Vec3 reflection_direction = compute_reflection(unit_vector(r_in.direction()), rec.normal);
      // add fuzzing sphere to endpoint of reflection for a "fuzzier reflection"
      r_out = Ray(rec.p, reflection_direction + fuzz * random_unit_vector());
      colour = albedo;
      // this check ensures that rays from the fuzzing step don't go back into the material
      return dot(r_out.direction(), rec.normal) > 0;
    }
  private:
    Colour albedo;
    double fuzz;
};

class Dieletric : public Material {
  public:
    Dieletric(double index_of_refraction) : ir(index_of_refraction) {}
    bool scatter(const Ray& r_in, const HitRecord& rec, Colour& colour, Ray& r_out) const override {
      colour = Colour(1.0, 1.0, 1.0);
      double refraction_ratio = rec.front_face ? 1.0/ir : ir; // NOTE: how do we know the refractive index of the other material is 1.0? Are we assuming ray always enters from "vacum"?
      Vec3 refraction_direction = compute_refraction(unit_vector(r_in.direction()), rec.normal, refraction_ratio);
      r_out = Ray(rec.p, refraction_direction);
      return true;
    }

  private:
    double ir;
};

#endif // MATERIAL_H