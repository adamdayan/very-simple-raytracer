#include <iostream>
#include <cmath>
#include "colour.h"

// void print_progress_bar(int image_height, int image_width, int cur_row, int cur_column) {
//     int total_pixels = image_height * image_width;
//     int completed = (cur_row * image_width) + cur_column;
//     int rounded_pct = round(static_cast<double>(completed) / total_pixels * 100)
// }

int main() {
  int image_height = 528;
  int image_width = 528;
  int max_colour = 255;

  std::cout << "P3" << std::endl;
  std::cout << image_width << " " << image_height << std::endl;
  std::cout << max_colour << std::endl;

  Colour colour;
  for (int i = 0; i < image_height; i++) {
      std::clog << "\nScanlines remaining: " << (image_height - i) << " " << std::flush;
      for (int j = 0; j < image_width; j++) {
          colour = Colour(static_cast<double>(j) / image_height, static_cast<double>(i) / image_width, 0);
          write_colour(std::cout, colour);
      }
  }

  return 0;
}