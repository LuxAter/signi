#include "bmp.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include <estl/logger.hpp>

#include "image.hpp"

bool signi::BmpWrite(const std::string& file, const Image& img) {
  std::pair<std::size_t, std::size_t> size = img.GetSize();
  char padding_data[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned padding = (4 - ((size.first * 3) % 4)) % 4;

  unsigned info_size = (2 * sizeof(unsigned short)) + (9 * sizeof(unsigned));
  unsigned header_size = (3 * sizeof(unsigned short)) + (2 * sizeof(unsigned));

  unsigned i_size = info_size;
  unsigned i_width = size.first;
  unsigned i_height = size.second;
  unsigned short i_planes = 1;
  unsigned short i_bit_count = 24;
  unsigned i_compression = 0;
  unsigned i_image_size = (((size.first * 3) + 3) & 0x0000FFFC) * size.second;
  unsigned i_xpm = 0;
  unsigned i_ypm = 0;
  unsigned i_clru = 0;
  unsigned i_clri = 0;

  unsigned short h_type = 19778;
  unsigned h_size = header_size + info_size + i_image_size;
  unsigned short h_reserved1 = 0;
  unsigned short h_reserved2 = 0;
  unsigned h_off_bits = header_size + info_size;

  std::ofstream out(file.c_str(), std::ios::binary);
  if (out.is_open()) {
    uint8_t** byte_data = (uint8_t**)malloc(size.second * sizeof(uint8_t*));
    for (std::size_t i = 0; i < size.second; ++i) {
      byte_data[i] = (uint8_t*)malloc(3 * size.first * sizeof(uint8_t));
    }
    for (std::size_t x = 0; x < size.first; ++x) {
      for (std::size_t y = 0; y < size.second; ++y) {
        Pixel pixel = img.GetPixel(x, y);
        uint8_t red = pixel.r * 255 + 0.5;
        uint8_t green = pixel.g * 255 + 0.5;
        uint8_t blue = pixel.b * 255 + 0.5;
        std::size_t id = 3 * x;
        byte_data[y][id] = blue;
        byte_data[y][id + 1] = green;
        byte_data[y][id + 2] = red;
      }
    }
    out.write(reinterpret_cast<const char*>(&h_type), sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&h_size), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&h_reserved1),
              sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&h_reserved2),
              sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&h_off_bits), sizeof(unsigned));

    out.write(reinterpret_cast<const char*>(&i_size), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_width), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_height), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_planes), sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&i_bit_count),
              sizeof(unsigned short));
    out.write(reinterpret_cast<const char*>(&i_compression), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_image_size), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_xpm), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_ypm), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_clru), sizeof(unsigned));
    out.write(reinterpret_cast<const char*>(&i_clri), sizeof(unsigned));
    for (std::size_t i = 0; i < size.second; ++i) {
      out.write(reinterpret_cast<const char*>(byte_data[size.second - i - 1]),
                sizeof(uint8_t) * 3 * size.first);
    }
    for (std::size_t i = 0; i < size.second; ++i) {
      free(byte_data[i]);
    }
    free(byte_data);
    out.close();
  } else {
    estl::logger::Error("Failed to open file %s to write to", file.c_str());
    return false;
  }
  return true;
}

signi::Image signi::BmpRead(const std::string& file) {
  FILE* load = fopen(file.c_str(), "rb");
  if (!load) {
    estl::logger::Error("Failed to open file %s to read", file.c_str());
    return Image();
  }
  uint8_t info[54];
  fread(info, sizeof(uint8_t), 54, load);
  int width = *(int*)&info[18];
  int height = *(int*)&info[22];
  Image img(width, height);
  for (std::size_t y = 0; y < height; ++y) {
    for (std::size_t x = 0; x < width; ++x) {
      uint8_t rgb[3];
      fread(rgb, sizeof(uint8_t), 3, load);
      img.SetPixel(x, height- y - 1, {rgb[2], rgb[1], rgb[0]});
    }
  }
  fclose(load);
  return img;
}
