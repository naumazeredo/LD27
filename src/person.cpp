#include "SDL2/SDL_assert.h"
#include "person.h"
#include "room.h"
#include "game.h"
#include "render/sprite.h"

Person::~Person()
{
  if (sprite_[0] != nullptr) delete sprite_[0];
  if (sprite_[1] != nullptr) delete sprite_[1];
}

void Person::Create(std::string name)
{
  std::string path = "assets/";
  path += name;
  path += ".png";

  nafw::Sprite* temp = new nafw::Sprite();
  temp->Create(game_->renderer(), path.c_str());

  sprite_[DIRECTION_RIGHT] = temp;

  temp = new nafw::Sprite();
  temp->Create(game_->renderer(), path.c_str());
  temp->AddClip(nullptr, nullptr, true);

  sprite_[DIRECTION_LEFT] = temp;

  init_ = true;
}

void Person::Move(float x, float y)
{
  x_ += x;
  y_ += y;

  int tw, th;
  sprite_[0]->GetSize(&tw, &th);

  if (room_ != nullptr)
  {
    if (x_ < room_->x()) x_ = room_->x();
    else if (x_ + tw > room_->x() + room_->w()) x_ = room_->x() + room_->w() - tw;

    /*
    if (y_ < r
    */
  }

  if (x > 0) facing_ = DIRECTION_RIGHT;
  else if (x < 0) facing_ = DIRECTION_LEFT;
}

void Person::SetRoom(Room* room, float x)
{
  room_ = room;
  x_ = x;
}

void Person::Draw(float depth)
{
  SDL_assert(init_);
  if (!visible_) return;
  sprite_[facing_]->Draw(x_, y_, depth);
}
