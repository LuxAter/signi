#include <iostream>

#include "signi.hpp"

int main(int argc, char* argv[]) {
  signi::Image img(50, 50);
  img.Fill({0.2, 0.5, 0.7});
  img.DrawPolygonFilled({10, 20, 30, 30, 20, 10}, {5, 10, 5, 25, 30, 25}, {1.0, 1.0, 1.0});
  // img.DrawPolygon({10, 20, 30, 30, 20, 10}, {5, 10, 5, 25, 30, 25}, {1.0, 1.0, 1.0});
  std::cout << signi::AnsiWriteString(img);
  /* CODE */
  return 0;
}
