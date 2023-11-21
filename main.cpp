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
  HittableList scene;  
  
  std::shared_ptr<Material> material_ground = std::make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
  // std::shared_ptr<Material> material_center = std::make_shared<Lambertian>(Colour(0.7, 0.3, 0.3));
  // std::shared_ptr<Material> material_left = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.3);
  std::shared_ptr<Material> material_center = std::make_shared<Dieletric>(1.5);
  std::shared_ptr<Material> material_left = std::make_shared<Dieletric>(1.5);
  std::shared_ptr<Material> material_right = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2), 1.0);

  scene.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
  scene.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
  scene.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
  scene.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

  // .ppm standard metadata 
  int max_colour = 255;
  std::cout << "P3" << std::endl;
  std::cout << image_width << " " << cam.get_image_height() << std::endl;
  std::cout << max_colour << std::endl;

  cam.render(scene);


  return 0;
}