/**
 *  Ludum Dare 27
 *
 *  coded by Naum Azeredo <naumazeredo@gmail.com>
 *
 */

#ifndef LD_GAME_H_
#define LD_GAME_H_

#include <vector>
#include <map>
#include "game.h"

class Person;
class Room;

class LDGame : public nafw::Game
{
 public:
  // Constructor
  LDGame() {}
  ~LDGame();

  // Game inheritance
  virtual void LoadAssets() override;
  virtual void Step(int delta) override;
  virtual void PhysicsStep(int delta) override;
  virtual void Draw() override;

 protected:
  virtual bool HandleInputs() override;

 private:
  // Player
  // FIXME change from Person to Player
  Person* player_;
  enum PlayerMove
  {
    MOVE_NOWHERE,
    MOVE_RIGHT,
    MOVE_LEFT
  };

  PlayerMove move_player_ = MOVE_NOWHERE;

  // NPCs
  std::map<std::string, Person*> npc_;

  // Rooms
  std::vector<Room*> room_;
};

#endif//LD_GAME_H_
