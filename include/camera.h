#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "colour.h"
#include "vec3.h"

class Camera {
  public:
    Camera(double aspect_ratio, double focal_length, int image_width) : 
      aspect_ratio(aspect_ratio), focal_length(focal_length), image_width(image_width) {}

    void initialise() {
      image_height = static_cast<int>(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;
 
      double viewport_height = 2.0;
      double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
      camera_center = Point3(0,0,0);

      // vectors that define the pixel grid. N.B: numbering pixels naturally from 0,0 in top left corner does not 
      // match the global coordinate frame so we must do some mapping
      Vec3 viewport_v{0, -viewport_height, 0};
      Vec3 viewport_u{viewport_width, 0, 0};

      // how much do we move in the viewport for each pixel in the image
      pixel_spacing_v = viewport_v / image_height; 
      pixel_spacing_u = viewport_u / image_width;

      // camera is pointed at middle of viewport so we can use focal length + viewport size to get to pixel 0,0 in main (i.e. camera's) coordinate frame
      Point3 viewport_upper_left = camera_center - Vec3{0,0, focal_length} - viewport_v/2 - viewport_u/2; 
      pixel_00_loc = viewport_upper_left - 0.5 * (pixel_spacing_u + pixel_spacing_v);
    }

    // given a ray and a scene, what colour does the ray produce
    Colour get_ray_colour(const Ray& r, const Hittable& scene) const {
      HitRecord rec;
      bool is_hit = scene.hit(r,Interval(0, infinity), rec);

      if (is_hit) {
        return Colour(0.5*(rec.normal + 1.0));
      }

      Vec3 unit_dir = unit_vector(r.direction());
      double a = 0.5*(unit_dir.y() + 1.0);
      return (1.0-a) * Colour(1.0, 1.0, 1.0) + a*Colour(0, 0, 1.0);
    }

    Ray get_ray(int pixel_row, int pixel_column) {
      Vec3 v = pixel_row * pixel_spacing_v;
      Vec3 u = pixel_column * pixel_spacing_u;
      Point3 cur_pixel = sample_pixel_square(v, u);
      Vec3 ray_direction = cur_pixel - camera_center;
      return Ray(camera_center, ray_direction);
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
              colour += get_ray_colour(r, scene);
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


    double aspect_ratio;
    double focal_length;
    int image_width;
    int image_height; 
    int n_samples = 10;
    Point3 pixel_00_loc;
    Vec3 pixel_spacing_v;
    Vec3 pixel_spacing_u;

    Point3 camera_center;
};

#endif // CAMERA_H