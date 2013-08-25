/**
 *  Not Available Framework
 *
 *  Game Application Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 */

#include <cstdio>
#include <sstream>
#include "SDL2/SDL.h"
#include "game.h"
#include "timer.h"
#include "render/renderer.h"
#include "render/texture.h"
#include "render/sprite.h"
#include "render/animatedsprite.h"
#include "render/geom.h"

namespace nafw
{

Game::Game()
{
  timer_ = new Timer();
}

Game::~Game()
{
  if (window_ != nullptr)
    SDL_DestroyWindow(window_);
  if (timer_ != nullptr)
    delete timer_;
  if (renderer_ != nullptr)
    delete renderer_;
}

bool Game::Start(const char* title, int argc, char** argv)
{
  // Init SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Could not init SDL: %s\n", SDL_GetError());
    return false;
  }

  // TODO read arguments and config file
  // Enable VSync
  /*
  if (!SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1"))
  {
    printf("VSync not enabled!\n");
  }
  */

  // Set texture filtering to linear
  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
  {
    printf("Linear texture filtering not enabled!\n");
  }

  // Create window
  window_ = SDL_CreateWindow(
    title,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN
  );
  if (window_ == NULL)
  {
    printf("Could not create window: %s\n", SDL_GetError());
    return false;
  }

  renderer_ = new Renderer(window_, SDL_RENDERER_ACCELERATED);

  this->init_ = true;

  return true;
}

void Game::SetFullscreen(bool fullscreen, bool borderless)
{
  SDL_assert(this->init_);
  Uint32 flags = 0;

  this->fullscreen_ = fullscreen || borderless;

  if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
  if (borderless) flags = SDL_WINDOW_FULLSCREEN_DESKTOP;

  SDL_SetWindowFullscreen(window_, flags);
}

void Game::ToggleFullscreen()
{
  this->fullscreen_ = !this->fullscreen_;
  SetFullscreen(this->fullscreen_, false);
}

bool Game::HandleInputs()
{
  // Basic Inputs
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT )
      return true;

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_F4 && (event.key.keysym.mod & KMOD_LALT))
        return true;

      if (event.key.keysym.sym == SDLK_RETURN && (event.key.keysym.mod & KMOD_LALT))
        this->ToggleFullscreen();
    }
  }

  return false;
}

bool Game::Run()
{
  SDL_assert(this->init_);

  // Testing area
  AnimatedSprite anim;
  anim.Create(renderer_, "assets/transp.png");

  anim.AddClip(new Rect(0, 0, 32, 32), nullptr, false);
  anim.AddClip(new Rect(32, 0, 32, 32), nullptr, false);
  anim.AddClip(new Rect(64, 0, 32, 32), nullptr, false);
  anim.AddClip(new Rect(96, 0, 32, 32), nullptr, false);

  anim.AddFrame(1, 1000);
  anim.AddFrame(2, 1000);
  anim.AddFrame(3, 1000);
  anim.AddFrame(2, 1000);

  anim.PlayAnimation();
  anim.SetAnimationLoop(true);
  // -----

  // Physics
  physics_dt = 10;
  int physics_accum = 0;

  // FIXME networking must be in the network environment
  /*
  bool network_on = false;
  //int local_sequence = 0;
  //int remote_sequence = 0;
  int network_dt = 30;
  int network_accum = 0;
  */

  // Init timer
  timer_->Init();

  // FPS counter
  int framecount=0;
  int frametime=timer_->GetTime();

  bool quit = false;
  while (!quit)
  {
    // Update timer
    timer_->NextFrame();

    // Handle input when network is off
    //if (!network_on)
    {
      if (HandleInputs())
      {
        quit = true;
        break;
      }
    }

    // Networking
    // XXX All networking should be apart
    /*
    network_accum += timer_->GetDelta();
    while (network_on && network_accum >= network_dt)
    {
      // Networking
      // Server->Client
      // TODO Verify if received a socket

      // Client->Server
      if (network_accum >= network_dt)
      {
        // Handle User Inputs
        if (HandleInputs())
        {
          quit = true;

          // TODO Send disconnect to server
          break;
        }

        // TODO Send file

        // Update accumulator
        network_accum -= network_dt;
      }

      // TODO Send update to server
    }
    */

    // Update physics
    physics_accum += timer_->GetDelta();
    while (physics_accum >= physics_dt)
    {
      // Physics
      if (physics_accum >= physics_dt)
      {
        //
        anim.Step(physics_dt);

        /* TODO Step physics */
        // Pass timer_->GetTime() + delta_physics to physics

        // Update accumulator
        physics_accum -= physics_dt;
      }
    }

    /* TODO Integrate the exceding time in physics */

    /* TODO Render */
    renderer_->ClearScreen();

    Draw();
    anim.Draw(100, 100);

    renderer_->RenderScreen();

    // FPS counter
    ++framecount;
    if (timer_->GetTime() - frametime >= 1000)
    {
      // Change window title
      std::ostringstream oss;
      oss << "Not Available Framework - FPS: " << framecount;
      SDL_SetWindowTitle(window_, oss.str().c_str());

      framecount = 0;
      frametime += 1000;
    }
  }

  // Finish game
  return false;
}

void Game::Draw()
{
  SDL_assert(this->init_);
}

}
