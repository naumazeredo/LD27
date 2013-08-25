#include "../SDL2/SDL_assert.h"
#include "../SDL2/SDL_rect.h"
#include "animatedsprite.h"
#include "texture.h"
#include "renderobj.h"
#include "renderer.h"
#include "geom.h"

namespace nafw
{

AnimatedSprite::~AnimatedSprite()
{
  Free();
}

void AnimatedSprite::Create(Renderer* renderer, std::string tex_path)
{
  renderer_ = renderer;
  texture_ = renderer->LoadTexture(tex_path);
  Free();
  init_ = true;
}

void AnimatedSprite::AddClip(const Rect* clip, const Point* center, bool flipped)
{
  SDL_assert(init_);

  Rect* newclip = nullptr;
  if (clip != nullptr) newclip = new Rect(*clip);
  clip_.push_back(newclip);

  Point* newcenter = nullptr;
  if (center != nullptr) newcenter = new Point(*center);
  center_.push_back(newcenter);

  is_flipped_.push_back(flipped);

  ++num_clips_;
}

void AnimatedSprite::SetScale(float scale) { scale_ = scale; }
void AnimatedSprite::SetRotation(double angle) { angle_ = angle; }

void AnimatedSprite::AddFrame(unsigned int clip_index, unsigned int duration)
{
    SDL_assert(clip_index < num_clips_);

    frame_clip_.push_back(clip_index);
    frame_duration_.push_back(duration);
  }

  void AnimatedSprite::SetAnimationLoop(bool loop)
  {
    loop_ = loop;
  }

  void AnimatedSprite::PlayAnimation()
  {
    playing_ = true;
  }

  void AnimatedSprite::PauseAnimation()
  {
    playing_ = false;
  }

  void AnimatedSprite::StopAnimation()
  {
    playing_ = false;
    current_frame_ = 0;
    current_time_ = 0;
  }

  void AnimatedSprite::Step(unsigned int delta)
  {
    SDL_assert(!frame_clip_.empty());

    current_time_ += delta;
  while (current_time_ >= frame_duration_[current_frame_])
  {
    current_time_ -= frame_duration_[current_frame_];
    ++current_frame_;
    if (current_frame_ >= frame_clip_.size())
    {
      current_frame_ = 0;
      if (!loop_)
        StopAnimation();
    }
  }
}

void AnimatedSprite::Draw(int x, int y, float depth)
{
  SDL_assert(init_);
  SDL_assert(!frame_clip_.empty());
  //renderer_->DrawTexture(texture_, Point(x, y), clip_[current_frame_], scale_, center_[current_frame_], angle_, is_flipped_[current_frame_]);
  unsigned int current_clip = frame_clip_[current_frame_];
  renderer_->DrawTexture(texture_, Point(x, y), clip_[current_clip], scale_, center_[current_clip], angle_, is_flipped_[current_clip]);
}

void AnimatedSprite::Free()
{
  if (clip_.size() > 0)
    for (auto& it : clip_)
      if (it != nullptr)
        delete it;
  clip_.clear();

  if (center_.size() > 0)
    for (auto& it : center_)
      if (it != nullptr)
        delete it;
  center_.clear();

  num_clips_ = 0;
  current_frame_ = 0;

  is_flipped_.clear();
  frame_clip_.clear();
  frame_duration_.clear();
}

}

