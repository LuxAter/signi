#ifndef SIGNI_ANSI_HPP_
#define SIGNI_ANSI_HPP_

#include "image.hpp"
// #include "pixel.hpp"

namespace signi {
  enum AnsiCharacter {
    ANSI_BLOCK,
    ANSI_DOUBLE,
    ANSI_SQUARE,
    ANSI_VERTICAL,
    ANSI_HORIZONTAL,
  };
  bool AnsiWrite(const std::string& file, const Image& img, AnsiCharacter= ANSI_BLOCK);
  std::string AnsiWriteString(const Image& img, AnsiCharacter = ANSI_BLOCK);
  Image AnsiRead(const std::string& file);
  Image AnsiReadString(const std::string& img);
}  // namespace signi

#endif  // SIGNI_ANSI_HPP_
