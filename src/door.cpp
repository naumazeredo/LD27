#include "SDL2/SDL_rect.h"
#include "game.h"
#include "render/renderer.h"
#include "room.h"
#include "door.h"


void Door::SetRoom(Room* room, int x)
{
  room_ = room;
  x_ = x;
}

void Door::SetDestination(Door* door)
{
  dest_ = door;
}

void Door::Draw(float depth)
{
  if (!visible_) return;

  // Draw door relatively to room
  float x = x_, y = y_;

  if (room_ != nullptr)
  {
    x += room_->x();
    y += room_->y();
  }

  SDL_Rect rect = GetCollisionBox();
  game_->renderer()->DrawRect(rect);
}

SDL_Rect Door::GetCollisionBox() const
{
  float x = x_;

  if (room_ != nullptr)
    x += room_->x();

  SDL_Rect rect;
  rect.x = static_cast<int>(x);
  rect.y = static_cast<int>(-7);
  rect.w = static_cast<int>(w_);
  rect.h = static_cast<int>(h_);
  return rect;
}

void Door::LinkDoors(Door* a, Door* b)
{
  a->SetDestination(b);
  b->SetDestination(a);

  // Move b's room so the doors overlap
  b->room()->SetPosition(a->x() - b->x(), -67);
}

