/**
 *  Not Available Framework
 *
 *  Texture Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Holds texture info, like width and height,
 *    Manages texture pointer, erasing pointer on destruction
 *
 */

#ifndef NAFW_RENDER_TEXTURE_H_
#define NAFW_RENDER_TEXTURE_H_

#include <string>
#include "../SDL2/SDL_stdinc.h"
#include "../SDL2/SDL_rect.h"
#include "../SDL2/SDL_render.h"

struct SDL_Texture;

namespace nafw
{
class Renderer;

/**
 *  Texture class
 */
class Texture
{
 public:
  // Constructor and Destructor
  explicit Texture(Renderer* renderer) : renderer_(renderer) {}
  ~Texture();

  // Rule of 'three'
  Texture(const Texture&) = default;
  Texture(Texture&&) = default;
  Texture& operator=(const Texture&) & = default;
  Texture& operator=(Texture&&) & = default;

  // Mutators
  bool Load(std::string path);
  void SetColor(Uint8 r, Uint8 g, Uint8 b);
  void SetBlendMode(SDL_BlendMode blending);
  void SetAlpha(Uint8 alpha);
  void Free();

  // Accessors
  inline int GetWidth() const { return width_; }
  inline int GetHeight() const { return height_; }
  inline std::string GetPath() const { return path_; }
  SDL_Texture* GetTexture();
 public:
  // Renderer
  Renderer* renderer_;

  // Hardware texture
  SDL_Texture* texture_;

  // Texture path
  std::string path_;

  // Image dimensions
  int width_=0, height_=0;

  // Verifiers
  bool loaded_=false;
};

}

#endif//NAFW_RENDER_TEXTURE_H_
