# BMP API #

```cpp
#include <signi/bmp.hpp>
```

This file allows the reading and writing to BMP files.

# Functions #

* * *


## BmpWrite ##

```cpp
void signi::BmpWrite(const std::string& file, const Image& img);
```

Writes the image data stored in `img` to the file path specified by `file`.

- **file:** File path to write to.
- **img:** Image data to write to file.

## BmpRead ##

```cpp
signi::Image signi::BmpRead(const std::string& file);
```

Reads the image data stored in the file specified by `file` to an
`signi::Image` object and then returns the image object.

- **file:** File path to read bmp from.

**Returns:** Image containing BMP data.
