#include <iostream>

#include "signi.hpp"

int main(int argc, char* argv[]) {
  signi::Image img = signi::PngRead("test.png");
  std::cout << signi::AnsiWriteString(img, signi::ANSI_HORIZONTAL);
  signi::Image res = signi::Resample(img, 150, 0, signi::NearestNeighborKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  res= signi::Resample(img, 150, 0, signi::BilinearKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  res= signi::Resample(img, 150, 0, signi::BellKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  res= signi::Resample(img, 150, 0, signi::HermiteKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  res= signi::Resample(img, 150, 0, signi::BicubicKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  res= signi::Resample(img, 150, 0, signi::MitchellKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  res= signi::Resample(img, 150, 0, signi::LanczosKernel);
  std::cout << "==============================\n";
  std::cout << signi::AnsiWriteString(res, signi::ANSI_HORIZONTAL);
  /* CODE */
  return 0;
}
