#include <iostream>

#include "signi.hpp"

int main(int argc, char* argv[]) {
  signi::Image img = signi::PngRead("a.png");
  std::cout << signi::AnsiWriteString(img, signi::ANSI_HORIZONTAL);
  // signi::PngWrite("a.png", img);
  /* CODE */
  return 0;
}
