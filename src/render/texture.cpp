#include <cstdio>
#include "../SDL2/SDL.h"
#include "../SDL2/SDL_image.h"
#include "renderer.h"
#include "texture.h"
#include "font.h"

namespace nafw
{

Texture::~Texture()
{
  Free();
}

bool Texture::Load(std::string path)
{
  SDL_assert(renderer_!=nullptr);

  // Deallocate texture
  Free();

  SDL_Texture* temp = IMG_LoadTexture(renderer_->GetRenderer(), path.c_str());
  if (temp == nullptr)
  {
    printf("Could not load texture %s! IMG error: %s\n", path.c_str(), IMG_GetError());
    return false;
  }

  SDL_QueryTexture(temp, nullptr, nullptr, &w_, &h_);
  texture_ = temp;

  path_ = path;
  loaded_ = true;

  // Return success
  return texture_ != nullptr;
}

bool Texture::LoadText(Font* font, std::string text, SDL_Color color)
{
  SDL_assert(renderer_ != nullptr);

  //Deallocate texture
  Free();

  SDL_Surface* surface = TTF_RenderText_Solid(font->font(), text.c_str(), color);
  if (surface == nullptr)
  {
    printf("Could not create surface from ttf! SDL error: %s\n", SDL_GetError());
    return false;
  }

  // Create texture from surface
  texture_ = SDL_CreateTextureFromSurface(renderer_->GetRenderer(), surface);
  if (texture_ == nullptr)
  {
    printf("Could not create texture from surface! SDL error: %s\n", SDL_GetError());
    return false;
  }

  w_ = surface->w;
  h_ = surface->h;

  SDL_FreeSurface(surface);

  loaded_ = true;

  return true;
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
  SDL_assert(loaded_);
  // Modulate texture rgb
  SDL_SetTextureColorMod(texture_, r, g, b);
}

void Texture::SetBlendMode(SDL_BlendMode blending)
{
  SDL_assert(loaded_);
  // Set blending function
  SDL_SetTextureBlendMode(texture_, blending);
}

void Texture::SetAlpha(Uint8 alpha)
{
  SDL_assert(loaded_);
  // Modulate texture alpha
  SDL_SetTextureAlphaMod(texture_, alpha);
}

SDL_Texture* Texture::GetTexture()
{
  SDL_assert(loaded_);
  return texture_;
}

void Texture::Free()
{
  if (loaded_ && texture_ != nullptr)
  {
    SDL_DestroyTexture(texture_);
    w_ = 0;
    h_ = 0;
    loaded_ = false;
    path_.clear();
  }
}

}

