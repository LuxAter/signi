#ifndef SIGNI_RESAMPLE_HPP_
#define SIGNI_RESAMPLE_HPP_


#include <functional>

#include "image.hpp"

namespace signi {
  enum ResampleKernel {
    NEAREST_NEIGHBOR,
    BILINEAR,
    BELL,
    HERMITE,
    BICUBIC,
    MITCHELL,
    LANCZOS
  };

  double NearestNeighborKernel(double x);
  double BilinearKernel(double x);
  double BellKernel(double x);
  double HermiteKernel(double x);
  double BicubicKernel(double x);
  double MitchellKernel(double x);
  double LanczosKernel(double x);

  Image Resample(const Image& src, std::size_t width, std::size_t height,
                   std::function<double(double)> kernel);
  Image OldResample(const Image& src, std::size_t width, std::size_t height,
                   std::function<double(double)> kernel);
}  // namespace signi

#endif  // SIGNI_RESAMPLE_HPP_
