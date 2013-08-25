/**
 *  Game Object base class
 *
 */

#ifndef LD_GAMEOBJ_H_
#define LD_GAMEOBJ_H_

#include <cstdio>

class GameObject
{
 public:
  // Constructor
  GameObject() {};

  // Getters
  inline float x() const { return x_; }
  inline float y() const { return y_; }

  // Reposition
  void SetPosition(float x, float y)
  {
    x_ = x;
    y_ = y;
  }

  virtual void Move(float x, float y=0)
  {
    x_ += x;
    y_ += y;

    if (x > 0) facing_ = DIRECTION_RIGHT;
    else if (x < 0) facing_ = DIRECTION_LEFT;
    // x can be 0, so it maintains last direction
  }

  // Visibility
  inline void set_visible(bool visible) { visible_ = visible; }
  inline bool visible() { return visible_; }

  // Draw function
  virtual void Draw(float depth = 0.0f)=0;

 protected:
  // Initialized
  bool init_ = false;

  // Position
  float x_=0, y_=0;

  // Direction
  enum Direction
  {
    DIRECTION_RIGHT=0,
    DIRECTION_LEFT
  };

  Direction facing_ = DIRECTION_RIGHT;

  // Visibility
  bool visible_ = true;
};

#endif//LD_GAMEOBJ_H_
