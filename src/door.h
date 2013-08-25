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

struct SDL_Rect;

namespace nafw
{
class Game;
}

class Room;

class Door : public GameObject
{
 public:
  // Constructor
  Door(nafw::Game* game) : game_(game), w_(32), h_(40) {}
  Door(const Door&) = default;
  Door(Door&&) = default;
  Door& operator=(const Door&) = default;
  Door& operator=(Door&) = default;
  virtual ~Door() {}

  // Create door
  void SetRoom(Room* room, int x);

  // Draw function
  virtual void Draw(float depth=0.0f) final;

  // Get room
  Room* room() const { return room_; }

  // Get destination door
  Door* dest() const { return dest_; }

  // Collision Box
  SDL_Rect GetCollisionBox() const;

  // Link doors
  // Move the second room so the doors overlap
  static void LinkDoors(Door* a, Door* b);
 private:
  // SetDestination
  void SetDestination(Door* door);

  // Game
  nafw::Game* game_;

  // Room
  Room* room_;

  // size
  int w_, h_;

  // Destination
  Door* dest_ = nullptr;
};

#endif//LD_DOOR_H_
