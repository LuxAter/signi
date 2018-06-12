#include <iostream>

#include "signi.hpp"

int main(int argc, char* argv[]) {
  signi::Image img(50, 50);
  img.Fill({0.2, 0.5, 0.7});
  img.DrawLine(0, 0, 40, 35, {1.0, 1.0, 1.0});
  std::string res = signi::AnsiWriteString(img, signi::ANSI_HORIZONTAL);
  std::cout << res << "\n";
  signi::Image read = signi::AnsiReadString(res);
  read.DrawLine(0, 10, 30, 30, {1.0, 0.0, 1.0});
  std::cout << signi::AnsiWriteString(read);
  /* CODE */
  return 0;
}
