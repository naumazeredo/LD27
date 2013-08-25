#include <cstdio>
#include <cmath>
#include "../SDL2/SDL_video.h"
#include "../SDL2/SDL_image.h"
#include "../SDL2/SDL_rect.h"
#include "texture.h"
#include "renderer.h"
#include "geom.h"
#include "../game.h"
#include "camera.h"

namespace nafw
{

Renderer::Renderer(Game* game, Uint32 flags)
{
  SDL_assert(game != nullptr);
  game_ = game;

  renderer_ = SDL_CreateRenderer(game_->window_, -1, flags);
  if (renderer_ == nullptr)
  {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    return;
  }

  SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

  // TODO initialize IMG
  if (!IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)
  {
    printf("SDL_image could not be initialized! SDL image error: %s\n", IMG_GetError());
    return;
  }
}

Renderer::~Renderer()
{
  if (renderer_ != nullptr)
    SDL_DestroyRenderer(renderer_);

  // Destroy textures
  if (!texture_container_.empty())
  {
    for (auto it = texture_container_.begin(); it != texture_container_.end(); ++it)
    {
      delete *it;
      texture_container_.erase(it);
    }
  }
}

Texture* Renderer::LoadTexture(std::string path)
{
  // Verify if texture was already loaded
  for (auto it : texture_container_)
    if (it->GetPath().compare(path) == 0)
      return it;

  // If not, create and load the new texture
  Texture* tex = new Texture(this);
  tex->Load(path);
  texture_container_.push_back(tex);
  return tex;
}

SDL_Rect Renderer::GetViewport()
{
  // Verify if is in camera view
  SDL_Rect viewport {0, 0, game_->width_, game_->height_};
  if (game_->camera_ != nullptr) viewport = game_->camera_->ToSDL();

  return viewport;
}

void Renderer::DrawTexture(Texture* texture, Point position, bool flip)
{
  DrawTexture(texture, position, nullptr, 1.0f, NULL, 0.0, flip);
}

void Renderer::DrawTexture(Texture* texture, Point position, const Rect* clip, bool flip)
{
  DrawTexture(texture, position, clip, 1.0f, nullptr, 0.0, flip);
}

void Renderer::DrawTexture(Texture* texture, Point position, const Rect* clip, const float scale, bool flip)
{
  DrawTexture(texture, position, clip, scale, nullptr, 0.0, flip);
}

void Renderer::DrawTexture(Texture* texture, Point position, const Rect* clip, const float scale, const Point* center, const double angle, bool flip)
{
  SDL_Rect viewport = GetViewport();
  SDL_Rect scalerect {
    position.x,
    position.y,
    (clip != nullptr ? static_cast<int>(clip->w * scale) : static_cast<int>(texture->w() * scale)),
    (clip != nullptr ? static_cast<int>(clip->h * scale) : static_cast<int>(texture->h() * scale))
  };
  if (!SDL_HasIntersection(&viewport, &scalerect)) return;  // Not in viewport

  scalerect.x -= viewport.x;
  scalerect.y -= viewport.y;

  SDL_Rect cliprect {
    (clip != nullptr ? static_cast<int>(clip->x) : 0),
    (clip != nullptr ? static_cast<int>(clip->y) : 0),
    (clip != nullptr ? static_cast<int>(clip->w) : texture->w()),
    (clip != nullptr ? static_cast<int>(clip->h) : texture->h())
  };
  SDL_Point* ctr = nullptr;
  if (center != nullptr)
  {
    ctr = new SDL_Point;
    *ctr = center->ToSDL();
  }
  SDL_RenderCopyEx(renderer_, texture->GetTexture(), &cliprect, &scalerect, angle, ctr, (flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE));
}

void Renderer::DrawLine(SDL_Point start, SDL_Point end, SDL_Color color)
{
  SDL_Rect viewport = GetViewport();

  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderDrawLine(renderer_, start.x - viewport.x, start.y - viewport.y, end.x - viewport.x, end.y - viewport.y);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::DrawRect(SDL_Rect rect, SDL_Color color)
{
  SDL_Rect viewport = GetViewport();
  SDL_Rect dest { rect.x - viewport.x, rect.y - viewport.y, rect.w, rect.h };

  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(renderer_, &dest);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::DrawFillRect(SDL_Rect rect, SDL_Color color)
{
  SDL_Rect viewport = GetViewport();
  SDL_Rect dest { rect.x - viewport.x, rect.y - viewport.y, rect.w, rect.h };

  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer_, &dest);
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::DrawCircle(SDL_Point center, float radius, SDL_Color color, float arc_delta)
{
  SDL_Rect viewport = GetViewport();
  SDL_Point realcenter {center.x - viewport.x, center.y - viewport.y};

  Uint8 r, g, b, a;
  SDL_GetRenderDrawColor(renderer_, &r, &g, &b, &a);
  SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);

  float angle = 0.0f;

  float rad_arc = arc_delta * M_PI / 180.0f;
  for (; angle <= 2 * M_PI - rad_arc; angle += rad_arc)
  {
    SDL_RenderDrawLine(
      renderer_,
      realcenter.x + radius * sin(angle),
      realcenter.y + radius * cos(angle),
      realcenter.x + radius * sin(angle + rad_arc),
      realcenter.y + radius * cos(angle + rad_arc)
    );
  }

  if (angle < M_PI)
  {
    SDL_RenderDrawLine(
      renderer_,
      realcenter.x + radius * sin(angle),
      realcenter.y + radius * cos(angle),
      realcenter.x + radius * sin(2 * M_PI),
      realcenter.y + radius * cos(2 * M_PI)
    );
  }

  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void Renderer::ClearScreen()
{
  SDL_RenderClear(renderer_);
}

void Renderer::RenderScreen()
{
  SDL_RenderPresent(renderer_);
}

}
