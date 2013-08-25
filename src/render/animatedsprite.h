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

#ifndef NAFW_RENDER_ANIMATEDSPRITE_H_
#define NAFW_RENDER_ANIMATEDSPRITE_H_

#include <string>
#include <vector>
#include "interfaces.h"
#include "renderobj.h"

namespace nafw
{

class Point;
class Rect;
class Texture;

// Animated Sprite
class AnimatedSprite : public RenderObject, public ISprite, public IAnimation
{
 public:
  // Constructors and Destructors
  AnimatedSprite() {};

  AnimatedSprite(const AnimatedSprite&) = default;
  AnimatedSprite(AnimatedSprite&&) = default;
  AnimatedSprite& operator=(const AnimatedSprite&) = default;
  AnimatedSprite& operator=(AnimatedSprite&&) = default;
  ~AnimatedSprite();

  // ISprite
  virtual void Create(Renderer* renderer, std::string tex_path) override;
  virtual void AddClip(const Rect* clip, const Point* center, bool flipped) override;
  virtual void SetScale(float scale) override;
  virtual void SetRotation(double angle) override;

  // IAnimation
  virtual void AddFrame(unsigned int clip_index, unsigned int duration) override;
  virtual void SetAnimationLoop(bool loop) override;
  virtual void PlayAnimation() override;
  virtual void PauseAnimation() override;
  virtual void StopAnimation() override;

  // IStep
  virtual void Step(int delta) override;

  // IRenderObject
  virtual void Draw(int x, int y, float depth = 0.0f) override;

 private:
  void Free();

  // Texture settings
  // FIXME animatedsprite can have multiple texture, I'm doing with only one
  Texture* texture_ = nullptr;
  std::vector<Rect*> clip_;
  std::vector<Point*> center_;
  std::vector<bool> is_flipped_;  // Horizontal flip (XXX do vertical flip?)
  unsigned int num_clips_ = 0;

  // TODO add frame order list to animation
  unsigned int current_frame_ = 0;
  unsigned int current_time_ = 0;
  std::vector<unsigned int> frame_clip_;
  std::vector<unsigned int> frame_duration_;
  bool playing_ = true;
  bool loop_ = false;

  float scale_ = 1.0f;
  double angle_ = 0.0f;
};

}

#endif//NAFW_RENDER_ANIMATEDSPRITE_H_
