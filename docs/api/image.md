# Image API

The `signi::Image` class in intended to just store and safely manipulate the
pixel data of an image. Reading and writing to different formats is done by
nonmember functions that take the image as an argument. This class should only
be used for manipulation of the pixel data.

[TOC]

* * *

# Constructor

* * *

```cpp
Image();
Image(std::size_t width, std::size_t height);
```

The basic image constructor takes dimensions of the image and nothing else. All
the constructor does is to initialize the pixel data array of the image.

# Data Access #

* * *

## GetPixelData ##

```cpp
const std::vector<std::vector<Pixel>>* GetPixelData() const;
```

GetPixelData retuns a pointer to the data vector. This is useful for using the
data to write to a file.

**Returns:** 2D vector containg pixel data.

## GetSize ##

```cpp
std::pair<std::size_t, std::size_t> GetSize() const;
```
GetSize returns the width and height of the image as a pair.

**Returns:** Pair containg (width, height).

## GetPixel ##

```cpp
const Pixel GetPixel(int x, int y) const;
```
GetPixel gets the pixel data for a single specified location. No bounds
checking is done on the data array.

- **x:** X position of pixel.
- **y:** Y position of pixel.

**Returns:** Pixel data at specified location.

# Graphics Primitives

 * * *

## Fill

```cpp
void signi::Image::Fill(Pixel pixel);
```

Fill is used to set all pixels of an image to a single color. It only takes a
single parameter.

-   **pixel:** Pixel data to apply to every pixel in the image.

## DrawPixel

```cpp
void signi::Image::DrawPixel(int x, int y, Pixel pixel, int breadth);
```

DrawPixel is used to set a single pixel in the image. Bounds checks are done on
the pixel, and if `breadth` is set, then a circle is drawn.

-   **x:** X position of pixel.
-   **Y:** Y position of pixel.
-   **pixel:** Pixel data to apply to pixel.
-   **breadth:** Area around pixel to also set.

## SetPixel ##

```cpp
void signi::Image::SetPixel(int x, int y, Pixel pixel);
```

SetPixel is used to set a single pixel in the image. Bounds checks are done on
the point. All other graphics calls (with the exception of `Fill`) results in a
call to SetPixel.

- **x:** X position of pixel.
- **y:** Y position of pixel.
- **pixel:** Pixel data to apply to pixel.

## DrawLine

```cpp
void signi::Image::DrawLine(int x0, int y0, int x1, int y1, Pixel pixel,
                            int breadth);
```

DrawLine is used to draw a rasterized line between two points. All points are
bound checked, and if `breadth` is set, then an area around the line is
drawn.

-   **x0:** Start x position.
-   **y0:** Start y position.
-   **x1:** End x position.
-   **y1:** End y position.
-   **pixel:** Pixel data to apply.
-   **breadth:** Area around line to also set.

## DrawTriangle

```cpp
void signi::Image::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2,
                                Pixel pixel, int breadth);
```

DrawTriangle is used to draw a triangle of three points. If `breadth` is set,
then an area around the line segments is also drawn.

-   **x0:** X of first point.
-   **y0:** Y of first point.
-   **x1:** X of second point.
-   **y1:** Y of second point.
-   **x2:** X of thrid point.
-   **y2** Y of third point.
-   **pixel:** Pixel data to apply.
-   **breadth:** Area around line to also set.

## DrawRectangle

```cpp
void signi::Image::DrawRectangle(int x, int y, int width, int height,
                                 Pixel pixel, int breadth);
```

DrawRectangle is used to draw a rectangle at given postion of given width and
height. If `breadth` is set, then an area around the line segments is also
drawn.

-   **x:** X position of the upper left corner of the rectangle.
-   **y:** Y position of the upper left corrner of the rectangle.
-   **width:** Width of the rectangle.
-   **height:** Height of the rectangle.
-   **pixel:** Pixel data to apply.
-   **breadth:** Area around line to also set.

## DrawCircle

```cpp
void signi::Image::DrawCircle(int cx, int cy, int radius, Pixel pixel,
                              int breadth);
```

DrawCircle is used to draw a circle centered at a given position with a given
radiux. If `breadth` is set, then an area around the circle is also drawn.

-   **x:** X position of the center of the circle.
-   **y:** Y position of the center of the circle.
-   **radius:** Radius of the circle.
-   **pixel:** Pixel data to apply.
-   **breadth:** Area around line to also set.

## DrawPolygon

```cpp
void signi::Image::DrawPolygon(std::vector<int> x, std::vector<int> y,
                               Pixel pixel, int breadth);
void signi::Image::DrawPolygon(std::vector<std::array<int, 2>> points,
                               Pixel pixel, int breadth);
```

DrawPolygon is used to draw an arbatrairy polygon connecting given points. If
`breadth` is set, then an area around the line segments is also drawn.

- **x:** Vector of X positions of points.
- **y:** Vector of Y positions of points.
- **points:** Vector of (x,y) pairs of points.
-   **pixel:** Pixel data to apply.
-   **breadth:** Area around line to also set.

## DrawTriangleFilled

```cpp
void signi::Image::DrawTriangleFilled(int x0, int y0, int x1, int y1, int x2,
                                      int y2, Pixel pixel);
```

DrawTriangleFilled is used to draw a filled triangle of three points. 

-   **x0:** X of first point.
-   **y0:** Y of first point.
-   **x1:** X of second point.
-   **y1:** Y of second point.
-   **x2:** X of thrid point.
-   **y2** Y of third point.
-   **pixel:** Pixel data to apply.

## DrawrectangleFilled

```cpp
void signi::Image::DrawRectangleFilled(int x, int y, int width, int height,
                                       Pixel pixel);
```
DrawRectangleFilled is used to draw a filled rectangle at given postion of
given width and height. 

-   **x:** X position of the upper left corner of the rectangle.
-   **y:** Y position of the upper left corrner of the rectangle.
-   **width:** Width of the rectangle.
-   **height:** Height of the rectangle.
-   **pixel:** Pixel data to apply.

## DrawCircleFilled

```cpp
void signi::Image::DrawCircleFilled(int cx, int cy, int radiux, Pixel pixel);
```
DrawCircleFilled is used to draw a filled circle centered at a given position
with a given radiux. 

-   **x:** X position of the center of the circle.
-   **y:** Y position of the center of the circle.
-   **radius:** Radius of the circle.
-   **pixel:** Pixel data to apply.

## DrawPolygonFilled

```cpp
void signi::Image::DrawPolygonFilled(std::vector<int> x, std::vector<int> y,
                                     Pixel pixel);
void signi::Image::DrawPolygonFilled(std::vector<std::array<int, 2>> points,
                                     Pixel pixel);
```
DrawPolygonFilled is used to draw an arbatrairy filled polygon connecting given
points. It uses a scanline algorithm to fill the polygons, and thus can result
in artifacts if a polygon has self intersection.

- **x:** Vector of X positions of points.
- **y:** Vector of Y positions of points.
- **points:** Vector of (x,y) pairs of points.
-   **pixel:** Pixel data to apply.
