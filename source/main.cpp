#include <iostream>

#include "signi.hpp"

int main(int argc, char* argv[]) {
  signi::Image img = signi::PngRead("small.png");
  std::cout << signi::AnsiWriteString(img, signi::ANSI_HORIZONTAL);
  img = signi::UpSample(img, 100, 76, signi::BilinearKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(img, signi::ANSI_HORIZONTAL);
  // signi::PngWrite("testing.png", img);
  /* CODE */
  return 0;
}
