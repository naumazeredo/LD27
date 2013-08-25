/**
 *  Ludum Dare 27
 *
 *  Person class
 *
 *  \brief Player and NPCs base
 *
 */

#ifndef LD_PERSON_H_
#define LD_PERSON_H_

#include <string>
#include "gameobj.h"

namespace nafw
{
class Game;
class Sprite;
}

class Door;
class Room;

class Person : public GameObject
{
 public:
  // Constructor
  Person(nafw::Game* game) : game_(game) {};
  Person(const Person&) = default;
  Person(Person&&) = default;
  Person& operator=(const Person&) = default;
  Person& operator=(Person&&) = default;
  virtual ~Person();

  // GameObject
  virtual void Move(float x, float y) override;

  // Create person
  void Create(std::string name = "person");

  // Locate in a room
  void SetRoom(Room* room, float x);

  // Get room
  inline Room* room() const { return room_; }

  // Interaction
  void EnterDoor();

  // CollisionBox
  SDL_Rect GetCollisionBox() const;

  // Draw function
  virtual void Draw(float depth = 0.0f) final;

 protected:
  // Interaction
  bool IsAtDoor();

  // Game
  nafw::Game* game_;

  // Sprite
  nafw::Sprite* sprite_[2]= {nullptr, nullptr};

  // Current Room
  Room* room_=nullptr;

  // Room player is above (updated everytime AtDoor is called)
  Door* door_=nullptr;
};

#endif//LD_PERSON_H_
