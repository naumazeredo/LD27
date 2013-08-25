#include "../SDL2/SDL_rect.h"
#include "../game.h"
#include "camera.h"

namespace nafw
{

Camera::Camera(Game* game) : game_(game), w_(game->GetWindowWidth()), h_(game->GetWindowHeight())
{
}

// Resize Camera
void Camera::SetSize(int w, int h)
{
  w_ = w;
  h_ = h;
}

// Reposition camera
void Camera::SetPosition(float x, float y)
{
  x_ = x;
  y_ = y;

  ApplyLimits();
}

// Move camera
void Camera::SetMovement(bool move)
{
  can_move_ = move;
}

void Camera::Move(float x, float y)
{
  x_ += x;
  y_ += y;

  ApplyLimits();
}

// Limit movement
void Camera::LimitHorizontal(float limit_left, float limit_right)
{
  limit_horizontal_ = true;
  limit_left_ = limit_left;
  limit_right_ = limit_right;
}

void Camera::LimitVertical(float limit_up, float limit_down)
{
  limit_vertical_ = true;
  limit_up_ = limit_up;
  limit_down_ = limit_down;
}

void Camera::SetLimit(bool horizontal, bool vertical)
{
  limit_horizontal_ = horizontal;
  limit_vertical_ = vertical;
}

void Camera::LookAt(float x, float y)
{
  x_ = x - w_ / 2.0f;
  y_ = y - h_ / 2.0f;

  ApplyLimits();
}

SDL_Rect Camera::ToSDL() const
{
  SDL_Rect rect {
    static_cast<int>(x_),
    static_cast<int>(y_),
    w_,
    h_
  };
  return rect;
}

void Camera::ApplyLimits()
{
  if (limit_horizontal_)
  {
    if (x_ < limit_left_) x_ = limit_left_;
    else if (x_ + w_ > limit_right_) x_ = limit_right_ - w_;
  }

  // TODO limit vertical
  /*
  if (limit_vertical_)
  {
    if (y_ < limit_up_)
  */
}

}

