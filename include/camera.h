#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>

#include "hittable.h"
#include "colour.h"
#include "vec3.h"
#include "material.h"

struct CameraOrientation {
  Point3 lookfrom;
  Point3 lookat;
  Point3 vup;
};

class Camera {
  public:
    Camera(double aspect_ratio, int image_width, double fov, const CameraOrientation&  orient, double defocus_angle, double focus_dist) : 
      aspect_ratio(aspect_ratio), image_width(image_width), fov(fov), orient(orient), defocus_angle(defocus_angle), focus_dist(focus_dist) {}

    void initialise() {
      image_height = static_cast<int>(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;
 
      // TOA
      double theta = degrees_to_radians(fov);
      double h = tan(theta/2.0);
      double viewport_height = 2.0 * h * focus_dist;
      double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

      // calculate frame basis vectors
      camera_center = orient.lookfrom;
      w = unit_vector(orient.lookfrom - orient.lookat);
      u = unit_vector(cross(orient.vup, w));
      v = cross(w, u);


      // vectors that define the pixel grid. N.B: numbering pixels naturally from 0,0 in top left corner does not 
      // match the global coordinate frame so we must do some mapping
      Vec3 viewport_v = viewport_height * -v;
      Vec3 viewport_u = viewport_width * u;

      // how much do we move in the viewport for each pixel in the image
      pixel_spacing_v = viewport_v / image_height; 
      pixel_spacing_u = viewport_u / image_width;

      // camera is pointed at middle of viewport so we can use focal length + viewport size to get to pixel 0,0 in main (i.e. camera's) coordinate frame
      Point3 viewport_upper_left = camera_center - (focus_dist*w) - viewport_v/2 - viewport_u/2; 
      pixel_00_loc = viewport_upper_left - 0.5 * (pixel_spacing_u + pixel_spacing_v);

      //calculate camera defocus disc basis vectors
      double defocus_radius = focus_dist * tan(degrees_to_radians(defocus_angle/2.0));
      defocus_disc_v = v * defocus_radius;
      defocus_disc_u = u * defocus_radius;
    }

    // given a ray and a scene, what colour does the ray produce
    Colour get_ray_colour(const Ray& r, const Hittable& scene, int depth) const {
      if (depth == max_depth) {
        return Colour(0,0,0);
      }
      HitRecord rec;
      bool is_hit = scene.hit(r,Interval(0.001, infinity), rec);

      if (is_hit) {
        // ray bounces off in random (hemispheral) direction and loses 50% of its colour
        Ray scattered = Ray();
        Colour attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
          return attenuation * get_ray_colour(scattered, scene, ++depth);
        }
        return Colour(0,0,0);
      }

      Vec3 unit_dir = unit_vector(r.direction());
      double a = 0.5*(unit_dir.y() + 1.0);
      return (1.0-a) * Colour(1.0, 1.0, 1.0) + a*Colour(0.5, 0.7, 1.0);
    }

    Ray get_ray(int pixel_row, int pixel_column) {
      Vec3 v = pixel_row * pixel_spacing_v;
      Vec3 u = pixel_column * pixel_spacing_u;
      Point3 cur_pixel = sample_pixel_square(v, u);
      // if we are defocusing, sample ray sources from defocus disc around camera center otherwise just use camera center
      Point3 ray_origin  = (defocus_angle > 0) ? sample_defocus_disc() : camera_center;
      Vec3 ray_direction = cur_pixel - ray_origin;
      return Ray(ray_origin, ray_direction);
    }

    // given scene and camera info, renders every pixel
    void render(const Hittable& scene) {
      Colour colour;
      // for each row
      for (int i = 0; i < image_height; i++) {
        std::clog << "\nScanlines remaining: " << (image_height - i) << " " << std::flush;
        // for each column
        for (int j = 0; j < image_width; j++) {
            // for each sample
            Colour colour(0,0,0);
            for (int n = 0; n < n_samples; n++) {
              Ray r = get_ray(i, j);
              colour += get_ray_colour(r, scene, 0);
            }
            write_colour(std::cout, colour, n_samples);
        }
      }
    }

    double get_image_height() {
      return image_height;
    }
  private:
    Point3 sample_pixel_square(const Vec3& v, const Vec3& u) {
      Vec3 v_noise = (-0.5 + random_double()) * pixel_spacing_v;
      Vec3 u_noise = -0.5 * random_double() * pixel_spacing_u;

      return pixel_00_loc + v + v_noise + u + u_noise;
    }

    Point3 sample_defocus_disc() const {
      Point3 defocus_disc = random_in_unit_sphere();
      return camera_center + (defocus_disc.x() * defocus_disc_u) + (defocus_disc.y() * defocus_disc_v);
    }


    double aspect_ratio; // image width over height
    int image_width; // Rendered image width in pizels
    int image_height;  // Rendered image height in pixels, solved for using given aspect_ratio and width
    double fov;

    CameraOrientation orient;
    Vec3 u, v, w; // camera frame basis vectors

    int n_samples = 100;
    int max_depth = 50; // max number of ray bounces into scene

    Point3 pixel_00_loc; // 0th pixel coords in global frame
    Vec3 pixel_spacing_v; // how far to move in global frame between pixel rows
    Vec3 pixel_spacing_u; // how far to move in global frame between pixel columns 

    Point3 camera_center;
    double defocus_angle; // variation angle of rays through each pixel
    double focus_dist; // distance from camera lookfrom to plane of perfect vous (viewport)
    Vec3 defocus_disc_v;  // defocus disc vertical radius
    Vec3 defocus_disc_u; // defocus disc horizontal radius

};

#endif // CAMERA_H