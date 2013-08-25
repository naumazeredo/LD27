#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_assert.h"
#include "person.h"
#include "door.h"
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

  int tw;
  sprite_[0]->GetSize(&tw, nullptr);

  if (room_ != nullptr)
  {
    if (x_ < 0) x_ = 0;
    else if (x_ + tw > room_->w()) x_ = room_->w() - tw;
  }

  if (x > 0) facing_ = DIRECTION_RIGHT;
  else if (x < 0) facing_ = DIRECTION_LEFT;
}

void Person::SetRoom(Room* room, float x)
{
  room_ = room;
  x_ = x;
}

bool Person::IsAtDoor()
{
  std::vector<Door*> door = room_->DoorVector();
  for (auto& it : door)
  {
    SDL_Rect a = GetCollisionBox();
    SDL_Rect b = it->GetCollisionBox();

    if (SDL_HasIntersection(&a, &b))
    {
      door_ = it;
      return true;
    }
  }

  door_ = nullptr;
  return false;
}

void Person::EnterDoor()
{
  if (!IsAtDoor()) return;
  if (door_->dest() == nullptr) return;

  float dx = x_ - door_->x();

  // Change rooms
  // Old room
  //room_->set_visible(false);

  // New room
  room_ = door_->dest()->room();
  x_ = door_->dest()->x() + dx;
  //room_->set_visible(true);

  // Above door
  door_ = nullptr;
}

SDL_Rect Person::GetCollisionBox() const
{
  int tw, th;
  sprite_[0]->GetSize(&tw, &th);

  float x = x_;//, y = y_;
  if (room_ != nullptr)
  {
    x += room_->x();
    //y += room_->y();
  }

  SDL_Rect rect;
  rect.x = static_cast<int>(x);
  rect.y = static_cast<int>(0);
  rect.w = static_cast<int>(tw);
  rect.h = static_cast<int>(th);
  return rect;
}

void Person::Draw(float depth)
{
  SDL_assert(init_);
  if (!visible_) return;

  // Draw sprite relatively to room
  float x = x_;//, y = y_;
  if (room_ != nullptr)
  {
    x += room_->x();
    //y += room_->y();
  }
  //sprite_[facing_]->Draw(x, y, depth);
  sprite_[facing_]->Draw(x, 0, depth);
}
