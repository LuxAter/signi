#ifndef SIGNI_BMP_HPP_
#define SIGNI_BMP_HPP_

#include "image.hpp"

namespace signi {
  bool BmpWrite(const std::string& file, const Image& img);
  Image BmpRead(const std::string& file);
}

#endif  // SIGNI_BMP_HPP_
