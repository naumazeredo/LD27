/**
 *  Ludum Dare 27
 *
 *  Room class
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 */

#ifndef LD_ROOM_H_
#define LD_ROOM_H_

#include <vector>
#include "gameobj.h"

namespace nafw
{
class Game;
}

class Person;

class Room : public GameObject
{
 public:
  // Constructor
  Room(nafw::Game* game, int w, int h) : game_(game), w_(w), h_(h) {};
  Room(const Room&) = default;
  Room(Room&&) = default;
  Room& operator=(const Room&) = default;
  Room& operator=(Room&&) = default;
  ~Room();

  // Add Person
  void AddNPC(Person* npc, int x);

  // Draw function
  virtual void Draw(float depth=0.0f) final;

  //
  inline int w() const { return w_; }
  inline int h() const { return h_; }

 private:
  // Game
  nafw::Game* game_;

  // Room properties
  int w_, h_;

  // NPCs
  std::vector<Person*> npc_;
};

#endif//LD_ROOM_H_

