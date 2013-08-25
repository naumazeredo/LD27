/**
 *  Not Available Framework
 *
 *  Game Application Class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 *  \brief Stores all main game structures
 *    Handle window and events
 *    Controls time flow and game state
 *
 */

#ifndef NAFW_GAME_H_
#define NAFW_GAME_H_

struct SDL_Window;

// Not Available Framework
namespace nafw
{

class Timer;
class Renderer;
class Camera;

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

/**
 *  Game Class
 *
 *  \brief Base game class, should be inherited
 */
// TODO Add Network
// TODO Add Physics
// TODO Add Camera (on renderer?)
class Game
{
 public:
  // Friends
  friend class Renderer;

  // Constructor and Destructor
  Game();
  virtual ~Game();

  // Start window with WINDOW_WIDTH x WINDOW_HEIGHT
  // TODO Save and read settings file
  bool Start(const char* title, int argc, char** argv);

  // Resize Window
  void SetSize(unsigned int w, unsigned int h);
  inline int GetWindowWidth() { return width_; }
  inline int GetWindowHeight() { return height_; }

  // Set fullscreen mode
  void SetFullscreen(bool fullscreen, bool borderless);
  void ToggleFullscreen();

  // Load stuff
  virtual void LoadAssets();

  // Run game logic
  bool Run();
  virtual void Step(int delta);

  // Physics update
  virtual void PhysicsStep(int delta);

  // Draw everything
  virtual void Draw();

  // Renderer
  inline Renderer* renderer() const { return renderer_; }

  // FPS
  inline float GetFPS() const { return fps_; }

  // Camera
  inline void SetCamera(Camera* camera) { camera_ = camera; }
  inline Camera* camera() const { return camera_; }

 protected:
  // Handle inputs
  virtual bool HandleInputs();

 private:
  // Game was initialized?
  bool init_ = false;

  // Game Window
  SDL_Window* window_ = nullptr;
  int width_, height_;
  bool fullscreen_ = false;

  // Renderer
  Renderer* renderer_ = nullptr;

  // Camera
  Camera* camera_ = nullptr;

  // Physics
  // TODO Create Physics class
  int physics_dt;

  // Game Timer
  nafw::Timer* timer_;

  // FPS
  float fps_ = 60.0f;
};

// Not Available Framework
}

#endif//NAFW_GAME_H_
