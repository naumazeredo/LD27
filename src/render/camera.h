/**
 *  Not Available Framework
 *
 *  Camera
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Game viewport
 *
 */

#ifndef NAFW_RENDER_CAMERA_H_
#define NAFW_RENDER_CAMERA_H_

namespace nafw
{

class Game;

class Camera
{
 public:
  // Constructor
  Camera(Game* game);
  Camera(const Camera&) = default;
  Camera(Camera&) = default;
  Camera& operator=(const Camera&) = default;
  Camera& operator=(Camera&) = default;
  ~Camera() {}

  // Resize camera
  // TODO change renderer logical size (SDL_RenderSetLogicalSize(SDL_Renderer*, int, int))
  void SetSize(int w, int h);

  // Reposition camera
  void SetPosition(float x, float y);

  // Move camera
  void SetMovement(bool move);
  void Move(float x, float y);

  // Limit movement
  void LimitHorizontal(float limit_left, float limit_right);
  void LimitVertical(float limit_up, float limit_down);
  void SetLimit(bool horizontal, bool vertical);

  // Look at point
  // TODO follow object
  void LookAt(float x, float y);

  // SDL_Rect
  SDL_Rect ToSDL() const;

 private:
  // 
  void ApplyLimits();

  // Game parent
  Game* game_;

  // Viewport
  float x_=0, y_=0;
  int w_, h_;

  // Camera movement
  bool can_move_ = false;

  // Move limits (right -> x + w) (down -> y + h)
  bool limit_horizontal_ = false;
  bool limit_vertical_ = false;
  float limit_left_, limit_right_,
    limit_up_, limit_down_;
};

}

#endif//NAFW_RENDER_CAMERA_H_
