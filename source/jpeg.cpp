#include "jpeg.hpp"

#include <cmath>

#include <jpeglib.h>
#include <estl/logger.hpp>

#include "image.hpp"

bool signi::JpegWrite(const std::string& file, const Image& img) {
  FILE* out = fopen(file.c_str(), "wb");
  if (!out) {
    return false;
  }
  struct jpeg_compress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_compress(&cinfo);
  jpeg_stdio_dest(&cinfo, out);
  cinfo.image_width = img.GetSize().first;
  cinfo.image_height = img.GetSize().second;
  cinfo.input_components = 3;
  cinfo.in_color_space = JCS_RGB;
  jpeg_set_defaults(&cinfo);
  jpeg_start_compress(&cinfo, true);
  uint8_t** byte_data =
      (uint8_t**)malloc(cinfo.image_height * sizeof(uint8_t*));
  for (std::size_t i = 0; i < cinfo.image_height; ++i) {
    byte_data[i] = (uint8_t*)malloc(3 * cinfo.image_width * sizeof(uint8_t));
  }
  for (std::size_t x = 0; x < cinfo.image_width; ++x) {
    for (std::size_t y = 0; y < cinfo.image_height; ++y) {
      Pixel pixel = img.GetPixel(x, y);
      uint8_t red = pixel.r * 255 + 0.5;
      uint8_t green = pixel.g * 255 + 0.5;
      uint8_t blue = pixel.b * 255 + 0.5;
      std::size_t id = 3 * x;
      byte_data[y][id] = red;
      byte_data[y][id + 1] = green;
      byte_data[y][id + 2] = blue;
    }
  }
  jpeg_write_scanlines(&cinfo, byte_data, cinfo.image_height);
  jpeg_finish_compress(&cinfo);
  for (std::size_t i = 0; i < cinfo.image_height; ++i) {
    free(byte_data[i]);
  }
  free(byte_data);
  jpeg_destroy_compress(&cinfo);
  fclose(out);
  return true;
}

signi::Image signi::JpegRead(const std::string& file) {
  FILE* load = fopen(file.c_str(), "rb");
  if (!load) {
    estl::logger::Error("File %s could not be opened", file.c_str());
    return Image();
  }
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, load);
  jpeg_read_header(&cinfo, true);
  jpeg_start_decompress(&cinfo);
  uint8_t** byte_data =
      (uint8_t**)malloc(cinfo.output_height * sizeof(uint8_t*));
  for (std::size_t i = 0; i < cinfo.output_height; ++i) {
    byte_data[i] = (uint8_t*)malloc(3 * cinfo.output_width * sizeof(uint8_t));
  }
  uint8_t* line[1];
  while(cinfo.output_scanline < cinfo.output_height){
    line[0] = byte_data[cinfo.output_scanline];
    jpeg_read_scanlines(&cinfo, line, 1);
  }
  Image img(cinfo.output_width, cinfo.output_height);
  uint8_t step = 3;
  for (int row = 0; row < cinfo.output_height; ++row) {
    for (int column = 0; column < cinfo.output_width; ++column) {
      img.SetPixel(column, row,
                   {(int)byte_data[row][step * column],
                    (int)byte_data[row][step * column + 1],
                    (int)byte_data[row][step * column + 2]});
    }
  }
  for (std::size_t i = 0; i < cinfo.image_height; ++i) {
    free(byte_data[i]);
  }
  free(byte_data);
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(load);
  return img;
}
