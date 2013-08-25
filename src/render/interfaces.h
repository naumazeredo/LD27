/**
 *  Not Available Framework
 *
 *  Interfaces
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Declare all interfaces related to render
 *
 */

#ifndef NAFW_INTERFACES_H_
#define NAFW_INTERFACES_H_

#include <string>

#define interface class

namespace nafw
{
class Point;
class Rect;
class Renderer;

interface ISteppable
{
 public:
  virtual void Step(int delta)=0;
};

interface ISprite
{
 public:
  virtual void Create(Renderer* renderer, std::string tex_path)=0;
  virtual void AddClip(const Rect* clip, const Point* center, bool flipped)=0;
  virtual void SetScale(float scale)=0;
  virtual void SetRotation(double angle)=0;
};

interface IAnimation : public ISteppable
{
 public:
  virtual void AddFrame(unsigned int clip_index, unsigned int delta);
  virtual void SetAnimationLoop(bool loop)=0;
  virtual void PlayAnimation()=0;
  virtual void PauseAnimation()=0;
  virtual void StopAnimation()=0;
};

interface IRenderObject
{
 public:
  virtual void Draw(int x, int y, float depth =0.0f)=0;
};

};

#endif//NAFW_INTERFACES_H_
