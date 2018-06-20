# PNG API #

```cpp
#include <signi/png.hpp>
```

This file allows the reading and writing to PNG files.

# Functions #

* * *


## PngWrite ##

```cpp
void signi::PngWrite(const std::string& file, const Image& img);
```

Writes the image data stored in `img` to the file path specified by `file`.

- **file:** File path to write to.
- **img:** Image data to write to file.

## PngRead ##

```cpp
signi::Image signi::PngRead(const std::string& file);
```

Reads the image data stored in the file specified by `file` to an
`signi::Image` object and then returns the image object.

- **file:** File path to read png from.

**Returns:** Image containing PNG data.
