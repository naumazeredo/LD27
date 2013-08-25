/**
 *  Not Available Framework
 *
 *  Sprite Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief A texture clipped and even animated,
 *    controlling clip rect and flipping
 *
 */

#ifndef NAFW_RENDER_SPRITE_H_
#define NAFW_RENDER_SPRITE_H_

#include <string>
#include "interfaces.h"
#include "renderobj.h"

namespace nafw
{

class Point;
class Rect;
class Texture;

class Sprite : public RenderObject, public ISprite
{
 public:
  // Constructors and Destructors
  Sprite() {}

  Sprite(const Sprite&) = default;
  Sprite(Sprite&&) = default;
  Sprite& operator=(const Sprite&) = default;
  Sprite& operator=(Sprite&&) = default;
  ~Sprite();

  // ISprite
  virtual void Create(Renderer* renderer, std::string tex_path) override;
  virtual void AddClip(const Rect* clip, const Point* center, bool flipped) override;
  virtual void SetScale(float scale) override;
  virtual void SetRotation(double angle) override;

  // IRenderObject
  virtual void Draw(int x, int y, float depth = 0.0f) override;

  //
  void GetSize(int* w, int* h);

 private:
  void Free();

  // Texture settings
  Texture* texture_ = nullptr;
  Rect* clip_ = nullptr;
  Point* center_ = nullptr;

  float scale_ = 1.0f;
  double angle_ = 0.0f;

  bool is_flipped_ = false;  // Horizontal flip (XXX do vertical flip?)
};

}

#endif//NAFW_RENDER_SPRITE_H_
