/*
 *  Not Available Framework
 *
 *  Timer class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief: timer?
 *
 */

#ifndef NAFW_TIMER_H_
#define NAFW_TIMER_H_

#include <ctime>

#include "SDL2\SDL_timer.h"

namespace nafw
{

class Timer
{
 public:
  // Constructors
  Timer() : init_(0), current_(0), delta_(0), pause_(0), paused_(false) {}

  // Destructors
  ~Timer() {}

  // Mutators
  inline void Init() { this->init_ = SDL_GetTicks(); this->current_ = init_; this->paused_ = false; this->pause_ = 0; }
  void NextFrame()
  {
    if (this->paused_)
    {
      this->pause_ = SDL_GetTicks() - this->current_;
    }
    else
    {
      this->current_ += this->delta_;
      this->delta_ = SDL_GetTicks() - this->current_ - this->pause_;
    }
  }
  //inline void Step(int delta) { this->current_ += delta; }
  inline void Pause() { this->paused_ = true; }
  inline void Unpause() { this->paused_ = false; }

  // Accessors
  inline int GetDelta() const { return this->delta_; }
  inline int GetTime() const { return this->current_ + this->delta_; }
  inline bool IsPaused() const { return this->paused_; }
private:
  int init_, current_, delta_, pause_;
  bool paused_;
};

}

#endif//NAFW_TIMER_H_
