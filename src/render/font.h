/**
 *  Not Available Framework
 *
 *  Font
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \thanks Lazyfoo
 *
 */

#ifndef NAFW_RENDER_FONT_H_
#define NAFW_RENDER_FONT_H_

#include "../SDL2/SDL_ttf.h"

namespace nafw
{

class Font
{
 public:
  // Constructor
  Font(){}
  ~Font();

  // Load
  bool Load();

  // Get
  inline TTF_Font* font() const { return font_; }

 private:
  // Font
  TTF_Font* font_;
};

}

#endif//NAFW_RENDER_FONT_H_

