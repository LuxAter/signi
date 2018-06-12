#ifndef SIGNI_IMAGE_HPP_
#define SIGNI_IMAGE_HPP_

#include <array>
#include <vector>

namespace signi {
  struct Pixel {
    Pixel() : r(0.0), g(0.0), b(0.0), a(1.0) {}
    Pixel(int red, int green, int blue)
        : r(red / 255.0), g(green / 255.0), b(blue / 255.0), a(1.0) {}
    Pixel(double red, double green, double blue)
        : r(red), g(green), b(blue), a(1.0) {}

    inline std::array<uint8_t, 4> GetInt() const {
      return std::array<uint8_t, 4>{
          {static_cast<uint8_t>(r * 255), static_cast<uint8_t>(g * 255),
           static_cast<uint8_t>(b * 255), static_cast<uint8_t>(a * 255)}};
    }
    inline int GetValue() const { return ((65025 * r) + (255 * g) + (b)); }

    double r, g, b, a;
  };
  class Image {
   public:
    Image();
    Image(std::size_t width, std::size_t height);
    virtual ~Image();

    inline const std::vector<std::vector<Pixel>>* GetPixelData() const {
      return &pixel_data_;
    }
    inline std::pair<std::size_t, std::size_t> GetSize() const {
      return std::make_pair(width_, height_);
    }

    inline void SetPixel(int x, int y, Pixel pixel);

    void Fill(Pixel pixel);

    void DrawLineLow(int x0, int y0, int x1, int y1, Pixel pixel);
    void DrawLineHigh(int x0, int y0, int x1, int y1, Pixel pixel);
    void DrawPixel(int x, int y, Pixel pixel);
    void DrawLine(int x0, int y0, int x1, int y1, Pixel pixel, int breadth = 1);
    void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2,
                      Pixel pixel, int breadth = 1);
    void DrawRectangle(int x, int y, int width, int height, Pixel pixel,
                       int breadth = 1);
    void DrawPolygon(std::vector<int> x, std::vector<int> y, Pixel pixel,
                     int breadth = 1);
    void DrawPolygon(std::vector<std::array<int, 2>> points, Pixel pixel,
                     int breadth = 1);

   private:
    std::size_t width_, height_;
    std::vector<std::vector<Pixel>> pixel_data_;
  };
  bool operator==(const Pixel& lhs, const Pixel& rhs);
  double PixelDiff(const Pixel& lhs, const Pixel& rhs);
}  // namespace signi

#endif  // SIGNI_IMAGE_HPP_
