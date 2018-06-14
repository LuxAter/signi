#ifndef SIGNI_JPEG_HPP_
#define SIGNI_JPEG_HPP_

#include "image.hpp"

namespace signi {
  bool JpegWrite(const std::string& file, const Image& img);
  Image JpegRead(const std::string& file);
} // namespace signi

#endif  // SIGNI_JPEG_HPP_
