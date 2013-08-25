/**
 *  Not Available Framework
 *
 *  Constants
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 */

#ifndef NAFW_RENDER_CONSTANTS_H_
#define NAFW_RENDER_CONSTANTS_H_

#include "../SDL2/SDL_video.h"

namespace nafw
{

namespace Color
{
  const SDL_Color white {0xFF, 0xFF, 0xFF};
  const SDL_Color black {0x00, 0x00, 0x00};
  const SDL_Color blue {0x00, 0x00, 0xFF};
  const SDL_Color green {0x00, 0xFF, 0x00};
  const SDL_Color red {0xFF, 0x00, 0x00};
  const SDL_Color magenta {0xFF, 0x00, 0xFF};
}

}

#endif//NAFW_RENDER_CONSTANTS_H_

