#include "png.hpp"

#include <cmath>

#include <png.h>
#include <estl/logger.hpp>

#include "image.hpp"


bool signi::PngWrite(const std::string& file, const Image& img) {
  FILE* out = fopen(file.c_str(), "wb");
  if (!out) {
    return false;
  }
  png_structp png =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(out);
    return false;
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(out);
    return false;
  }
  if (setjmp(png_jmpbuf(png))) {
    fclose(out);
    return false;
  }
  std::pair<std::size_t, std::size_t> size = img.GetSize();
  uint8_t** byte_data = (png_bytepp)malloc(size.second * sizeof(png_bytep));
  for (std::size_t i = 0; i < size.second; ++i) {
    byte_data[i] = (png_bytep)malloc(6 * size.first * sizeof(png_byte));
  }
  for (std::size_t x = 0; x < size.first; ++x) {
    for (std::size_t y = 0; y < size.second; ++y) {
      Pixel pixel = img.GetPixel(x, y);
      unsigned red = pixel.r * 65535 + 0.5;
      unsigned green = pixel.g * 65535 + 0.5;
      unsigned blue = pixel.b * 65535 + 0.5;
      std::size_t id = 6 * x;
      byte_data[y][id] =
          static_cast<uint8_t>(std::floor(static_cast<double>(red) / 256.0));
      byte_data[y][id + 1] = static_cast<uint8_t>(red % 256);
      byte_data[y][id + 2] =
          static_cast<uint8_t>(std::floor(static_cast<double>(green) / 256.0));
      byte_data[y][id + 3] = static_cast<uint8_t>(green % 256);
      byte_data[y][id + 4] =
          static_cast<uint8_t>(std::floor(static_cast<double>(blue) / 256.0));
      byte_data[y][id + 5] = static_cast<uint8_t>(blue % 256);
    }
  }
  png_init_io(png, out);
  png_set_IHDR(png, info, size.first, size.second, 16, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT,
               PNG_FILTER_TYPE_DEFAULT);
  png_write_info(png, info);
  png_write_image(png, byte_data);
  png_write_end(png, NULL);
  png_free_data(png, info, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png, (png_infopp)NULL);
  fclose(out);
  return true;
}

signi::Image signi::PngRead(const std::string& file) {
  unsigned char header[8];
  FILE* load = fopen(file.c_str(), "rb");
  if (!load) {
    estl::logger::Error("File %s could not be opened", file.c_str());
    return Image();
  }
  fread(header, 1, 8, load);
  if (png_sig_cmp(header, 0, 8)) {
    estl::logger::Error("File %s is not recognized as a PNG file",
                        file.c_str());
    fclose(load);
    return Image();
  }
  png_structp png =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    estl::logger::Error("png_create_read_struct failed");
    fclose(load);
    return Image();
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    estl::logger::Error("png_create_infor_struct failed");
    fclose(load);
    return Image();
  }
  if (setjmp(png_jmpbuf(png))) {
    estl::logger::Error("Error during init_io");
    fclose(load);
    return Image();
  }

  png_init_io(png, load);
  png_set_sig_bytes(png, 8);

  png_read_info(png, info);

  int width = png_get_image_width(png, info);
  int height = png_get_image_height(png, info);
  png_byte color = png_get_color_type(png, info);
  png_byte depth = png_get_bit_depth(png, info);

  int passes = png_set_interlace_handling(png);
  png_read_update_info(png, info);

  if (setjmp(png_jmpbuf(png))) {
    estl::logger::Error("Error during read_image");
  }
  uint8_t** byte_data = (png_bytepp)malloc(height * sizeof(png_bytep));
  for (std::size_t i = 0; i < height; ++i) {
    byte_data[i] = (png_bytep)malloc(png_get_rowbytes(png, info));
  }
  png_read_image(png, byte_data);
  uint8_t step = 3;
  if(color == 0){
    step = 1;
  }else if(color == 2){
    step = 3;
  }else if(color == 4){
    step = 2;
  }else if(color == 6){
    step = 4;
  }
  if(depth == 16){
    step *= 2;
  }
  Image img(width, height);
  for (int row = 0; row < height; ++row) {
    for (int column = 0; column < width; ++column) {
      if (depth == 8) {
        img.SetPixel(column, row,
                     {(int)byte_data[row][step * column],
                      (int)byte_data[row][step * column + 1],
                      (int)byte_data[row][step * column + 2]});
      } else if (depth == 16) {
        img.SetPixel(column, row,
            {(static_cast<uint16_t>(byte_data[row][step * column + 1]) << 8) |
                 byte_data[row][step * column],
             (static_cast<uint16_t>(byte_data[row][step * column + 3]) << 8) |
                 byte_data[row][step * column + 2],
             (static_cast<uint16_t>(byte_data[row][step * column + 5]) << 8) |
                 byte_data[row][step * column + 4]});
      }
    }
  }
  return img;
}
