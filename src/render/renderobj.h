/**
 *  Not Available Framework
 *
 *  Render Object
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Base abstract class for all sprites
 *
 */

#ifndef NAFW_RENDEROBJ_H_
#define NAFW_RENDEROBJ_H_

#include "interfaces.h"

namespace nafw
{

class Renderer;

class RenderObject : public IRenderObject
{
 public:
  RenderObject() {}
  //RenderObject(Renderer* renderer) : renderer_(renderer) {}
  virtual ~RenderObject() {}
 protected:
  // Renderer
  Renderer* renderer_ = nullptr;

  // Verify if object was created
  bool init_ = false;
};

}

#endif//NAFW_RENDEROBJ_H_

