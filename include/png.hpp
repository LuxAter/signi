#ifndef SIGNI_PNG_HPP_
#define SIGNI_PNG_HPP_

#include "image.hpp"

namespace signi {
  bool PngWrite(const std::string& file, const Image& img);
  Image PngRead(const std::string& file);
} // namespace signi

#endif  // SIGNI_PNG_HPP_
