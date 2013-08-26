#include <cstdio>
#include "../SDL2/SDL_ttf.h"
#include "font.h"

namespace nafw
{

Font::~Font()
{
  if (font_ != nullptr)
    TTF_CloseFont(font_);
}

// Load
bool Font::Load()
{
  font_ = TTF_OpenFont("assets/font.ttf", 12);
  if (font_ == nullptr)
  {
    printf("Could not load font! SDL ttf error: %s\n", TTF_GetError());
    return false;
  }

  return true;
}

}

