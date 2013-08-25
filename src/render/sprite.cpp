#include "../SDL2/SDL_assert.h"
#include "../SDL2/SDL_rect.h"
#include "sprite.h"
#include "texture.h"
#include "renderobj.h"
#include "renderer.h"
#include "geom.h"

namespace nafw
{

Sprite::~Sprite()
{
  Free();
}

void Sprite::Create(Renderer* renderer, std::string tex_path)
{
  renderer_ = renderer;
  texture_ = renderer->LoadTexture(tex_path);
  Free();
  is_flipped_ = false;
  init_ = true;
}

void Sprite::AddClip(const Rect* clip, const Point* center, bool flipped)
{
  SDL_assert(init_);
  Free();
  if (clip != nullptr)
  {
    clip_ = new Rect(*clip);
  }

  if (center != nullptr)
  {
    center_ = new Point(*center);
  }

  is_flipped_ = flipped;
}

void Sprite::SetScale(float scale) { scale_ = scale; }
void Sprite::SetRotation(double angle) { angle_ = angle; }

void Sprite::Draw(int x, int y, float depth)
{
  SDL_assert(init_);
  renderer_->DrawTexture(texture_, Point(x, y), clip_, scale_, center_, angle_, is_flipped_);
}

void Sprite::GetSize(int* w, int* h)
{
  SDL_assert(init_);
  if (clip_ != nullptr)
  {
    if (w != nullptr) *w = clip_->w;
    if (h != nullptr) *h = clip_->h;
  }
  else
  {
    if (w != nullptr) *w = texture_->w();
    if (h != nullptr) *h = texture_->h();
  }
}

void Sprite::Free()
{
  if (clip_ != nullptr) delete clip_;
  clip_ = nullptr;

  if (center_ != nullptr) delete center_;
  center_ = nullptr;
}

}

