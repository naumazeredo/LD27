/**
 *  Ludum Dare 27
 *
 *  Door
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 */

#ifndef LD_DOOR_H_
#define LD_DOOR_H_

#include "gameobj.h"

namespace nafw
{
class Game;
}

class Door
{
 public:
  // Constructor
  Door(nafw::Game* game) : game_(game) {}
  Door(const Door&) = default;
  Door(Door&&) = default;
  Door& operator=(const Door&) = default;
  Door& operator=(Door&) = default;
  ~Door();

  // Draw function
  virtual void Draw(depth=0.0f) final;
 private:
  // Game
  nafw::Game* game_;
};

#endif//LD_DOOR_H_
