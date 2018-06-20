# Signi

* * *

# Introduction

* * *

**Signi** is a C++ class based image handling system. It allows simple reading
and writing of image pixel data into many common formats. As well as the
ability to manipulate images through graphics primitives such as circles,
lines, rectangles, and polygons.

[TOC]

# Usage

* * *

Usage of the library is extremely simple. Below is a basic example.

```cpp
#include <signi/signi.hpp>

void main(){
  signi::Image img = signi::PngRead("test.png");
  signi::JpegWrite("out.jpeg", img);
  return 0;
}
```

Compile the program with

```fish
gcc main.cpp -lsigni
```

This program will read a PNG file called `test.png`, and then write a JPEG file
called `out.jpeg`. Simple as that to read and convert between different file
formats. To change the format, all that needs to be done is to change the
prefix on the functions. e.g. `signi::___Read` and `signi::___Write`.

# Building #

* * *

To build the library, clone the Github repository recursivly, then run Make.

```fish
git clone --recursive https://github.com/LuxAtrumStudio/signi
cd signi && make
```

This will build all the neccessary resources for the library. Then to install
the library just run

```fish
sudo make install
```
