#include <iostream>
#include <cmath>

#include "simple_raytracer.h"
#include "colour.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"

// just a stub atm
Colour ray_colour(const Ray& r, const HittableList& scene) {

  HitRecord rec;
  bool is_hit = scene.hit(r,Interval(0, infinity), rec);

  if (is_hit) {
    return Colour(0.5*(rec.normal + 1.0));
  }

  Vec3 unit_dir = unit_vector(r.direction());
  double a = 0.5*(unit_dir.y() + 1.0);
  return (1.0-a) * Colour(1.0, 1.0, 1.0) + a*Colour(0, 0, 1.0);
}

int main() {
  // image
  float aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = static_cast<int>(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height; 

  // camera 
  double viewport_height = 2.0;
  double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
  Point3 camera_center{0,0,0};
  double focal_length = 1.0; // NOTE: should this be a vector?

  // vectors that define the pixel grid. N.B: numbering pixels naturally from 0,0 in top left corner does not 
  // match the global coordinate frame so we must do some mapping
  Vec3 viewport_v{0, -viewport_height, 0};
  Vec3 viewport_u{viewport_width, 0, 0};

  // how much do we move in the viewport for each pixel in the image
  Vec3 pixel_spacing_v = viewport_v / image_height; 
  Vec3 pixel_spacing_u = viewport_u / image_width;

  // camera is pointed at middle of viewport so we can use focal length + viewport size to get to pixel 0,0 in main (i.e. camera's) coordinate frame
  Point3 viewport_upper_left = camera_center - Vec3{0,0, focal_length} - viewport_v/2 - viewport_u/2; 
  Point3 pixel_00_loc = viewport_upper_left - 0.5 * (pixel_spacing_u + pixel_spacing_v);

  // setup scene
  HittableList scene({
    std::make_shared<Sphere>(Point3(0,0,-1), 0.5),
    std::make_shared<Sphere>(Point3(0,-100.5, -1), 100) 
  });

  // .ppm standard metadata 
  int max_colour = 255;
  std::cout << "P3" << std::endl;
  std::cout << image_width << " " << image_height << std::endl;
  std::cout << max_colour << std::endl;

  // render 
  Colour colour;
  for (int i = 0; i < image_height; i++) {
      std::clog << "\nScanlines remaining: " << (image_height - i) << " " << std::flush;
      for (int j = 0; j < image_width; j++) {
          Point3 cur_pixel = pixel_00_loc + (i * pixel_spacing_v) + (j * pixel_spacing_u);
          Vec3 ray_direction = cur_pixel - camera_center;
          Ray r(camera_center, ray_direction);

          Colour colour = ray_colour(r, scene);
          write_colour(std::cout, colour);
      }
  }

  return 0;
}