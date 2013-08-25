#include "room.h"
#include "game.h"
#include "render/renderer.h"
#include "door.h"
#include "person.h"

void Room::AddNPC(Person* npc, int x)
{
  npc->SetRoom(this, x);
  npc_.push_back(npc);
}

void Room::AddDoor(Door* door, int x)
{
  door->SetRoom(this, x);
  door_.push_back(door);
}

void Room::Draw(float depth)
{
  if (!visible_) return;

  // Draw Room
  SDL_Rect rect;
  rect.x = static_cast<int>(x_);
  rect.y = static_cast<int>(y_);
  rect.w = static_cast<int>(w_);
  rect.h = static_cast<int>(h_);
  game_->renderer()->DrawRect(rect);

  // Draw doors
  for (auto it : door_)
    it->Draw();

  // Draw NPCs
  for (auto it : npc_)
    it->Draw();
}
