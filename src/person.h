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

#include <map>
#include <string>
#include "gameobj.h"
#include "question.h"

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

  // Speak
  void Speak();
  void SpeakDelay(int delay);
  inline void set_responsive(bool resp) { responsive_ = resp; }
  inline bool responsive() { return responsive_; }

  // Add phrases
  void AddPhrase(Question question, std::string phrase);

  // Step
  void Step(int delta);

  // Draw function
  virtual void Draw(float depth = 0.0f) final;

 protected:
  // Interaction
  bool IsAtDoor();

  // Draw text
  void DrawSpeak();

  // Game
  nafw::Game* game_;

  // Sprite
  nafw::Sprite* sprite_[2]= {nullptr, nullptr};

  // Current Room
  Room* room_=nullptr;

  // Room player is above (updated everytime AtDoor is called)
  Door* door_=nullptr;

  // phrases
  std::map<Question, std::string> phrases_;
  bool speaking_ = false;
  int speaking_accum_ = 0;
  bool delay_ = false;
  int delay_accum_ = 0;
  bool responsive_ = true;
};

#endif//LD_PERSON_H_
