# JPEG API #

```cpp
#include <signi/jpeg.hpp>
```

This file allows the reading and writing to JPEG files.

# Functions #

* * *


## JpegWrite ##

```cpp
void signi::JpegWrite(const std::string& file, const Image& img);
```

Writes the image data stored in `img` to the file path specified by `file`.

- **file:** File path to write to.
- **img:** Image data to write to file.

## JpegRead ##

```cpp
signi::Image signi::JpegRead(const std::string& file);
```

Reads the image data stored in the file specified by `file` to an
`signi::Image` object and then returns the image object.

- **file:** File path to read jpeg from.

**Returns:** Image containing JPEG data.
