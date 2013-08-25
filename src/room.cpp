#include "room.h"
#include "game.h"
#include "render/renderer.h"
#include "person.h"

void Room::AddNPC(Person* npc, int x)
{
  npc->SetRoom(this, x + x_);
  npc_.push_back(npc);
}

void Room::Draw(float depth)
{
  if (!visible_) return;

  SDL_Rect rect;
  rect.x = static_cast<int>(x_);
  rect.y = static_cast<int>(y_);
  rect.w = static_cast<int>(w_);
  rect.h = static_cast<int>(h_);
  game_->renderer()->DrawRect(rect);

  for (auto it : npc_)
    it->Draw();
}
