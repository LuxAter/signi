The `signi::Image` class in intended to just store and safely manipulate the
pixel data of an image. Reading and writing to different formats is done by
nonmember functions that take the image as an argument. This class should only
be used for manipulation of the pixel data.

[TOC]

* * *

# Constructor

```cpp
Image();
Image(std::size_t width, std::size_t height);
```

The basic image constructor takes dimensions of the image and nothing else. All
the constructor does is to initialize the pixel data array of the image.

# Graphics Primitives

* [Fill](#fill)
* [DrawPixel](#drawpixel)
* [DrawLine](#drawline)

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

## DrawTriangle ##

```cpp
void signi::Image::DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2,
                                Pixel pixel, int breadth);
```

DrawTriangle is used to draw a triangle of three points.

## DrawRectangle ##

```cpp
void signi::Image::DrawRectangle(int x, int y, int width, int height,
                                 Pixel pixel, int breadth);
```

## DrawCircle ##

```cpp
void signi::Image::DrawCircle(int cx, int cy, int radiux, Pixel pixel,
                              int breadth);
```

## DrawPolygon ##

```cpp
void signi::Image::DrawPolygon(std::vector<int> x, std::vector<int> y,
                               Pixel pixel, int breadth);
void signi::Image::DrawPolygon(std::vector<std::array<int, 2>> points,
                               Pixel pixel, int breadth);
```

## DrawTriangleFilled ##

```cpp
void signi::Image::DrawTriangleFilled(int x0, int y0, int x1, int y1, int x2,
                                      int y2, Pixel pixel);
```

## DrawrectangleFilled ##

```cpp
void signi::Image::DrawRectangleFilled(int x, int y, int width, int height,
                                       Pixel pixel);
```

## DrawCircleFilled ##

```cpp
void signi::Image::DrawCircleFilled(int cx, int cy, int radiux, Pixel pixel);
```

## DrawPolygonFilled ##

```cpp
void signi::Image::DrawPolygonFilled(std::vector<int> x, std::vector<int> y,
                                     Pixel pixel);
void signi::Image::DrawPolygonFilled(std::vector<std::array<int, 2>> points,
                                     Pixel pixel);
```
