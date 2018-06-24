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
  double MitchellKenel(double x);
  double LanczosKernel(double x);

  Pixel ApplyKernel(ResampleKernel kernel, const std::size_t& x,
                    const std::size_t& y, const double& dx, const double& dy,
                    const std::vector<std::vector<Pixel>>* pixel_data);
  Image DownSample(const Image& src, std::size_t width, std::size_t height,
                   ResampleKernel kernel = NEAREST_NEIGHBOR);
  Image UpSample(const Image& src, std::size_t width, std::size_t height,
                 std::function<double(double)> kernel);

  std::vector<double> UpSample(const std::vector<double> src, std::size_t width, std::function<double(double)> kernel);
}  // namespace signi

#endif  // SIGNI_RESAMPLE_HPP_
