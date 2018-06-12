#include "ansi.hpp"

#include <algorithm>
#include <bitset>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <estl/basic/format.hpp>
#include <estl/logger.hpp>

#include "image.hpp"

std::vector<std::string> split(const std::string& s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> tokens;
  while (getline(ss, item, delim)) {
    tokens.push_back(item);
  }
  return tokens;
}
int CountSubstring(const std::string& str, const std::string& sub) {
  if (sub.length() == 0) return 0;
  int count = 0;
  for (size_t offset = str.find(sub); offset != std::string::npos;
       offset = str.find(sub, offset + sub.length())) {
    ++count;
  }
  return count;
}

bool signi::AnsiWrite(const std::string& file, const Image& img,
                      AnsiCharacter character) {
  std::ofstream out(file.c_str());
  if (out.is_open()) {
    out << AnsiWriteString(img, character);
  }
}

std::string signi::AnsiWriteString(const Image& img, AnsiCharacter character) {
  std::string result;
  const std::vector<std::vector<Pixel>>* pixel_data = img.GetPixelData();
  std::pair<std::size_t, std::size_t> size = img.GetSize();
  switch (character) {
    case ANSI_BLOCK: {
      for (std::size_t y = 0; y < size.second; ++y) {
        for (std::size_t x = 0; x < size.first; ++x) {
          std::array<uint8_t, 4> rgba = pixel_data->at(x).at(y).GetInt();
          result += estl::base::format("\033[38;2;%d;%d;%dm\u2588\033[0m",
                                       rgba[0], rgba[1], rgba[2]);
        }
        result += "\n";
      }
      break;
    }
    case ANSI_DOUBLE: {
      for (std::size_t y = 0; y < size.second; ++y) {
        for (std::size_t x = 0; x < size.first; ++x) {
          std::array<uint8_t, 4> rgba = pixel_data->at(x).at(y).GetInt();
          result += estl::base::format("\033[38;2;%d;%d;%dm\u2588\u2588\033[0m",
                                       rgba[0], rgba[1], rgba[2]);
        }
        result += "\n";
      }
      break;
    }
    case ANSI_SQUARE: {
      for (std::size_t y = 0; y < size.second; ++y) {
        for (std::size_t x = 0; x < size.first; ++x) {
          std::array<uint8_t, 4> rgba = pixel_data->at(x).at(y).GetInt();
          result += estl::base::format("\033[38;2;%d;%d;%dm\u25A0\033[0m",
                                       rgba[0], rgba[1], rgba[2]);
        }
        result += "\n";
      }
      break;
    }
    case ANSI_VERTICAL: {
      for (std::size_t y = 0; y < size.second; ++y) {
        for (std::size_t x = 0; x < size.first; x += 2) {
          std::array<uint8_t, 4> rgba = pixel_data->at(x).at(y).GetInt();
          std::array<uint8_t, 4> b_rgba = pixel_data->at(x + 1).at(y).GetInt();
          result += estl::base::format(
              "\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm\u258C\033[0m", rgba[0],
              rgba[1], rgba[2], b_rgba[0], b_rgba[1], b_rgba[2]);
        }
        result += "\n";
      }
      break;
    }
    case ANSI_HORIZONTAL: {
      for (std::size_t y = 0; y < size.second; y += 2) {
        for (std::size_t x = 0; x < size.first; ++x) {
          std::array<uint8_t, 4> rgba = pixel_data->at(x).at(y).GetInt();
          std::array<uint8_t, 4> b_rgba = pixel_data->at(x).at(y + 1).GetInt();
          result += estl::base::format(
              "\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm\u2580\033[0m", rgba[0],
              rgba[1], rgba[2], b_rgba[0], b_rgba[1], b_rgba[2]);
        }
        result += "\n";
      }
      break;
    }
  }
  return result;
}

signi::Image signi::AnsiRead(const std::string& file) {}

signi::Image signi::AnsiReadString(const std::string& img) {
  std::string first_line = split(img, '\n')[0];
  bool vertical = first_line.find("\u258c") != std::string::npos;
  bool horizontal = first_line.find("\u2580") != std::string::npos;
  std::string character = "\u2588";
  if (vertical) {
    character = "\u258c";
  } else if (horizontal) {
    character = "\u2580";
  } else if (first_line.find("\u25A0") != std::string::npos) {
    character = "\u25A0";
  } else if (first_line.find("\u2588\u2588") != std::string::npos) {
    character = "\u2588\u2588";
  }
  std::size_t width =
                  CountSubstring(first_line, character) * (vertical ? 2 : 1),
              height = split(img, '\n').size() * (horizontal ? 2 : 1);
  Pixel fg, bg;
  Image res(width, height);
  int y = 0;
  for (auto line : split(img, '\n')) {
    int x = 0;
    for (auto block : split(line, '\033')) {
      uint8_t state = 0;
      // std::cout << block << "::";
      for (auto entry : split(block, ';')) {
        if (entry == "[38") {
          state = 1;
        } else if (entry == "[48") {
          state = 2;
        } else if (entry == "2" && (state == 1 || state == 2)) {
          state += 2;
        } else if (state == 3) {
          fg.r = stoi(entry) / 255.0;
          state += 2;
        } else if (state == 4) {
          bg.r = stoi(entry) / 255.0;
          state += 2;
        } else if (state == 5) {
          fg.g = stoi(entry) / 255.0;
          state += 2;
        } else if (state == 6) {
          bg.g = stoi(entry) / 255.0;
          state += 2;
        } else if (state == 7) {
          fg.b = stoi(entry.substr(0, entry.find('m'))) / 255.0;
          if (entry.back() != 'm') {
            std::string ch = entry.substr(entry.find('m') + 1);
            if (ch == "\u2588" || ch == "\u2588\u2588" || ch == "\u25A0") {
              // std::cout << (int)fg.GetInt()[0] << "," << (int)fg.GetInt()[1]
              //           << "," << (int)fg.GetInt()[2] << "\n";
              res.SetPixel(x, y, fg);
              x++;
              // std::cout << "(" << x << ',' << y << ")\n";
            } else if (ch == "\u258C") {
              res.SetPixel(x, y, fg);
              x++;
              res.SetPixel(x, y, bg);
              x++;
            } else if (ch == "\u2580") {
              res.SetPixel(x, y, fg);
              res.SetPixel(x, y + 1, bg);
              x++;
            }
          }
          state = 0;
        } else if (state == 8) {
          bg.b = stoi(entry.substr(0, entry.find('m'))) / 255.0;
          if (entry.back() != 'm') {
            std::string ch = entry.substr(entry.find('m') + 1);
            if (ch == "\u2588" || ch == "\u2588\u2588" || ch == "\u25A0") {
              // std::cout << (int)fg.GetInt()[0] << "," << (int)fg.GetInt()[1]
              //           << "," << (int)fg.GetInt()[2] << "\n";
              res.SetPixel(x, y, fg);
              x++;
              // std::cout << "(" << x << ',' << y << ")\n";
            } else if (ch == "\u258C") {
              res.SetPixel(x, y, fg);
              x++;
              res.SetPixel(x, y, bg);
              x++;
            } else if (ch == "\u2580") {
              res.SetPixel(x, y, fg);
              res.SetPixel(x, y + 1, bg);
              x++;
            }
          }
          state = 0;
        }
      }
    }
    y++;
    if (horizontal) {
      y++;
    }
  }
  return res;
}
