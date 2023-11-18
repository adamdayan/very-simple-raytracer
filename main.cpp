#include <iostream>
#include <cmath>

#include "simple_raytracer.h"
#include "camera.h"
#include "colour.h"
#include "ray.h"
#include "hittable_list.h"
#include "sphere.h"
#include "interval.h"


int main() {
  // setup camera
  float aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  double focal_length = 1.0;
  Camera cam(aspect_ratio, focal_length, image_width);
  cam.initialise();

  // setup scene
  HittableList scene({
    std::make_shared<Sphere>(Point3(0,0,-1), 0.5),
    std::make_shared<Sphere>(Point3(0,-100.5, -1), 100) 
  });

  // .ppm standard metadata 
  int max_colour = 255;
  std::cout << "P3" << std::endl;
  std::cout << image_width << " " << cam.get_image_height() << std::endl;
  std::cout << max_colour << std::endl;

  cam.render(scene);


  return 0;
}