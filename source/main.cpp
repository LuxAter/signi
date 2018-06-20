#include <iostream>

#include "signi.hpp"

int main(int argc, char* argv[]) {
  signi::Image img = signi::BmpRead("out.bmp");
  signi::PngWrite("testing.png", img);
  /* CODE */
  return 0;
}
