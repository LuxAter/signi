#include "resample.hpp"

#include <cmath>
#include <functional>

#include "image.hpp"

#include <iostream>

double sinc(double x) {
  if (x == 0) {
    return 1;
  } else {
    return sin(x) / x;
  }
}

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
double signi::BellKernel(double x) {
  if (std::fabs(x) < 0.5) {
    return 0.75 - std::pow(std::fabs(x), 2);
  } else if (std::fabs(x) < 1.5) {
    return 0.5 * std::pow(std::fabs(x) - 1.5, 2);
  } else {
    return 0;
  }
}
double signi::HermiteKernel(double x) {
  if (std::fabs(x) <= 1) {
    return (2 * std::pow(std::fabs(x), 3)) - (3 * std::pow(std::fabs(x), 2)) +
           1;
  } else {
    return 0;
  }
}
double signi::BicubicKernel(double x) {
  const double a = -0.5;
  if (std::fabs(x) <= 1) {
    return ((a + 2) * std::pow(std::fabs(x), 3)) -
           ((a + 3) * std::pow(std::fabs(x), 2)) + 1;
  } else if (std::fabs(x) < 2) {
    return (a * std::pow(std::fabs(x), 3)) -
           (5 * a * std::pow(std::fabs(x), 2)) + (8 * a * std::fabs(x)) -
           (4 * a);
  } else {
    return 0;
  }
}
double signi::MitchellKernel(double x) {
  const double b = (1.0 / 3.0), c = (1.0 / 3.0);
  if (std::fabs(x) < 1) {
    return (1.0 / 6.0) *
           (((12 - (9 * b) - (6 * c)) * std::pow(std::fabs(x), 3)) +
            ((-18 + (12 * b) + (6 * c)) * std::pow(std::fabs(x), 2)) +
            (6 - (2 * b)));
  } else if (std::fabs(x) < 2) {
    return (1.0 / 6.0) * (((-b - 6 * c) * std::pow(std::fabs(x), 3)) +
                          ((6 * b + 30 * c) * std::pow(std::fabs(x), 2)) +
                          ((-12 * b - 48 * c) * std::pow(std::fabs(x), 2)) +
                          (8 * b + 24 * c));
  } else {
    return 0;
  }
}
double signi::LanczosKernel(double x) {
  const double a = 3;
  if (std::fabs(x) < a) {
    return sinc(x) * sinc(x / a);
  } else {
    return 0;
  }
}

signi::Image signi::Resample(const Image& src, std::size_t width,
                             std::size_t height,
                             std::function<double(double)> kernel) {
  bool x_up = false, y_up = false;
  if (width == 0 && height == 0) {
    return src;
  } else if (width == 0 && height != 0) {
    width = src.GetSize().first *
            (static_cast<double>(height) / src.GetSize().second);
  } else if (width != 0 && height == 0) {
    height = src.GetSize().second *
             (static_cast<double>(width) / src.GetSize().first);
  }
  if (width > src.GetSize().first) {
    x_up = true;
  }
  if (height > src.GetSize().second) {
    y_up = true;
  }
  Image dest(width, height);
  double dx = src.GetSize().first / static_cast<double>(width),
         dy = src.GetSize().second / static_cast<double>(height);
  std::vector<std::vector<Pixel>> tmp(width,
                                      std::vector<Pixel>(src.GetSize().second));
  for (std::size_t y = 0; y < src.GetSize().second; ++y) {
    for (std::size_t x = 0; x < width; ++x) {
      Pixel pixel;
      double weight_norm = 0.0;
      for (double sx = std::max(0.0, floor((static_cast<double>(x) - 3) * dx));
           sx <= std::min(static_cast<double>(src.GetSize().first - 1),
                          ceil((x + 3) * dx));
           ++sx) {
        double dist_x;
        if (x_up) {
          dist_x = (sx) - (x * dx);
        } else {
          dist_x = (sx / dx) - x;
        }
        double val = kernel(dist_x);
        weight_norm += val;
        Pixel src_pixel = src.GetPixel(sx, y);
        pixel.r += val * src_pixel.r;
        pixel.g += val * src_pixel.g;
        pixel.b += val * src_pixel.b;
      }
      pixel.r /= weight_norm;
      pixel.g /= weight_norm;
      pixel.b /= weight_norm;
      tmp.at(x).at(y) = pixel;
    }
  }
  for (std::size_t y = 0; y < height; ++y) {
    for (std::size_t x = 0; x < width; ++x) {
      Pixel pixel;
      double weight_norm = 0.0;
      for (double sy = std::max(0.0, floor((static_cast<double>(y) - 3) * dx));
           sy <= std::min(static_cast<double>(src.GetSize().second - 1),
                          ceil((y + 3) * dy));
           ++sy) {
        double dist;
        if (y_up) {
          dist = (sy) - (y * dy);
        } else {
          dist = (sy / dy) - y;
        }
        double val = kernel(dist);
        weight_norm += val;
        Pixel src_pixel = tmp.at(x).at(sy);
        pixel.r += val * src_pixel.r;
        pixel.g += val * src_pixel.g;
        pixel.b += val * src_pixel.b;
      }
      pixel.r /= weight_norm;
      pixel.g /= weight_norm;
      pixel.b /= weight_norm;
      dest.SetPixel(x, y, pixel);
    }
  }
  return dest;
}

signi::Image signi::OldResample(const Image& src, std::size_t width,
                                std::size_t height,
                                std::function<double(double)> kernel) {
  bool x_up = false, y_up = false;
  if (width == 0 && height == 0) {
    return src;
  } else if (width == 0 && height != 0) {
    width = src.GetSize().first *
            (static_cast<double>(height) / src.GetSize().second);
  } else if (width != 0 && height == 0) {
    height = src.GetSize().second *
             (static_cast<double>(width) / src.GetSize().first);
  }
  if (width > src.GetSize().first) {
    x_up = true;
  }
  if (height > src.GetSize().second) {
    y_up = true;
  }
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
          double dist_x, dist_y;
          if (x_up) {
            dist_x = (sx) - (x * dx);
          } else {
            dist_x = (sx / dx) - x;
          }
          if (y_up) {
            dist_y = (sy) - (y * dy);
          } else {
            dist_y = (sy / dy) - y;
          }
          double dist = sqrt(pow(dist_x, 2) + pow(dist_y, 2));
          double val = kernel(dist);
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
      dest.SetPixel(x, y, pixel);
    }
  }
  return dest;
}
