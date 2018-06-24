#include "resample.hpp"

#include <cmath>
#include <functional>

#include "image.hpp"

#include <iostream>

double signi::NearestNeighborKernel(double x) {
  if (std::fabs(x) <= 0.5) {
    return 1;
  } else {
    return 0;
  }
}
double signi::BilinearKernel(double x) {
  if (std::fabs(x) < 1) {
    return 1 - std::fabs(x);
  } else {
    return 0;
  }
}
double signi::BellKernel(double x) {}
double signi::HermiteKernel(double x) {}
double signi::BicubicKernel(double x) {}
double signi::MitchellKenel(double x) {}
double signi::LanczosKernel(double x) {}

signi::Pixel signi::ApplyKernel(
    ResampleKernel kernel, const std::size_t& x, const std::size_t& y,
    const double& dx, const double& dy,
    const std::vector<std::vector<Pixel>>* pixel_data) {
  double sx = x * dx;
  double sy = y * dy;
  double weight = 0.0;
  double sum = 0.0;
}

signi::Image signi::DownSample(const Image& src, std::size_t width,
                               std::size_t height, ResampleKernel kernel) {
  Image dest(width, height);
  return dest;
}
signi::Image signi::UpSample(const Image& src, std::size_t width,
                             std::size_t height,
                             std::function<double(double)> kernel) {
  Image dest(width, height);
  double dx = src.GetSize().first / static_cast<double>(width),
         dy = src.GetSize().second / static_cast<double>(height);
  for (std::size_t y = 0; y < height; ++y) {
    for (std::size_t x = 0; x < width; ++x) {
      Pixel pixel;
      double weight_norm = 0.0;
      for (double sy = std::max(0.0, floor((static_cast<double>(y) - 3) * dy));
           sy <= std::min(static_cast<double>(src.GetSize().second - 1),
                         ceil((y + 3) * dy));
           ++sy) {
        for (double sx =
                 std::max(0.0, floor((static_cast<double>(x) - 3) * dx));
             sx <= std::min(static_cast<double>(src.GetSize().first - 1),
                           ceil((x + 3) * dx));
             ++sx) {
          double dist_x = (sx) - (x* dx);
          double dist_y = (sy) - (y * dy);
          double dist = sqrt(pow(dist_x, 2) + pow(dist_y, 2));
          double val = kernel(dist);
          if(x == 1 && y == 1){
            std::cout << sx << ',' << sy << ":" << dist << "->" << val << '\n';
          }
          weight_norm += val;
          Pixel src_pixel = src.GetPixel(sx, sy);
          pixel.r += val * src_pixel.r;
          pixel.g += val * src_pixel.g;
          pixel.b += val * src_pixel.b;
        }
      }
        pixel.r /= weight_norm;
        pixel.g /= weight_norm;
        pixel.b /= weight_norm;
      // std::cout << pixel.r << ',' << pixel.g << ',' << pixel.b << '\n';
      dest.SetPixel(x, y, pixel);
    }
  }
  return dest;
  //   src.GetSize().second; double range = 1; Pixel rgba; for (std::size_t y =
  //   0; y < height; ++y) {
  //     for (std::size_t x = 0; x < width; ++x) {
  //       double sum = 0.0, weight_norm = 0.0;
  //       for (std::size_t sx = (x > 3 ? x - 3 : 0);
  //            sx < (x + 3 < width ? x + 3 : width); ++sx) {
  //         for (std::size_t sy = (y > 3 ? y - 3 : 0);
  //              sy < (y + 3 < width ? y + 3 : width); ++sy) {
  //           sum += (NearestNeighborKernel(std::floor(sx * dx) / dx) *
  //                   src.GetPixel(std::floor(sx * dx), std::floor(sy *
  //                   dy)).r);
  //           weight_norm += NearestNeighborKernel(std::floor(sx * dx) / dx);
  //         }
  //       }
  //       dest.SetPixel(x, y, rgba);
  //     }
  //   }
  //   return dest;
}

std::vector<double> signi::UpSample(const std::vector<double> src,
                                    std::size_t width,
                                    std::function<double(double)> kernel) {
  std::vector<double> res;
  double dx = src.size() / static_cast<double>(width);
  for (std::size_t x = 0; x < width; ++x) {
    double sum = 0.0, weight_norm = 0.0;
    for (double sx = std::max(0.0, floor(((double)x - 3) * dx));
         sx <= std::min((double)src.size() - 1, ceil((x + 3) * dx)); ++sx) {
      weight_norm += kernel((((double)sx / dx) - x) * dx);
      sum += (kernel((((double)sx / dx) - x) * dx) * src.at(sx));
    }
    res.push_back(sum / weight_norm);
  }
  return res;
}
