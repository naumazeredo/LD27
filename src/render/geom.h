/**
 *  Not Available Framework
 *
 *  Geometry
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief All geometry classes
 *
 */

#ifndef NAFW_GEOM_H_
#define NAFW_GEOM_H_

namespace nafw
{

class Point
{
 public:
  Point() : x(0), y(0) {}
  Point(int x, int y) : x(x), y(y) {}

  Point(const Point&) = default;
  Point(Point&&) = default;
  Point& operator=(const Point&) = default;
  Point& operator=(Point&&) = default;
  ~Point() {}

  SDL_Point ToSDL() const
  {
    SDL_Point point {x, y};
    return point;
  }

  int x, y;
};

class Rect
{
 public:
  Rect() : x(0), y(0), w(0), h(0) {}
  Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}

  Rect(const Rect&) = default;
  Rect(Rect&&) = default;
  Rect& operator=(const Rect&) = default;
  Rect& operator=(Rect&&) = default;
  ~Rect() {}

  SDL_Rect ToSDL() const
  {
    SDL_Rect rect {x, y, w, h};
    return rect;
  }

  int x, y, w, h;
};

}

#endif//NAFW_GEOM_H_
