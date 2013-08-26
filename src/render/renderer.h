/**
 *  Not Available Framework
 *
 *  Renderer Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Holds, manages and draws game textures
 *
 */

#ifndef NAFW_RENDER_RENDERER_H_
#define NAFW_RENDER_RENDERER_H_

#include <vector>
#include <string>
#include "../SDL2/SDL_rect.h"
#include "../SDL2/SDL_render.h"
#include "constants.h"

struct SDL_Window;
struct SDL_Renderer;

namespace nafw
{

class Point;
class Rect;
class Texture;
class Game;

// TODO Gather all drawing to do one
class Renderer
{
 public:
  // Constructor and Destructor
  Renderer(Game* game, Uint32 flags);
  ~Renderer();

  // Return Renderer
  inline SDL_Renderer* GetRenderer() const { return renderer_; }

  // Texture loader
  Texture* LoadTexture(std::string path);

  void DrawTexture(Texture* texture, Point position, bool flip = false);   // Basic texture drawing
  void DrawTexture(Texture* texture, Point position, const Rect* clip, bool flip = false);   // Clipped drawing
  void DrawTexture(Texture* texture, Point position, const Rect* clip, const float scale, bool flip = false);    // Scaled, clipped drawing
  void DrawTexture(Texture* texture, Point position, const Rect* clip, const float scale, const Point* center, const double angle, bool flip = false); // Rotated, scaled, clipped drawing

  // Basic draw
  void DrawLine(SDL_Point start, SDL_Point end, SDL_Color color = Color::black);
  void DrawRect(SDL_Rect rect, SDL_Color color = Color::black);
  void DrawFillRect(SDL_Rect rect, SDL_Color color = Color::black);
  void DrawCircle(SDL_Point center, float radius, SDL_Color color = Color::black, float arc_delta=5.0f);

  // Text drawing
  void DrawText(std::string text, Point position, SDL_Color color = Color::black);

  void ClearScreen();
  void RenderScreen();

 private:
  // Get Viewport
  SDL_Rect GetViewport();

  // Game
  Game* game_;

  // SDL Renderer
  SDL_Renderer* renderer_ = nullptr;

  // Texture Container
  // FIXME textures can change properties, so it shouldnt be contained by path
  std::vector<Texture*> texture_container_;
};

}

#endif//NAFW_RENDER_RENDERER_H_
