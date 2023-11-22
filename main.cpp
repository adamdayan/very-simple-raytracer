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
  CameraOrientation cam_orient{ Point3(13, 2, 3), Point3(0,0,0), Point3(0,1,0) };
  Camera cam(aspect_ratio, image_width, 40, cam_orient, 0.6, 10.0, 1);
  cam.initialise();

  // setup scene
  HittableList scene;  
  
  // add ground 
  std::shared_ptr<Material> material_ground = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
  scene.add(std::make_shared<Sphere>(Point3(0.0, -1000, 0), 1000.0, material_ground));


  // add randomised spheres 
  for (int i = -11; i < 11; i++) {
    for (int j = -11; j < 11; j++) {
      double select_mat = random_double(0, 1);
      Point3 sphere_center(i + 0.9*random_double(), 0.2, j + 0.9*random_double());
      std::shared_ptr<Material> sphere_mat;

      // ensure no overlaps
      if ((sphere_center- Point3(4, 0.2, 0)).length() > 0.9) {
        if (select_mat > 0.5) {
          // diffuse
          Colour albedo = Colour::random() * Colour ::random();
          sphere_mat = std::make_shared<Lambertian>(albedo);
          scene.add(std::make_shared<Sphere>(sphere_center, 0.2, sphere_mat));
        } else if (select_mat > 0.05) {
          // metal
          Colour albedo = Colour::random();
          sphere_mat = std::make_shared<Metal>(albedo, random_double());
          scene.add(std::make_shared<Sphere>(sphere_center, 0.2, sphere_mat));
        } else {
          // glass 
          sphere_mat = std::make_shared<Dieletric>(1.5);
          scene.add(std::make_shared<Sphere>(sphere_center, 0.2, sphere_mat));
        }
      }
    }
  }

  std::shared_ptr<Material> material1 = std::make_shared<Dieletric>(1.5);
  scene.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

  std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
  scene.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

  std::shared_ptr<Material> material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
  scene.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

  // .ppm standard metadata 
  int max_colour = 255;
  std::cout << "P3" << std::endl;
  std::cout << image_width << " " << cam.get_image_height() << std::endl;
  std::cout << max_colour << std::endl;

  cam.render(scene);


  return 0;
}