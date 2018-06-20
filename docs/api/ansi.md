# ANSI API #

```cpp
#include <signi/ansi.hpp>
```

This file allows the reading and writing to any ANSI compatable terminal, with
Unicode support.

# Enum #

* * *

## AnsiCharacter ##

The character for best results is `ANSI_HORIZONTAL`.

- `ANSI_BLOCK`
- `ANSI_DOBULE`
- `ANSI_SQUARE`
- `ANSI_VERTICAL`
- `ANSI_HORIZONTAL`

# Functions #

* * *

## AnsiWrite ##

```cpp
void signi::AnsiWrite(const std::string& file, const Image& img
                      AnsiCharacter character=ANSI_BLOCK);
```

Writes the image data stored in `img` to the file path specified by `file`. The
file data is writen as ANSI escape codes, such that printing the file using
`printf` or `echo` will cause the image to be displayed in the terminal.

- **file:** File path to write to.
- **img:** Image data to write to file.
- **character:** Character element to use as a pixel.

## AnsiWriteString ##

```cpp
std::string signi::AnsiWriteString(const Image& img,
                                   AnsiCharacter character=ANSI_BLOCK);
```
Writes the image data stored in `img` to a string that is then returned.

- **img:** Image data to write to string.
- **character:** Character element to use as a pixel.

**Returns:** String of escape sequences representing the image.

## AnsiRead ##

```cpp
signi::Image signi::AnsiRead(const std::string& file);
```

Reads the image data stored in the file specified by `file` to an
`signi::Image` object and then returns the image object.

- **file:** File path to read ansi from.

**Returns:** Image containing ANSI data.

## AnsiReadString ##

```cpp
signi::Image signi::AnsiReadString(const std::string& img);
```
Reads the image data stored in the string to a `signi::Image` object and then
returns the image object.

- **img:** Image string to parse.

**Returns:** Image containing ANSI data.
