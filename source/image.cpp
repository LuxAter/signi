#include "image.hpp"

#include <algorithm>
#include <cmath>

#include <iostream>

signi::Image::Image() : width_(0), height_(0) {}
signi::Image::Image(std::size_t width, std::size_t height)
    : width_(width),
      height_(height),
      pixel_data_(width_, std::vector<Pixel>(height_)) {}
signi::Image::~Image() {}

void signi::Image::Fill(Pixel pixel) {
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      pixel_data_[x][y] = pixel;
    }
  }
}

void signi::Image::DrawPixel(int x, int y, Pixel pixel, int breadth) {
  if (breadth == 1) {
    SetPixel(x, y, pixel);
  } else {
    DrawCircleFilled(x, y, breadth / 2, pixel);
  }
}
void signi::Image::DrawLineLow(int x0, int y0, int x1, int y1, Pixel pixel,
                               int breadth) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yi = 1;
  if (dy < 0) {
    yi = -1;
    dy = -dy;
  }
  int d = 2 * dy - dx;
  int y = y0;
  for (int x = x0; x <= x1; ++x) {
    DrawPixel(x, y, pixel, breadth);
    if (d > 0) {
      y += yi;
      d -= (2 * dx);
    }
    d += (2 * dy);
  }
}
void signi::Image::DrawLineHigh(int x0, int y0, int x1, int y1, Pixel pixel,
                                int breadth) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xi = 1;
  if (dx < 0) {
    xi = -1;
    dx = -dx;
  }
  int d = 2 * dx - dy;
  int x = x0;
  for (int y = y0; y <= y1; ++y) {
    DrawPixel(x, y, pixel, breadth);
    if (d > 0) {
      x += xi;
      d -= (2 * dy);
    }
    d += (2 * dx);
  }
}
void signi::Image::DrawLine(int x0, int y0, int x1, int y1, Pixel pixel,
                            int breadth) {
  if (abs(y1 - y0) < abs(x1 - x0)) {
    if (x0 > x1) {
      DrawLineLow(x1, y1, x0, y0, pixel, breadth);
    } else {
      DrawLineLow(x0, y0, x1, y1, pixel, breadth);
    }
  } else {
    if (y0 > y1) {
      DrawLineHigh(x1, y1, x0, y0, pixel, breadth);
    } else {
      DrawLineHigh(x0, y0, x1, y1, pixel, breadth);
    }
  }
}
void signi::Image::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2,
                                Pixel pixel, int breadth) {
  DrawLine(x0, y0, x1, y1, pixel, breadth);
  DrawLine(x0, y0, x2, y2, pixel, breadth);
  DrawLine(x1, y1, x2, y2, pixel, breadth);
}
void signi::Image::DrawRectangle(int x, int y, int width, int height,
                                 Pixel pixel, int breadth) {
  DrawLine(x, y, x + width, y, pixel, breadth);
  DrawLine(x, y, x, y + height, pixel, breadth);
  DrawLine(x + width, y, x + width, y + height, pixel, breadth);
  DrawLine(x, y + height, x + width, y + height, pixel, breadth);
}
void signi::Image::DrawCircle(int cx, int cy, int radius, Pixel pixel,
                              int breadth) {
  int x = radius - 1;
  int y = 0;
  int err = (x * x) - (radius * radius) + radius;
  while (x >= y) {
    DrawPixel(cx + x, cy + y, pixel, breadth);
    DrawPixel(cx + y, cy + x, pixel, breadth);
    DrawPixel(cx - y, cy + x, pixel, breadth);
    DrawPixel(cx - x, cy + y, pixel, breadth);
    DrawPixel(cx - x, cy - y, pixel, breadth);
    DrawPixel(cx - y, cy - x, pixel, breadth);
    DrawPixel(cx + y, cy - x, pixel, breadth);
    DrawPixel(cx + x, cy - y, pixel, breadth);
    if (err <= 0) {
      y++;
      err += 2 * y + 1;
    } else {
      x--;
      err -= x * 2 + 1;
    }
  }
}
void signi::Image::DrawPolygon(std::vector<int> x, std::vector<int> y,
                               Pixel pixel, int breadth) {
  for (std::size_t i = 1; i < x.size() && i < y.size(); ++i) {
    DrawLine(x[i - 1], y[i - 1], x[i], y[i], pixel, breadth);
  }
  DrawLine(x[0], y[0], x.back(), y.back(), pixel, breadth);
}
void signi::Image::DrawPolygon(std::vector<std::array<int, 2>> points,
                               Pixel pixel, int breadth) {
  for (std::size_t i = 1; i < points.size(); ++i) {
    DrawLine(points[i - 1][0], points[i - 1][1], points[i][0], points[i][1],
             pixel, breadth);
  }
  DrawLine(points[0][0], points[0][1], points.back()[0], points.back()[1],
           pixel, breadth);
}

void signi::Image::DrawTriangleFilled(int x0, int y0, int x1, int y1, int x2,
                                      int y2, Pixel pixel) {
  DrawPolygonFilled({x0, x1, x2}, {y0, y1, y2}, pixel);
}
void signi::Image::DrawRectangleFilled(int x, int y, int width, int height,
                                       Pixel pixel) {
  for (int i = x; i < width; ++i) {
    for (int j = y; j < height; ++j) {
      SetPixel(i, j, pixel);
    }
  }
}
void signi::Image::DrawCircleFilled(int cx, int cy, int radius, Pixel pixel) {
  int rsq = radius * radius;
  for (int y = -radius; y <= radius; ++y) {
    for (int x = -radius; x <= radius; ++x) {
      if (x * x + y * y < rsq) {
        SetPixel(cx + x, cy + y, pixel);
      }
    }
  }
}
void signi::Image::DrawPolygonFilled(std::vector<int> x, std::vector<int> y,
                                     Pixel pixel) {
  int min_y = y[0];
  int max_y = y[0];
  for (std::size_t i = 1; i < y.size(); ++i) {
    min_y = std::min(min_y, y[i]);
    max_y = std::max(max_y, y[i]);
  }
  for (int i = min_y; i <= max_y; i++) {
    std::vector<int> inter;
    for (std::size_t j = 0; j < x.size() && j < y.size(); j++) {
      std::size_t k = (j + 1) % std::min(x.size(), y.size());
      if (std::max(y[j], y[k]) > i && std::min(y[j], y[k]) <= i) {
        if (x[j] == x[k]) {
          inter.push_back(x[j]);
        } else {
          double m = static_cast<double>(y[k] - y[j]) / (x[k] - x[j]);
          inter.push_back(static_cast<int>((i - y[j] + (m * x[j])) / m));
        }
      }
    }
    std::sort(inter.begin(), inter.end());
    for (std::size_t a = 0; a < inter.size(); a += 2) {
      std::size_t b = (a + 1) % inter.size();
      DrawLine(inter[a], i, inter[b], i, pixel);
    }
  }
}
void signi::Image::DrawPolygonFilled(std::vector<std::array<int, 2>> points,
                                     Pixel pixel) {
  int min_y = points[0][1];
  int max_y = points[0][1];
  for (std::size_t i = 1; i < points.size(); ++i) {
    min_y = std::min(min_y, points[i][1]);
    max_y = std::max(max_y, points[i][1]);
  }
  min_y = std::max(min_y, 0);
  max_y = std::min(static_cast<std::size_t>(max_y), height_);
  for (int i = min_y; i <= max_y; i++) {
    std::vector<int> inter;
    for (std::size_t j = 0; j < points.size(); j++) {
      std::size_t k = (j + 1) % points.size();
      if (std::max(points[j][1], points[k][1]) > i &&
          std::min(points[j][1], points[k][1]) <= i) {
        if (points[j][0] == points[k][0]) {
          inter.push_back(points[j][0]);
        } else {
          double m = static_cast<double>(points[k][1] - points[j][1]) /
                     (points[k][0] - points[j][0]);
          inter.push_back(
              static_cast<int>((i - points[j][1] + (m * points[j][0])) / m));
        }
      }
    }
    std::sort(inter.begin(), inter.end());
    for (std::size_t a = 0; a < inter.size(); a += 2) {
      std::size_t b = (a + 1) % inter.size();
      DrawLine(inter[a], i, inter[b], i, pixel);
    }
  }
}

bool signi::operator==(const Pixel& lhs, const Pixel& rhs) {
  return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a);
}
double signi::PixelDiff(const Pixel& lhs, const Pixel& rhs) {
  return pow(lhs.r - rhs.r, 2) + pow(lhs.g - rhs.g, 2) + pow(lhs.b - rhs.b, 2);
}

signi::Pixel signi::HVS(const uint16_t &h, const double &s, const double &v){
  double c = v * s;
  double x = c * (1 - std::fabs(std::fmod((h / 60.0), 2.0) - 1));
  double m = v - c;
  double rp = 0.0, gp = 0.0, bp = 0.0;
  if(h < 60){
    rp = c; gp = x;
  }else if(h < 120){
    rp = x; gp = c;
  }else if(h < 180){
    gp = c; bp = x;
  }else if(h < 240){
    gp = x; bp = c;
  }else if(h < 300){
    rp = x; bp = c;
  }else if(h < 360){
    rp = c;
    bp = x;
  }
  return Pixel(rp + m, gp + m, bp + m);
}
