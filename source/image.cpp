#include "image.hpp"

#include <cmath>

signi::Image::Image() : width_(0), height_(0) {}
signi::Image::Image(std::size_t width, std::size_t height)
    : width_(width),
      height_(height),
      pixel_data_(width_, std::vector<Pixel>(height_)) {}
signi::Image::~Image() {}
void signi::Image::SetPixel(int x, int y, Pixel pixel) {
  if (static_cast<unsigned>(x) < width_ && static_cast<unsigned>(y) < height_) {
    pixel_data_[x][y] = pixel;
  }
}

void signi::Image::Fill(Pixel pixel) {
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      pixel_data_[x][y] = pixel;
    }
  }
}

void signi::Image::DrawPixel(int x, int y, Pixel pixel) {
  SetPixel(x, y, pixel);
}
void signi::Image::DrawLineLow(int x0, int y0, int x1, int y1, Pixel pixel) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }
  int d = 2 * dy - dx;
  int y = y0;
  for (int x = x0; x < x1; ++x) {
    SetPixel(x, y, pixel);
    if (d > 0) {
      y += yi;
      d -= (2 * dx);
    }
    d += (2 * dy);
  }
}
void signi::Image::DrawLineHigh(int x0, int y0, int x1, int y1, Pixel pixel) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }
  int d = 2 * dx - dy;
  int x = x0;
  for (int y = y0; y < y1; ++y) {
    SetPixel(x, y, pixel);
    if (d > 0) {
      x += xi;
      d -= (2 * dy);
    }
    d += (2 * dx);
  }
}
void signi::Image::DrawLine(int x0, int y0, int x1, int y1, Pixel pixel,
                            int breadth) {
  // SetPixel(x0, y0, pixel);
  if (abs(y1 - y0) < abs(x1 - x0)) {
    if (x0 > x1) {
      DrawLineLow(x1, y1, x0, y0, pixel);
    } else {
      DrawLineLow(x0, y0, x1, y1, pixel);
    }
  } else {
    if (y0 > y1) {
      DrawLineHigh(x1, y1, x0, y0, pixel);
    } else {
      DrawLineHigh(x0, y0, x1, y1, pixel);
    }
  }
  // SetPixel(x1, y1, pixel);
}
void signi::Image::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2,
                                Pixel pixel, int breadth) {}
void signi::Image::DrawRectangle(int x, int y, int width, int height,
                                 Pixel pixel, int breadth) {}
void signi::Image::DrawPolygon(std::vector<int> x, std::vector<int> y,
                               Pixel pixel, int breadth) {}
void signi::Image::DrawPolygon(std::vector<std::array<int, 2>> points,
                               Pixel pixel, int breadth) {}


bool signi::operator==(const Pixel& lhs, const Pixel& rhs) {
    return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b &&
            lhs.a == rhs.a);
  }
double signi::PixelDiff(const Pixel& lhs, const Pixel& rhs){
  return pow(lhs.r - rhs.r, 2) + pow(lhs.g - rhs.g, 2) + pow(lhs.b - rhs.b, 2);
}
